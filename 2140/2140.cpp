#include<iostream>
#include<stdio.h>
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
template<typename T>
inline void quickread(T &x);
//快输
template<typename T>
inline void quickwrite(T x);

const int MAXL=1000005;
char s[MAXL],t[MAXL];
int len_s,len_t;

int queue_s[MAXL],queue_t[MAXL];
int stack[MAXL],top=0;
int head_s=1,head_t=1;
int tail_s=0,tail_t=0;

const long long BASE=1331;
const long long MOD=100000007;
long long base[MAXL];
void get_base_pow()
{
    base[0]=1;
    for(int i=1;i<MAXL;i++)
        base[i]=base[i-1]*BASE%MOD;
}

long long hash_pre_s[MAXL];
long long hash_pre_t[MAXL];
void get_hash_pre()
{
    hash_pre_s[0]=0;
    for(int i=1;i<=len_s;i++)
        hash_pre_s[i]=(hash_pre_s[i-1]*BASE+s[i])%MOD;
    
    hash_pre_t[0]=0;
    for(int i=1;i<=len_t;i++)
        hash_pre_t[i]=(hash_pre_t[i-1]*BASE+t[i])%MOD;
}
long long hash_range(long long *hash_pre,int i,int j)
{
    if(i>j)return 0;
    return ((hash_pre[j]-hash_pre[i-1]*base[j-i+1])%MOD+MOD)%MOD;
}

#ifdef MAIN
//主函数
int main()
{
    #ifdef DEBUG
        file_mode();
    #endif
    scanf("%s",s+1);
    scanf("%s",t+1);
    len_s=strlen(s+1);
    len_t=strlen(t+1);
    get_base_pow();
    get_hash_pre();

    // for(int i=1;i<=len_s;i++)
    // {
    //     quickwrite(hash_range(hash_pre_s,i,i));
    // }cout<<endl;
    for(int i=1;i<=len_t;i++)
    {
        if(t[i]=='?')
            queue_t[++tail_t]=i;
        if(s[i]=='?')
            queue_s[++tail_s]=i;
    }

    for(int pos=1;pos<=len_s-len_t+1;pos++)
    {
        top=0;
        stack[++top]=pos-1;
        int pt=head_t;
        int ps=head_s;
        while(pt<=tail_t&&ps<=tail_s)
        {
            if(queue_s[ps]==queue_t[pt]+pos-1)
            {
                stack[++top]=queue_s[ps];
                ps++;
                pt++;
                continue;
            }
            if(queue_s[ps]>queue_t[pt]+pos-1)
            {
                stack[++top]=queue_t[pt]+pos-1;
                pt++;
                continue;
            }
            if(queue_s[ps]<queue_t[pt]+pos-1)
            {
                stack[++top]=queue_s[ps];
                ps++;
                continue;
            }

        }
        while(ps<=tail_s)stack[++top]=queue_s[ps++];
        while(pt<=tail_t)stack[++top]=queue_t[pt++]+pos-1;

        stack[++top]=pos+len_t;

        bool pair=true;
        for(int i=2;i<=top;i++)
        {
            if(hash_range(hash_pre_s,stack[i-1]+1,stack[i]-1)!=
                hash_range(hash_pre_t,stack[i-1]-pos+1+1,stack[i]-pos+1-1))
            {
                pair=false;
                break;
            }
        }
        if(pair)
            quickwrite(pos-1);
        
        if(s[pos]=='?')
            ++head_s;
        if(s[pos+len_t]=='?')
            queue_s[++tail_s]=pos+len_t;
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

