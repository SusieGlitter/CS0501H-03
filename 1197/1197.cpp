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
const int MAXN=500005;
const int MAXM=500005;
#endif

int N,M;
int s,t;
bool bar[MAXN],Bar[MAXN];
int atm[MAXN],Atm[MAXN];
int S,P;

int head[MAXN],next[MAXM],edto[MAXM],ecnt;
int Head[MAXN],Next[MAXM],Edto[MAXM],Ecnt;

int Indeg[MAXN];

int Ans[MAXN],ANS;

void ins(int s,int t)
{
    next[++ecnt]=head[s];
    head[s]=ecnt;
    edto[ecnt]=t;
}
void Ins(int S,int T)
{
    Next[++Ecnt]=Head[S];
    Head[S]=Ecnt;
    Edto[Ecnt]=T;
    Indeg[T]++;
}

int sta[MAXN],sta_top;
int dfn[MAXN],low[MAXN],dfn_cnt;
int color[MAXN],color_cnt;
// std::vector<int>group[MAXN];
void tarjan(int now)
{
    sta[++sta_top]=now;
    low[now]=dfn[now]=++dfn_cnt;
    for(int i=head[now];i;i=next[i])
    {
        int son=edto[i];
        if(dfn[son]==0)
        {
            tarjan(son);
            low[now]=std::min(low[now],low[son]);
        }
        else if(color[son]==0)
        {
            low[now]=std::min(low[now],dfn[son]);
        }
    }
    if(dfn[now]==low[now])
    {
        color[now]=++color_cnt;
        // group[color_cnt].push_back(now);
        Atm[color_cnt]+=atm[now];
        while(sta[sta_top]!=now)
        {
            int mem=sta[sta_top];
            color[mem]=color_cnt;
            // group[color_cnt].push_back(mem);
            Atm[color_cnt]+=atm[mem];
            sta_top--;
        }
        sta_top--;
    }
}

#ifdef MAIN
//主函数
int main()
{
    #ifdef DEBUG
        file_mode();
    #endif

    quickread(N);
    quickread(M);
    for(int i=1;i<=M;i++)
    {
        quickread(s);
        quickread(t);
        ins(s,t);
    }
    for(int i=1;i<=N;i++)
    {
        quickread(atm[i]);
    }
    quickread(S);
    quickread(P);
    for(int i=1;i<=N;i++)
        if(dfn[i]==0)
            tarjan(i);
    for(int i=1;i<=N;i++)
        for(int j=head[i];j;j=next[j])
            if(color[i]!=color[edto[j]])
                Ins(color[i],color[edto[j]]);
    for(int i=1;i<=P;i++)
    {
        int b;
        quickread(b);
        Bar[color[b]]=true;
    }

    std::queue<int> topo;
    for(int i=1;i<=color_cnt;i++)
    {
        Ans[i]=-(0x3f3f3f3f);
        if(Indeg[i]==0)
            topo.push(i);
    }
    Ans[color[S]]=Atm[color[S]];
    while(topo.empty()==false)
    {
        int now=topo.front();
        topo.pop();
        for(int i=Head[now];i;i=Next[i])
        {
            int son=Edto[i];
            Ans[son]=std::max(Ans[son],Ans[now]+Atm[son]);
            if(--Indeg[son]==0)
                topo.push(son);
        }
    }
    for(int i=1;i<=color_cnt;i++)
        if(Bar[i])
            ANS=std::max(ANS,Ans[i]);
    quickwrite(ANS);


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

