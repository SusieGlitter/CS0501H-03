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

int a[MAXN];

int mode,x,d;
enum Elazytag
{
    none=0,empty,full
};

struct node
{
    Elazytag lazytag=none;
    int l_empty,r_empty,max_empty;
}tree[4*MAXN+1];

inline void pushup(int now,int s,int t,int mid,int lson,int rson)
{
    tree[now].l_empty=tree[lson].l_empty;
    tree[now].r_empty=tree[rson].r_empty;
    if(tree[now].l_empty==mid-s+1)
        tree[now].l_empty+=tree[rson].l_empty;
    if(tree[now].r_empty==t-mid)
        tree[now].r_empty+=tree[lson].r_empty;
    
    tree[now].max_empty=std::max(std::max(tree[lson].max_empty,tree[rson].max_empty),tree[lson].r_empty+tree[rson].l_empty);
}

inline void pushdown(int now,int s,int t,int mid,int lson,int rson)
{
    if(tree[now].lazytag==none)return;
    if(tree[now].lazytag==full)
    {
        tree[lson].max_empty=0;
        tree[lson].l_empty=0;
        tree[lson].r_empty=0;

        tree[rson].max_empty=0;
        tree[rson].l_empty=0;
        tree[rson].r_empty=0;
    }
    else
    {
        tree[lson].max_empty=mid-s+1;
        tree[lson].l_empty=tree[lson].max_empty;
        tree[lson].r_empty=tree[lson].max_empty;

        tree[rson].max_empty=t-mid;
        tree[rson].l_empty=tree[rson].max_empty;
        tree[rson].r_empty=tree[rson].max_empty;
    }
    tree[lson].lazytag=tree[now].lazytag;
    tree[rson].lazytag=tree[now].lazytag;
    tree[now].lazytag=none;
}

void build(int now,int s,int t)
{
    if(s==t)
    {
        tree[now].max_empty=1;
        tree[now].l_empty=1;
        tree[now].r_empty=1;
        return;
    }
    int mid=(s+t)>>1;
    int lson=2*now;
    int rson=lson+1;
    build(lson,s,mid);
    build(rson,mid+1,t);

    pushup(now,s,t,mid,lson,rson);
}

void update(int now,int s,int t,int l,int r,Elazytag lazytag)
{
    if(s>r||t<l)return;
    if(s>=l&&t<=r)
    {
        if(lazytag==none)return;
        if(lazytag==full)
        {
            tree[now].max_empty=0;
            tree[now].l_empty=0;
            tree[now].r_empty=0;
        }
        else
        {
            tree[now].max_empty=t-s+1;
            tree[now].l_empty=tree[now].max_empty;
            tree[now].r_empty=tree[now].max_empty;
        }
        tree[now].lazytag=lazytag;
        return;
    }

    int mid=(s+t)>>1;
    int lson=2*now;
    int rson=lson+1;

    pushdown(now,s,t,mid,lson,rson);

    update(lson,s,mid,l,r,lazytag);
    update(rson,mid+1,t,l,r,lazytag);

    pushup(now,s,t,mid,lson,rson);
}
int find(int now,int s,int t,int target)
{
    if(s==t)
        return s;
    
    int mid=(s+t)>>1;
    int lson=2*now;
    int rson=lson+1;

    pushdown(now,s,t,mid,lson,rson);

    if(tree[lson].max_empty>=target)
        return find(lson,s,mid,target);
    else if(tree[lson].r_empty+tree[rson].l_empty>=target)
        return mid-tree[lson].r_empty+1;
    return find(rson,mid+1,t,target);
}


#ifdef MAIN
//主函数
int main()
{
    #ifdef DEBUG
        file_mode();
    #endif

    quickread(n);quickread(m);
    build(1,1,n);

    for(int i=1;i<=m;i++)
    {
        quickread(mode);
        switch (mode)
        {
        case 1:
            quickread(d);
            if(tree[1].max_empty<d)
                quickwrite(0);
            else
            {
                int pos=find(1,1,n,d);
                quickwrite(pos);
                update(1,1,n,pos,pos+d-1,full);
            }
            break;
        case 2:
            quickread(x);
            quickread(d);
            update(1,1,n,x,x+d-1,empty);
            break;
        default:
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

