#include<iostream>
#include<stdio.h>
#include<cstring>
using namespace std;
//调试开关
#define DEBUG

//小数据
#define SMALL

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
const int MAXN=10;
#endif
#ifndef SMALL
const int MAXN=3004;
#endif

int lowbit(int x)
{
    return x&-x;
}

class fenwick2
{
public:
    int n,m;
    int **c;
public:
    fenwick2(int n,int m):n(n),m(m)
    {
        c=new int*[n];
        for(int i=1;i<=n;i++)
            c[i]=new int[m];
    }
    ~fenwick2()
    {
        for(int i=1;i<=n;i++)
        {
            delete[] c[i];
            c[i]=nullptr;
        }
        delete[] c;
        c=nullptr;
    }
    void build(int *pre,int n,int m)
    {
        for(int i=1;i<n;i++)
            for(int j=1;j<m;j++)
                c[i][j]=pre[i*MAXN*2+j]+pre[(i-lowbit(i))*MAXN*2+j-lowbit(j)]
                        -pre[(i-lowbit(i))*MAXN*2+j]-pre[i*MAXN*2+j-lowbit(j)];
    }
    void add(int x,int y,int a)
    {
        for(int i=x;i<n;i+=lowbit(i))
            for(int j=y;j<m;j+=lowbit(j))
                c[i][j]+=a;
    }
    int sum(int x,int y)
    {
        int ret=0;
        for(int i=x;i>0;i-=lowbit(i))
            for(int j=y;j>0;j-=lowbit(j))
                ret+=c[i][j];
        return ret;
    }
    int ask(int x1,int y1,int x2,int y2)
    {
        return sum(x2,y2)-sum(x2,y1-1)-sum(x1-1,y2)+sum(x1-1,y1-1);
    }
};
int a[MAXN*2][MAXN*2];
int n,m;
int &b(int x,int y)
{
    return a[x+y-1][y-x+n];
}
int bx(int x,int y)
{
    return x+y-1;
}
int by(int x,int y)
{
    return y-x+n;
}
int k,x,y,z;
#ifdef MAIN
//主函数
int main()
{
    #ifdef DEBUG
        file_mode();
    #endif
    quickread(m);
    quickread(n);
    fenwick2 fen(2*n,2*m);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            quickread(b(i,j));
    for(int i=1;i<=2*n;i++)
        for(int j=1;j<=2*m;j++)
            a[i][j]+=a[i-1][j];
    for(int i=1;i<=2*n;i++)
        for(int j=1;j<=2*m;j++)
            a[i][j]+=a[i][j-1];
    fen.build(&a[0][0],2*n,2*m);
    
    while(true)
    {
        if(scanf("%d",&k)==EOF)break;
        
        scanf("%d",&y);
        scanf("%d",&x);
        scanf("%d",&z);
        switch(k)
        {
        case 1:
            fen.add(bx(x,y),by(x,y),z);
            break;
        case 2:
            quickwrite(fen.ask(bx(x,y-z),by(x,y-z),bx(x,y+z),by(x,y+z)));
            break;
        }
    }
    #ifdef DEBUG
        for(int i=1;i<=n*2;i++)
        {
            for(int j=1;j<=m*2;j++)
                cout<<a[i][j]<<' ';
            cout<<endl;
        }cout<<endl;
        for(int i=1;i<n*2;i++)
        {
            for(int j=1;j<m*2;j++)
                cout<<fen.c[i][j]<<' ';
            cout<<endl;
        }
    #endif
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

