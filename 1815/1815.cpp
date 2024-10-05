#include<iostream>
#include<stdio.h>
#include<cstring>
#include<algorithm>
using namespace std;
//调试开关
// #define DEBUG

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

#ifndef DEBUG
const int MAXN=100005;
#endif
#ifdef DEBUG
const int MAXN=102;
#endif

int n,d;
int ans=0x7fffffff;

struct node
{
    int x,y;
}miss[MAXN],tool[MAXN];
void nodesort(node* miss,int s,int t)
{
    #ifdef DEBUG
        cout<<s<<t<<1<<endl;
        for(int i=1;i<=n;i++)
        {
            quickwrite(miss[i].x);
            quickwrite(miss[i].y);
        cout<<endl;
        }
        cout<<endl;
    #endif

    if(s==t)return;
    int mid=(s+t)/2;
    nodesort(miss,s,mid);
    nodesort(miss,mid+1,t);

    
    #ifdef DEBUG
        cout<<s<<t<<2<<endl;
        for(int i=1;i<=n;i++)
        {
            quickwrite(miss[i].x);
            quickwrite(miss[i].y);
        cout<<endl;
        }
        cout<<endl;
    #endif

    for(int pi=s,pj=mid+1,pk=s;pk<=t;pk++)
        tool[pk]=((pi<=mid&&(pj>t||miss[pi].x<miss[pj].x))?miss[pi++]:miss[pj++]);
    for(int pk=s;pk<=t;pk++)
        miss[pk]=tool[pk];

    #ifdef DEBUG
        cout<<s<<t<<3<<endl;
        for(int i=1;i<=n;i++)
        {
            quickwrite(miss[i].x);
            quickwrite(miss[i].y);
        cout<<endl;
        }
        cout<<endl;
    #endif
}
class MAXqueue
{
private:
    int queue[MAXN];
    int head=0,tail=-1;
public:
    void push(int i)
    {
        while(head<=tail&&miss[queue[tail]].y<=miss[i].y)
            tail--;
        queue[++tail]=i;
    }
    void pop(int l)
    {
        while(head<=tail&&queue[head]<=l)
            head++;
    }
    int rangeMAX()
    {
        return queue[head];
    }
}maxqueue;
class MINqueue
{
private:
    int queue[MAXN];
    int head=0,tail=-1;
public:
    void push(int i)
    {
        while(head<=tail&&miss[queue[tail]].y>=miss[i].y)
            tail--;
        queue[++tail]=i;
    }
    void pop(int l)
    {
        while(head<=tail&&queue[head]<=l)
            head++;
    }
    int rangeMIN()
    {
        return queue[head];
    }
}minqueue;
#ifdef MAIN
//主函数
int main()
{
    #ifdef DEBUG
        file_mode();
    #endif
    quickread(n);
    quickread(d);
    for(int i=1;i<=n;i++)
    {
        quickread(miss[i].x);
        quickread(miss[i].y);
    }
    
    nodesort(miss,1,n);

    int l=1,r=1;
    for(;r<=n;r++)
    {
        maxqueue.push(r);
        minqueue.push(r);
        while(miss[maxqueue.rangeMAX()].y-miss[minqueue.rangeMIN()].y>=d)
        {
            ans=min(ans,miss[r].x-miss[l].x);
            maxqueue.pop(l);
            minqueue.pop(l);
            l++;
        }
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
    putchar(' ');
}

