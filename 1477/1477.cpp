#include<iostream>
// #include<stdio.h>
#include<cstring>
using namespace std;
//调试开关
#define DEBUG

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
inline void quickread(int &x);
//快输
inline void quickwrite(int x);

const int MAX_L=1000005;
char target[MAX_L];int m;
int kmpnext[MAX_L];

void KMP_aux()
{
    kmpnext[0]=-1;
    int last;
    for(int curr=0;curr<m;curr++)
    {
        last=kmpnext[curr];
        while(last!=-1&&target[last]!=target[curr])
            last=kmpnext[last];
        kmpnext[curr+1]=last+1;

    }
}

int sta[MAX_L],top;

#ifdef MAIN
//主函数
int main()
{
    #ifdef DEBUG
        file_mode();
    #endif

    cin.get(target,1000000);
    m=strlen(target);
    KMP_aux();
    // for(int i=0;i<m;i++)
    //     quickwrite(kmpnext[i]);
    // cout<<endl;
    int tool=m;
    while(tool>0)
    {
        sta[++top]=tool;
        tool=kmpnext[tool];
    }
    while(top)
        quickwrite(sta[top--]);

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

inline void quickread(int &x)
{
    x=0;
    char c=getchar();
    bool flag(0);
    while(!isdigit(c))flag|=c==45,c=getchar();
    while(isdigit(c))x=(x<<3)+(x<<1)+(c^48),c=getchar();
    flag?x=-x:x;
}
inline void quickwrite(int x)
{
    x<0?x=-x,putchar(45):0;
    static short sta[50],top(0);
    do sta[++top]=x%10,x/=10;while(x);
    while(top)putchar(sta[top--]^48);
    putchar(10);
}
