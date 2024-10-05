#include<iostream>
#include<stdio.h>
#include<cstring>
#include<cmath>
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
const int MAXN=10004;
const int MAXM=500005;
#endif

int n,m,q;
int s,t,dis;

//graph
int head[MAXN],next[2*MAXN],edto[5*MAXN],edle[5*MAXN],ecnt;

void ins(int s,int t,int w)
{
    next[++ecnt]=head[s];
    head[s]=ecnt;
    edto[ecnt]=t;
    edle[ecnt]=w;
}
void ins2(int s,int t,int w)
{
    ins(s,t,w);
    ins(t,s,w);
}

// dsu
int dsu_fat[MAXN];
int dsu_siz[MAXN];

void dsu_pre()
{
    for(int i=1;i<=n;i++)
    {
        dsu_fat[i]=i;
        dsu_siz[i]=1;
    }
}

int dsu_find(int x)
{
    return dsu_fat[x]==x?x:dsu_fat[x]=dsu_find(dsu_fat[x]);
}

void dsu_unite(int x,int y,int dis)
{
    x=dsu_find(x);
    y=dsu_find(y);
    if(x==y)return;
    if(dsu_siz[x]<dsu_siz[y])
        std::swap(x,y);
    dsu_fat[y]=x;
    dsu_siz[x]+=dsu_siz[y];
    ins2(x,y,dis);
}

//heap
struct edge
{
    int s;
    int t;
    int dis;
};
int heap_size;
edge heap[MAXM];

void heap_down(int now)
{
    while(now*2<=heap_size)
    {
        int son=now*2;
        if(son+1<=heap_size&&heap[son+1].dis>heap[son].dis)son++;
        if(heap[son].dis<=heap[now].dis)break;
        std::swap(heap[now],heap[son]);
        now=son;
    }
}
void heap_build()
{
    for(int i=heap_size;i>=1;i--)
        heap_down(i);
}
edge heap_pop()
{
    edge ret=heap[1];
    heap[1]=heap[heap_size--];
    heap_down(1);
    return ret;
}

//lca

int f[20][MAXN],w[20][MAXN],dep[MAXN];

void lca_init(int fat,int now)
{
    // quickwrite(now);

    dep[now]=dep[fat]+1;
    f[0][now]=fat;
    for(int i=1;i<20;i++)
    {
        f[i][now]=f[i-1][f[i-1][now]];
        w[i][now]=std::min(w[i-1][now],w[i-1][f[i-1][now]]);
    }
    for(int i=head[now];i;i=next[i])
    {
        int son=edto[i];
        if(son==fat)continue;
        w[0][son]=edle[i];
        lca_init(now,son);
    }
}

int lca_pathmin(int x,int y)
{
    int min=0x7fffffff;
    if(dep[x]>dep[y])
        std::swap(x,y);
    for(int i=0,delta=dep[y]-dep[x];delta;i++,delta>>=1)
    {
        if(delta&1)
        {
            min=std::min(min,w[i][y]);
            y=f[i][y];
        }
    }
    if(x==y)
    {
        return min;
    }
    for(int i=19;i>=0;i--)
    {
        if(f[i][x]!=f[i][y])
        {
            min=std::min(min,w[i][x]);
            x=f[i][x];
            min=std::min(min,w[i][y]);
            y=f[i][y];
        }
    }
    min=std::min(min,w[0][x]);
    min=std::min(min,w[0][y]);

    return min;
}

#ifdef MAIN
//主函数
int main()
{
    #ifdef DEBUG
        file_mode();
    #endif
    
    quickread(n);
    quickread(m);
    for(int i=1;i<=m;i++)
    {
        quickread(s);
        quickread(t);
        quickread(dis);
        heap[++heap_size].dis=dis;
        heap[heap_size].s=s;
        heap[heap_size].t=t;
    }

    heap_build();
    dsu_pre();
    edge temp;
    while(heap_size)
    {
        temp=heap_pop();
        dsu_unite(temp.s,temp.t,temp.dis);
    }
    for(int i=1;i<=n;i++)
        if(i==dsu_find(i))
            lca_init(0,i);
    

    quickread(q);
    for(int i=1;i<=q;i++)
    {
        quickread(s);quickread(t);
        if(dsu_find(s)!=dsu_find(t))
            quickwrite(-1);
        else
            quickwrite(lca_pathmin(s,t));
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