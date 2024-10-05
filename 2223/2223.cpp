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
const int MAXN=100005;
#endif


int n,m;
long long a[MAXN];
int l,r,val,opt;

struct node
{
    long long range_max=0;
    long long range_sum=0;
}tree[4*MAXN+1];

inline void pushup(int now,int s,int t,int mid,int lson,int rson)
{
    tree[now].range_sum=tree[lson].range_sum+tree[rson].range_sum;
    tree[now].range_max=std::max(tree[lson].range_max,tree[rson].range_max);
}

void build(int now,int s,int t)
{
    if(s==t)
    {
        tree[now].range_max=a[s];
        tree[now].range_sum=a[s];
        return;
    }
    int mid=(s+t)>>1;
    int lson=2*now;
    int rson=lson+1;
    
    build(lson,s,mid);
    build(rson,mid+1,t);

    pushup(now,s,t,mid,lson,rson);
}

void updata_sqrt(int now,int s,int t,int l,int r)
{
    if(tree[now].range_max<=1)return;
    if(s==t)
    {
        tree[now].range_max=sqrt(tree[now].range_max);
        tree[now].range_sum=tree[now].range_max;
        return;
    }
    int mid=(s+t)>>1;
    int lson=2*now;
    int rson=lson+1;
    if(l<=mid)updata_sqrt(lson,s,mid,l,r);
    if(r>mid)updata_sqrt(rson,mid+1,t,l,r);
    pushup(now,s,t,mid,lson,rson);
}
long long getsum(int now,int s,int t,int l,int r)
{
    if(s>=l&&t<=r)
        return tree[now].range_sum;
    int mid=(s+t)>>1;
    int lson=2*now;
    int rson=lson+1;
    long long ret=0;
    if(l<=mid)ret+=getsum(lson,s,mid,l,r);
    if(r>mid)ret+=getsum(rson,mid+1,t,l,r);
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
    for(int i=1;i<=n;i++)
    	quickread(a[i]);
    build(1,1,n);
    quickread(m);
    for(int i=1;i<=m;i++)
    {
        // quickread(opt);
        // quickread(l);
        // quickread(r);
        std::cin>>opt>>l>>r;
        switch(opt)
        {
        case 1:
        	quickwrite(getsum(1,1,n,l,r));
        	break;
        case 2:
        	updata_sqrt(1,1,n,l,r);
        	break;
		}
    }
    return 0;



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
