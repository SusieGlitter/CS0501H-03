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
const int MAXN=100005;
#endif


int n,m;

double a[MAXN];

int mode,x,y;
double k;

struct node
{
    double add_tag=0;
    double sum_1=0;
    double sum_2=0;
}tree[4*MAXN+1];

inline void pushup(int now,int s,int t,int mid,int lson,int rson)
{
    tree[now].sum_1=tree[lson].sum_1+tree[rson].sum_1;
    tree[now].sum_2=tree[lson].sum_2+tree[rson].sum_2;
}

inline void pushdown(int now,int s,int t,int mid,int lson,int rson)
{
    if(tree[now].add_tag==0)return;

    tree[lson].sum_2+=2*tree[now].add_tag*tree[lson].sum_1
                    +(mid-s+1)*tree[now].add_tag*tree[now].add_tag;
    tree[rson].sum_2+=2*tree[now].add_tag*tree[rson].sum_1
                    +(t-mid)*tree[now].add_tag*tree[now].add_tag;

    tree[lson].sum_1+=(mid-s+1)*tree[now].add_tag;
    tree[rson].sum_1+=(t-mid)*tree[now].add_tag;

    tree[lson].add_tag+=tree[now].add_tag;
    tree[rson].add_tag+=tree[now].add_tag;

    tree[now].add_tag=0;
}

void build(int now,int s,int t)
{
    if(s==t)
    {
        tree[now].sum_2=a[s]*a[s];
        tree[now].sum_1=a[s];
        return;
    }
    int mid=(s+t)>>1;
    int lson=2*now;
    int rson=lson+1;
    
    build(lson,s,mid);
    build(rson,mid+1,t);

    pushup(now,s,t,mid,lson,rson);
}

void updata_add(int now,int s,int t,int l,int r,double k)
{
    if(s>r||t<l)return;
    if(s>=l&&t<=r)
    {
        tree[now].sum_2+=2*k*tree[now].sum_1+(t-s+1)*k*k;
        tree[now].sum_1+=(t-s+1)*k;
        tree[now].add_tag+=k;
        return;
    }
    int mid=(s+t)>>1;
    int lson=2*now;
    int rson=lson+1;
    pushdown(now,s,t,mid,lson,rson);
    updata_add(lson,s,mid,l,r,k);
    updata_add(rson,mid+1,t,l,r,k);
    pushup(now,s,t,mid,lson,rson);
}
double getsum_1(int now,int s,int t,int l,int r)
{
    if(s>r||t<l)return 0;
    if(s>=l&&t<=r)
        return tree[now].sum_1;
    int mid=(s+t)>>1;
    int lson=2*now;
    int rson=lson+1;
    pushdown(now,s,t,mid,lson,rson);
    double ret=getsum_1(lson,s,mid,l,r)+getsum_1(rson,mid+1,t,l,r);
    pushup(now,s,t,mid,lson,rson);
    return ret;
}
double getsum_2(int now,int s,int t,int l,int r)
{
    if(s>r||t<l)return 0;
    if(s>=l&&t<=r)
        return tree[now].sum_2;
    int mid=(s+t)>>1;
    int lson=2*now;
    int rson=lson+1;
    pushdown(now,s,t,mid,lson,rson);
    double ret=getsum_2(lson,s,mid,l,r)+getsum_2(rson,mid+1,t,l,r);
    pushup(now,s,t,mid,lson,rson);
    return ret;
}


#ifdef MAIN
//主函数
int main()
{
    #ifdef DEBUG
        file_mode();
    #endif

    std::cin>>n;
    std::cin>>m;

    for(int i=1;i<=n;i++)
        std::cin>>a[i];
    build(1,1,n);

    for(int i=1;i<=m;i++)
    {
        quickread(mode);
        switch (mode)
        {
        case 1:
            std::cin>>x;
            std::cin>>y;
            std::cin>>k;
            updata_add(1,1,n,x,y,k);
            break;
        case 2:
            std::cin>>x;
            std::cin>>y;
            quickwrite((int)((double)(getsum_1(1,1,n,x,y)*100)/(y-x+1)));
            break;
        case 3:
            std::cin>>x;
            std::cin>>y;
            double Ex=(double)(getsum_1(1,1,n,x,y))/(y-x+1);
            double Ex2=(double)(getsum_2(1,1,n,x,y))/(y-x+1);
            quickwrite((int)((Ex2-Ex*Ex)*100));
            break;
        }
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

