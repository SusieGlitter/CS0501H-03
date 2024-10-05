#include<iostream>
#include<stdio.h>
#include<cstring>
using namespace std;
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
const int MAXN=100005;
#endif
const int MAXINT=0x7fffffff;
class seg
{
private:
    int flag[4*MAXN];
    int size;
public:
    seg(int size):size(size)
    {
        for(int i=1;i<=4*size;i++)
            flag[i]=MAXINT;
    }
    ~seg(){}

    //修改lr 当前now-st 最小尝试更新为mini
    void pushdown(int s,int t,int now)
    {
        if(flag[now]==MAXINT)return;
        flag[now*2]=min(flag[now*2],flag[now]);
        flag[now*2+1]=min(flag[now*2+1],flag[now]);
        flag[now]=MAXINT;
    }
    void pushup(int now)
    {
        return;
    }

    void update(int l,int r,int mini,int s,int t,int now)
    {

        if(l<=s&&t<=r)
        {
            flag[now]=min(flag[now],mini);
            return;
        }
        int mid=(s+t)>>1;
        pushdown(s,t,now);

        if(l<=mid&&mini<flag[now*2])update(l,r,mini,s,mid,now*2);
        if(r>mid&&mini<flag[now*2+1])update(l,r,mini,mid+1,t,now*2+1);

        pushup(now);
    }

    int ans[MAXN];
    void getans(int s,int t,int now)
    {
        if(s==t)
        {
            ans[s]=flag[now];
            return;
        }
        int mid=(s+t)>>1;
        pushdown(s,t,now);

        getans(s,mid,now*2);
        getans(mid+1,t,now*2+1);

        pushup(now);
    }

};
int n,m,h[MAXN],x,l,r;
#ifdef MAIN
//主函数
int main()
{
    #ifdef DEBUG
        file_mode();
    #endif
    quickread(n);
    quickread(m);
    for(int i=1;i<=n;i++)
    {
        quickread(h[i]);
    }
    seg boom(n);
    for(int i=1;i<=m;i++)
    {
        quickread(x);
        quickread(l);
        quickread(r);
        boom.update(l,r,x,1,n,1);
    }
    boom.getans(1,n,1);
    for(int i=1;i<=n;i++)
        quickwrite(min(h[i],boom.ans[i]));


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
