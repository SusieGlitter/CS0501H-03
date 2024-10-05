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

int n,m,map[MAXM][MAXM],id[MAXM][MAXM];
int x,y,c;
int dx[4]={0,0,1,-1};
int dy[4]={1,-1,0,0};
int c42i[6]={0,0,0,1,1,2};
int c42j[6]={1,2,3,2,3,3};
// dsu
int dsu_fat[MAXM*MAXM];
int dsu_siz[MAXM*MAXM];

void dsu_pre()
{
    for(int i=1;i<=n;i++)
    {
        dsu_fat[i]=i;
        dsu_siz[i]=1;
    }
}

int dsu_find(int x)
{
    return dsu_fat[x]==x?x:dsu_fat[x]=dsu_find(dsu_fat[x]);
}

void dsu_unite(int x,int y)
{
    x=dsu_find(x);
    y=dsu_find(y);
    if(x==y)return;
    if(dsu_siz[x]<dsu_siz[y])
        std::swap(x,y);
    dsu_fat[y]=x;
    dsu_siz[x]+=dsu_siz[y];
}

int supernode[5*MAXN],supernode_cnt;

int findsupernode(int x,int y)
{
    int fat=dsu_find(id[x][y]);
    if(supernode[fat]==0)
        supernode[fat]=++supernode_cnt;
    supernode[id[x][y]]=supernode[fat];
    return supernode[fat];

}

int head[5*MAXN],next[10*MAXN],edto[10*MAXN],ecnt;
void ins(int s,int t)
{
    next[++ecnt]=head[s];
    head[s]=ecnt;
    edto[ecnt]=t;
}
void ins2(int s,int t)
{
    ins(s,t);
    ins(t,s);
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
    int iid=0;
    for(int i=1;i<=m;i++)
        for(int j=1;j<=m;j++)
            id[i][j]=++iid;
    for(int i=1;i<=n;i++)
    {
        quickread(x);
        quickread(y);
        quickread(c);
        map[x][y]=c+1;
        for(int k=0;k<4;k++)
            if(map[x+dx[k]][y+dy[k]]==map[x][y])
                dsu_unite(id[x+dx[k]][y+dy[k]],id[x][y]);
    }

    //色块编号
    for(int i=1;i<=m;i++)
        for(int j=1;j<=m;j++)
            if(map[i][j]!=0)
                findsupernode(i,j);
    
    //颜色之间连线
    for(int i=1;i<=m;i++)
        for(int j=1;j<=m;j++)
            if(map[i][j]!=0)
                for(int d=0;d<4;d++)
                {
                    int x=i+dx[d];
                    int y=j+dy[d];
                    if(map[x][y]!=0&&findsupernode(i,j)!=findsupernode(x,y))
                        ins2(findsupernode(i,j),findsupernode(x,y));
                }
    
    //无色链接不同色块
    for(int i=1;i<=m;i++)
        for(int j=1;j<=m;j++)
            if(map[i][j]==0)
                for(int c42=0;c42<6;c42++)
                {
                    int x1=i+dx[c42i[c42]];
                    int x2=i+dx[c42j[c42]];
                    int y1=j+dy[c42i[c42]];
                    int y2=j+dy[c42j[c42]];
                    if(map[x1][y1]!=0&&map[x2][y2]!=0&&findsupernode(x1,y1)!=findsupernode(x2,y2))
                    {
                        ++supernode_cnt;
                        ins2(supernode_cnt,findsupernode(x1,y1));
                        ins2(supernode_cnt,findsupernode(x2,y2));
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