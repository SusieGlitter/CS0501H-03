#include<iostream>
#include<stdio.h>
#include<cstring>
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
const int MAXN=10000007;
#endif

int n,m,a,b,c;
int head[MAXN],next[2*MAXN],edto[2*MAXN],etop;

void ins(int s, int t)
{
    edto[++etop]=t;
    next[etop]=head[s];
    head[s]=etop;
}

int dep[MAXN],f[20][MAXN];
int covery[MAXN];

void lcainit(int now,int fat)
{
    dep[now]=dep[fat]+1;
    f[0][now]=fat;
    for(int i=1;i<20;i++)
        f[i][now]=f[i-1][f[i-1][now]];
    for(int i=head[now];i;i=next[i])
    {
        int son=edto[i];
        if(son==fat)continue;
        lcainit(son,now);
    }
}
int lca(int x,int y)
{
    if(dep[x]>dep[y])
        std::swap(x,y);
    int delta=dep[y]-dep[x];
    for(int i=0;delta;i++,delta>>=1)
        if(delta&1)
            y=f[i][y];
    if(x==y)return x;
    for(int i=19;i>=0;i--)
        if(f[i][x]!=f[i][y])
        {
            x=f[i][x];
            y=f[i][y];
        }
    return f[0][x];
}

void cover(int a,int b)
{
    covery[a]++;
    covery[b]++;
    covery[lca(a,b)]-=2;
}
int ans=0;
void getans(int now,int fat)
{
    for(int i=head[now];i;i=next[i])
    {
        int son=edto[i];
        if(son==fat)continue;
        getans(son,now);
        covery[now]+=covery[son];
    }
    if(now==1)return;
    if(covery[now]==1)
        ans+=1;
    if(covery[now]==0)
        ans+=m;
}


#ifdef MAIN
//主函数
int main()
{
    #ifdef DEBUG
        file_mode();
    #endif

    quickread(n);quickread(m);
    for(int i=1;i<n;i++)
    {
        quickread(a);
        quickread(b);
        ins(a,b);
        ins(b,a);
    }
    lcainit(1,0);

    for(int i=1;i<=m;i++)
    {
        quickread(a);
        quickread(b);
        cover(a,b);
    }
    getans(1,0);
    std::cout<<ans;

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

