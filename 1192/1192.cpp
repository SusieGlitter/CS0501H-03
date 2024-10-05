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
const int MAXN=1003;
const int MAXM=102;
#endif

int n,m,map[MAXM][MAXM];
int dis[MAXM][MAXM];
bool visit[MAXM][MAXM];
int x,y,c;
int dx[4]={0,0,1,-1};
int dy[4]={1,-1,0,0};

struct node
{
    int x;
    int y;
    int c;
    int dis;
    node(){}
    node(int x,int y,int c,int dis):x(x),y(y),c(c),dis(dis){}
};

node nodestack0[MAXM*MAXM];
node nodestack1[MAXM*MAXM];
node nodestack2[MAXM*MAXM];
int top0,top1,top2;
node *zero=nodestack0;
node *one=nodestack1;
node *two=nodestack2;

void roll()
{
    top0=top1;
    top1=top2;
    top2=0;
    node *temp=zero;
    zero=one;
    one=two;
    two=temp;
}


#ifdef MAIN
//主函数
int main()
{
    #ifdef DEBUG
        file_mode();
    #endif

    quickread(m);
    quickread(n);
    for(int i=1;i<=m;i++)
        for(int j=1;j<=m;j++)
        {
            visit[i][j]=false;
            dis[i][j]=2100000000;
        }
    for(int i=1;i<=n;i++)
    {
        quickread(x);
        quickread(y);
        quickread(c);
        map[x][y]=c+1;
    }
    zero[++top0]=node(1,1,map[1][1],0);
    while(top0!=0||top1!=0||top2!=0)
    {
        while(top0!=0)
        {
            node now=zero[top0--];
            visit[now.x][now.y]=true;
            if(now.dis>dis[now.x][now.y])continue;
            dis[now.x][now.y]=now.dis;
            for(int di=0;di<4;di++)
            {
                int xt=now.x+dx[di];
                int yt=now.y+dy[di];
                if(visit[xt][yt])continue;
                //同色进0栈
                if(now.c==map[xt][yt])
                {
                    zero[++top0]=node(xt,yt,now.c,now.dis);
                }
                else
                {
                //异色进1栈
                    if(map[xt][yt]!=0)
                        one[++top1]=node(xt,yt,map[xt][yt],now.dis+1);
                //白色进2栈
                    else if(map[now.x][now.y]!=0)
                        two[++top2]=node(xt,yt,now.c,now.dis+2);
                }
            }
        }
        roll();
    }

    if(dis[m][m]==2100000000)
        dis[m][m]=-1;
    quickwrite(dis[m][m]);

    

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