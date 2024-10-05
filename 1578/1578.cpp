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
const int MAXN=501;
#endif

int s,p,parts;
int x[MAXN],y[MAXN];
double ans;

// dsu
int dsu_fat[MAXN];
int dsu_siz[MAXN];

void dsu_pre()
{
    for(int i=1;i<=p;i++)
    {
        dsu_fat[i]=i;
        dsu_siz[i]=1;
    }
}

int dsu_find(int x)
{
    return dsu_fat[x]==x?x:dsu_fat[x]=dsu_find(dsu_fat[x]);
}

void dsu_unite(int x,int y)
{
    x=dsu_find(x);
    y=dsu_find(y);
    if(x==y)return;
    parts--;
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
int n;
node heap[MAXN*MAXN/2];

void heap_down(int now)
{
    while(now*2<=n)
    {
        int son=now*2;
        if(son+1<=n&&heap[son+1].dis<heap[son].dis)son++;
        if(heap[son].dis>=heap[now].dis)break;
        std::swap(heap[now],heap[son]);
        now=son;
    }
}
void heap_build()
{
    for(int i=n;i>=1;i--)
        heap_down(i);
}
node heap_pop()
{
    node ret=heap[1];
    heap[1]=heap[n--];
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

    quickread(s);
    quickread(p);
    parts=p;
    if(s>=p)
    {
        std::cout<<0<<std::endl;
        return 0;
    }
    for(int i=1;i<=p;i++)
    {
        quickread(x[i]);
        quickread(y[i]);
    }
    for(int i=1;i<=p;i++)
        for(int j=1;j<i;j++)
        {
            heap[++n].s=i;
            heap[n].t=j;
            heap[n].dis=(x[i]-x[j])*(x[i]-x[j])+(y[i]-y[j])*(y[i]-y[j]);
        }
    heap_build();
    dsu_pre();
    node temp;
    int l,r;
    while(parts!=1&&parts>s)
    {
        temp=heap_pop();
        l=temp.s;
        r=temp.t;
        dsu_unite(l,r);
    }
    ans=temp.dis;
    printf("%.2lf", sqrt(ans));

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

