#include<iostream>
#include<stdio.h>
#include<cstring>
using namespace std;
//调试开关
#define DEBUG

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

#ifdef DEBUG
const int MAXN=114;
#endif
#ifndef DEBUG
const int MAXN=10000007;
#endif

int n,m;
int p[MAXN];
int pre[MAXN];
int ans,maxans;


class Queue
{
private:
    int queue[MAXN];
    int head=0,tail=-1;
public:
    void push(int i)
    {
        while(head<=tail&&pre[i]<pre[queue[tail]])
            tail--;
        queue[++tail]=i;
    }
    void pop(int l)
    {
        while(head<=tail&&queue[head]<=l)
            head++;
    }
    int rangeMin()
    {
        if(head>tail)return 0;
        return queue[head];
    }
}queue;

#ifdef MAIN
//主函数
int main()
{
    #ifdef DEBUG
        file_mode();
    #endif

    cin>>n>>m;
    for(int i=1;i<=n;i++)
    {
        quickread<int>(p[i]);
        pre[i]=pre[i-1]+p[i];
    }
    queue.push(0);
    for(int i=1;i<m;i++)
    {
        queue.push(i);
        ans=max(ans,pre[i]-pre[queue.rangeMin()]);
    }
    ans=max(ans,pre[m]-pre[queue.rangeMin()]);

    for(int i=m;i<=n;i++)
    {
        queue.pop(i-m);
        queue.push(i);
        ans=max(ans,pre[i]-pre[queue.rangeMin()]);
    }
    if(ans==0)
        quickwrite<int>(maxans);
    else
        quickwrite<int>(ans);
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
        // cout<<file_path<<endl;
        ofstream file_in;
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

