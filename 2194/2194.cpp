#include<iostream>
#include<stdio.h>
#include<cstring>
// using namespace std;
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
const int MAXN=11;
#endif
#ifndef SMALL
const int MAXN=5000006;
const int bits=31;
#endif

int n,u,v,w;

int head[MAXN],next[2*MAXN],edto[2*MAXN],edwe[2*MAXN],etop;

void ins(int s, int t,int w)
{
    edto[++etop]=t;
    edwe[etop]=w;
    next[etop]=head[s];
    head[s]=etop;
}

int sum[MAXN];

void dfs(int now,int fat)
{
    for(int i=head[now];i;i=next[i])
    {
        int son=edto[i],w=edwe[i];
        if(son==fat)continue;
        sum[son]=w^sum[now];
        dfs(son,now);
    }
}

int tire[MAXN][2],tirecnt;

void insert(int x)
{
    int now=0;
    for(int i=30;i>=0;i--)
    {
        int bit=((x>>i)&1);
        if(!tire[now][bit])
            tire[now][bit]=++tirecnt;
        now=tire[now][bit];
    }
}
void build()
{
    for(int i=1;i<=n;i++)
    {
        insert(sum[i]);
    }
}
int ans;
int search(int x)
{
    int now=0,subans=0;
    for(int i=30;i>=0;i--)
    {
        int bit=((x>>i)&1);
        if(tire[now][1^bit])
        {
            now=tire[now][1^bit];
            subans+=1<<i;
        }
        else
        {
            now=tire[now][bit];
        }
        if(subans&&((unsigned)subans<<1)<(unsigned)ans)break;
    }
    return subans;
}

#ifdef MAIN
//主函数
int main()
{
    #ifdef DEBUG
        file_mode();
    #endif

    quickread(n);
    for(int i=1;i<n;i++)
    {
        quickread(u);quickread(v);quickread(w);
        ins(u,v,w);
        ins(v,u,w);
    }

    dfs(1,0);
    build();
    for(int i=1;i<=n;i++)
    {
        ans=std::max(ans,search(sum[i]));
    }
    quickwrite(ans);
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
        int file_path_lenth=strlen(file_path);
        file_path[file_path_lenth++]='/';
        file_path[file_path_lenth+0]=file_path[file_path_lenth-5];
        file_path[file_path_lenth+1]=file_path[file_path_lenth-4];
        file_path[file_path_lenth+2]=file_path[file_path_lenth-3];
        file_path[file_path_lenth+3]=file_path[file_path_lenth-2];
        file_path[file_path_lenth+4]='.';
        file_path[file_path_lenth+5]='i';
        file_path[file_path_lenth+6]='n';
        file_path[file_path_lenth+7]='\0';
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

