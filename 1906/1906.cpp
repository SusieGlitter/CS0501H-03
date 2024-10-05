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
const int MAXN=5003;
const int MAXM=100005;
#endif

int n,m,k,parts;
int u,v,w;
long long ans[MAXN],ans_top;

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
    parts--;
    ++ans_top;
    ans[ans_top]=ans[ans_top-1]+dis;
    if(dsu_siz[x]<dsu_siz[y])
        std::swap(x,y);
    dsu_fat[y]=x;
    dsu_siz[x]+=dsu_siz[y];
}

//heap
struct node
{
    int s;
    int t;
    int dis;
};
int heap_size;
node heap[MAXM];

void heap_down(int now)
{
    while(now*2<=heap_size)
    {
        int son=now*2;
        if(son+1<=heap_size&&heap[son+1].dis<heap[son].dis)son++;
        if(heap[son].dis>=heap[now].dis)break;
        std::swap(heap[now],heap[son]);
        now=son;
    }
}
void heap_build()
{
    for(int i=heap_size;i>=1;i--)
        heap_down(i);
}
node heap_pop()
{
    node ret=heap[1];
    heap[1]=heap[heap_size--];
    heap_down(1);
    return ret;
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
    quickread(k);

    for(int i=1;i<=m;i++)
    {
        quickread(u);
        quickread(v);
        quickread(w);
        heap[++heap_size].dis=w;
        heap[heap_size].s=u;
        heap[heap_size].t=v;
    }
    heap_build();
    dsu_pre();
    node temp;
    int s,t,dis;
    parts=n;
    while(parts!=1)
    {
        temp=heap_pop();
        s=temp.s;
        t=temp.t;
        dis=temp.dis;
        dsu_unite(s,t,dis);
    }
    quickwrite(ans[ans_top-k]);

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