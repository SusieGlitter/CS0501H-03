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

int lowbit(int x)
{
    return x&-x;
}
class OnlyDeleteVector
{
private:
    int *data;
    int *c;
    int size;
public:
    OnlyDeleteVector(int size):size(size)
    {
        c=new int[size+1];
        data=new int[size+1];
        for(int i=1;i<=size;i++)
            data[i]=i;
        for(int i=1;i<=size;i++)
            c[i]=lowbit(i);
    }
    ~OnlyDeleteVector()
    {
        delete[] c;
        delete[] data;
    }
    void add(int x,int k)
    {
        while(x<=size)
        {
            c[x]+=k;
            x+=lowbit(x);
        }
    }
    int getsum(int x)
    {
        int ret=0;
        while(x>0)
        {
            ret+=c[x];
            x-=lowbit(x);
        }
        return ret;
    }
    int bisearch(int s,int t,int key)
    {
        while(s<t)
        {
            int mid=(s+t)/2;
            if(getsum(mid)<key)
                s=mid+1;
            else
                t=mid;
        }
        return s;
    }
    void erase(int x)
    {
        add(bisearch(1,size,x),-1);
    }
    int access(int x)
    {
        return data[bisearch(1,size,x)];
    }

};
int n;
int a[MAXN];
int ans[MAXN];
#ifdef MAIN
//主函数
int main()
{
    #ifdef DEBUG
        file_mode();
    #endif
    quickread(n);
    OnlyDeleteVector v=OnlyDeleteVector(n);
    // v.erase(3);
    // v.erase(3);
    // cout<<v.access(3);
    for(int i=1;i<=n;i++)
        quickread(a[i]);
    for(int i=n;i>=1;i--)
    {
        ans[i]=v.access(a[i]+1);
        v.erase(a[i]+1);
    }
    for(int i=1;i<=n;i++)
        quickwrite(ans[i]);

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

