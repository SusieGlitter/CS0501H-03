#include<iostream>
#include<stdio.h>
#include<cstring>
#include<vector>
#include<queue>
//调试开关
#define DEBUG

//小数据
// #define SMALL

//主函数开关
#define MAIN

#ifdef DEBUG
    #include<unistd.h>
    #include<fstream>
    #include<string.h>
    char file_path[256];
    //获取路径
    void get_path();
    //切换到文件输入输出
    void file_mode();
#endif

//快读
template<typename T>
inline void quickread(T &x);
//快输
template<typename T>
inline void quickwrite(T x);

#ifdef SMALL
const int MAXN=102;
#endif
#ifndef SMALL
const int MAXN=25004;
const int MAXM=50004;
#endif

int T,R,P,S,A,B,C,b[MAXM];

int head[MAXN],next[MAXM*4],edto[MAXM*4],edle[MAXM*4],edki[MAXM*4],ecnt;
void ins(int s,int t,int dis,int ki)
{
    next[++ecnt]=head[s];
    head[s]=ecnt;
    edto[ecnt]=t;
    edle[ecnt]=dis;
    edki[ecnt]=ki;
}
void ins2(int s,int t,int dis,int ki)
{
    ins(s,t,dis,ki);
    ins(t,s,dis,ki);
}

//缩点
std::vector<int> group[MAXN];
int color[MAXN],color_cnt,dep[MAXN],indeg[MAXN];
void dfs(int now,int col)
{
    color[now]=col;
    group[col].push_back(now);
    for(int i=head[now];i;i=next[i])
    {
        if(edki[i]==0)
        {
            int son=edto[i];
            if(color[son]==0)
                dfs(son,col);
        }
    }

}

int ans[MAXN];
bool vis[MAXN];
std::priority_queue<std::pair<int,int>,std::vector<std::pair<int,int>>,std::greater<std::pair<int,int> > > pq;
void dijk(int now_color)
{
    for(int i=0;i<group[now_color].size();i++)
    {
        int member=group[now_color][i];
        if(ans[member]<0x3f3f3f3f)
            pq.push(std::make_pair(ans[member],member));
    }
    while(pq.empty()==false)
    {
        int dis=pq.top().first;
        int now=pq.top().second;
        pq.pop();
        while(pq.empty()==false&&dis>ans[now])
        {
            dis=pq.top().first;
            now=pq.top().second;
            pq.pop();
        }
        if(pq.empty()==true&&dis>now[ans])break;
        if(vis[now])continue;
        vis[now]=true;
        for(int i=head[now];i;i=next[i])
        {
            // if(edki[i]==1)continue;
            int son=edto[i];
            if(ans[son]>ans[now]+edle[i])
            {
                ans[son]=ans[now]+edle[i];
                if(color[son]==now_color)
                    pq.push(std::make_pair(ans[son],son));
            }
        }
    }
}

#ifdef MAIN
//主函数
int main()
{
    #ifdef DEBUG
        file_mode();
    #endif

    quickread(T);
    quickread(R);
    quickread(P);
    quickread(S);
    for(int i=1;i<=R;i++)
    {
        quickread(A);
        quickread(B);
        quickread(C);
        ins2(A,B,C,0);
    }
    for(int i=1;i<=P;i++)
    {
        quickread(A);
        quickread(b[i]);
        quickread(C);
        ins(A,b[i],C,1);
    }

    for(int i=1;i<=T;i++)
        if(color[i]==0)
            dfs(i,++color_cnt);
    for(int i=1;i<=P;i++)
        indeg[color[b[i]]]++;
    
    for(int i=1;i<=T;i++)
    {
        ans[i]=0x3f3f3f3f;
    }
    ans[S]=0;

    std::queue<int> topo;
    for(int i=1;i<=color_cnt;i++)
        if(indeg[i]==0)
            topo.push(i);
    while(topo.empty()==false)
    {
        int now_color=topo.front();
        topo.pop();
        dijk(now_color);
        for(int i=0;i<group[now_color].size();i++)
            for(int j=head[group[now_color][i]];j;j=next[j])
                if(edki[j]==1)
                    if(--indeg[color[edto[j]]]==0)
                        topo.push(color[edto[j]]);
    }
    for(int i=1;i<=T;i++)
    {
        if(ans[i]==0x3f3f3f3f)
            std::cout<<"NO PATH"<<std::endl;
        else
            quickwrite(ans[i]);
    }


    #ifdef DEBUG
        fclose(stdin);
    #endif
    return 0;
}
#endif

/*
#ifdef DEBUG

#endif
*/






#ifdef DEBUG
    void get_path()
    {
        getcwd(file_path,256);
        int file_path_length=strlen(file_path);
        file_path[file_path_length++]='/';
        file_path[file_path_length+0]=file_path[file_path_length-5];
        file_path[file_path_length+1]=file_path[file_path_length-4];
        file_path[file_path_length+2]=file_path[file_path_length-3];
        file_path[file_path_length+3]=file_path[file_path_length-2];
        file_path[file_path_length+4]='.';
        file_path[file_path_length+5]='i';
        file_path[file_path_length+6]='n';
        file_path[file_path_length+7]='\0';
    }
    void file_mode()
    {
        get_path();
        std::ofstream file_in;
        if(access(file_path,F_OK))
        {
            file_in.open(file_path);
            file_in.close();
        }
        freopen(file_path,"r",stdin);
    }
#endif

template<typename T>
inline void quickread(T &x)
{
    x=0;
    char c=getchar();
    bool flag(0);
    while(!isdigit(c))flag|=c==45,c=getchar();
    while(isdigit(c))x=(x<<3)+(x<<1)+(c^48),c=getchar();
    flag?x=-x:x;
}
template<typename T>
inline void quickwrite(T x)
{
    x<0?x=-x,putchar(45):0;
    static short sta[50],top(0);
    do sta[++top]=x%10,x/=10;while(x);
    while(top)putchar(sta[top--]^48);
    putchar(10);
}

