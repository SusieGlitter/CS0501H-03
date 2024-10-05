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

int ans[MAXN];

int l[MAXN],r[MAXN],val[MAXN];

struct node
{
    int lazytag=1;
    int lcm=1;
    int gcd=0;
}tree[4*MAXN+1];

int gcd(int a,int b)
{
    return b?gcd(b,a%b):a;
}
int lcm(int a,int b)
{
    return a*b/gcd(a,b);
}

inline void pushup(int now,int s,int t,int mid,int lson,int rson)
{
    tree[now].lcm=lcm(tree[lson].lcm,tree[rson].lcm);
}

inline void pushdown(int now,int s,int t,int mid,int lson,int rson)
{
    if(tree[now].lazytag==1)return;

    tree[lson].lcm=lcm(tree[now].lazytag,tree[lson].lcm);
    tree[rson].lcm=lcm(tree[now].lazytag,tree[rson].lcm);

    tree[lson].lazytag=lcm(tree[now].lazytag,tree[lson].lazytag);
    tree[rson].lazytag=lcm(tree[now].lazytag,tree[rson].lazytag);

    tree[now].lazytag=1;
}

void build(int now,int s,int t)
{
    if(s==t)
    {
        return;
    }
    int mid=(s+t)>>1;
    int lson=2*now;
    int rson=lson+1;
    
    build(lson,s,mid);
    build(rson,mid+1,t);

    pushup(now,s,t,mid,lson,rson);
}

void update(int now,int s,int t,int l,int r,int k)
{
    if(s>r||t<l)return;
    if(s>=l&&t<=r)
    {
        tree[now].lcm=lcm(tree[now].lcm,k);
        tree[now].lazytag=lcm(tree[now].lazytag,k);
        return;
    }
    int mid=(s+t)>>1;
    int lson=2*now;
    int rson=lson+1;
    pushdown(now,s,t,mid,lson,rson);
    update(lson,s,mid,l,r,k);
    update(rson,mid+1,t,l,r,k);
    pushup(now,s,t,mid,lson,rson);
}
void allpushdown(int now,int s,int t)
{
    if(s==t)
    {
        ans[s]=tree[now].lcm;
        return;
    }
    int mid=(s+t)>>1;
    int lson=2*now;
    int rson=lson+1;
    pushdown(now,s,t,mid,lson,rson);
    allpushdown(lson,s,mid);
    allpushdown(rson,mid+1,t);
}
int log2[MAXN];
int st[20][MAXN];
void st_build()
{
    log2[1]=0;
    for(int i=2;i<=n;i++)log2[i]=log2[i/2]+1;
    for(int j=1;j<=n;j++)st[0][j]=ans[j];
    for(int i=1;i<20;i++)
        for(int j=1;j+(1<<i)-1<=n;j++)
            st[i][j]=gcd(st[i-1][j],st[i-1][j+(1<<(i-1))]);
}

int st_get(int s,int t)
{
    int sti=log2[t-s+1];
    return gcd(st[sti][s],st[sti][t-(1<<sti)+1]);
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

    build(1,1,n);

    for(int i=1;i<=m;i++)
    {
        quickread(l[i]);
        quickread(r[i]);
        quickread(val[i]);
        update(1,1,n,l[i],r[i],val[i]);
    }
    allpushdown(1,1,n);

    st_build();

    for(int i=1;i<=m;i++)
    {
        if(val[i]!=st_get(l[i],r[i]))
        {
            quickwrite(-1);
            #ifdef DEBUG
                fclose(stdin);
            #endif
            return 0;
        }
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
    putchar(32);
}

