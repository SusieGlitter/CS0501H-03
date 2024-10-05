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
const int MAXN=1003;
#endif

int a, b, m, n;
long long h[MAXN][MAXN];
long long maxi[MAXN][MAXN],mini[MAXN][MAXN];
long long maxQueue[MAXN], minQueue[MAXN];
int maxHead, maxTail, minHead, minTail;
#ifdef MAIN
//主函数
int main()
{
    #ifdef DEBUG
        file_mode();
    #endif
    quickread(a);
    quickread(b);
    quickread(m);
    quickread(n);
    for (int i = 1; i <= a; i++)
        for (int j = 1; j <= b; j++)
            quickread(h[i][j]);

    for (int i = 1; i <= a; i++)
    {
        maxHead = minHead = 0;
        maxTail = minTail = -1;
        for (int j = 1; j <= n; j++)
        {
            while (maxHead <= maxTail && h[i][maxQueue[maxTail]] > h[i][j])maxTail--;
            while (minHead <= minTail && h[i][minQueue[minTail]] < h[i][j])minTail--;
            maxQueue[++maxTail]=j;
            minQueue[++minTail]=j;
        }
        maxi[i][1]=h[i][minQueue[minHead]];
        mini[i][1]=h[i][maxQueue[maxHead]];

        for(int j=2;j+n-1 <= b ;j++)
        {
            while(maxHead <= maxTail && maxQueue[maxHead] < j)maxHead++;
            while(minHead <= minTail && minQueue[minHead] < j)minHead++;

            while (maxHead <= maxTail && h[i][maxQueue[maxTail]] > h[i][j+n-1])maxTail--;
            while (minHead <= minTail && h[i][minQueue[minTail]] < h[i][j+n-1])minTail--;

            maxQueue[++maxTail]=j+n-1;
            minQueue[++minTail]=j+n-1;

            maxi[i][j]=h[i][minQueue[minHead]];
            mini[i][j]=h[i][maxQueue[maxHead]];

        }
    }
    long long ans=10000000000012;

    for(int i=1 ; i+m-1 <=a ;i++){
        for(int j=1;j+n-1 <= b;j++){
            long long submaxi=-1;
            long long submini = 10000000000012;

            for(int k=i;k <= i+m-1 ;k++){
                submaxi = max(submaxi , maxi[k][j]);
                submini = min(submini , mini[k][j]);
            }

            ans=min(ans , abs(submaxi-submini));
//            cout<<ans<<" ";
        }
    }

    cout<<endl<<ans;


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

