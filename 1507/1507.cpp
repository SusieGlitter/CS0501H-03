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
inline void quickwrite(int x,const char seg);

const int MAX_L=1000005;
char source[MAX_L];
char target[MAX_L];
int kmpnext[MAX_L];

void KMP_aux(char* target,int* next)
{
    next[0]=-1;
    int last;
    int target_len=strlen(target);
    for(int curr=0;curr<target_len;curr++)
    {
        last=next[curr];
        while(last!=-1&&target[last]!=target[curr])
            last=next[last];
        next[curr+1]=last+1;

    }
}
void KMP(char* source,char* target,int* next)
{
    int source_len=strlen(source);
    int target_len=strlen(target);
    int target_pos=0;
    for(int source_pos=0;source_pos<source_len;source_pos++)
    {
        while(target_pos!=-1&&target[target_pos]!=source[source_pos])
            target_pos=next[target_pos];
        target_pos++;
        if(target_pos==target_len)
            quickwrite(source_pos-target_len+2,'\n');
    }
}


#ifdef MAIN
//主函数
int main()
{
    #ifdef DEBUG
        file_mode();
    #endif

    cin>>source;
    cin>>target;
    KMP_aux(target,kmpnext);
    KMP(source,target,kmpnext);
    // for(int i=0;i<m;i++)
    //     quickwrite(kmpnext[i]);
    // cout<<endl;
    
    for(int i=0;i<strlen(target);i++)
        quickwrite(kmpnext[i+1],' ');


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
inline void quickwrite(int x,const char seg)
{
    x<0?x=-x,putchar(45):0;
    static short sta[50],top(0);
    do sta[++top]=x%10,x/=10;while(x);
    while(top)putchar(sta[top--]^48);
    putchar(seg);
}

