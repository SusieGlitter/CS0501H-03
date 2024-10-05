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
inline void quickread(int &x);
//快输
inline void quickwrite(int x);

const int BASE=97;
const int MOD=5000011;

int base_pow[12];
void Hash_aux(int* base_pow,int base,int mod)
{
    base_pow[0]=1;
    for(int i=1;i<=10;i++)
        base_pow[i]=base_pow[i-1]*base%mod;
}
int Hash(char* s,int* base_pow,int mod)
{
    int ret=0,len=strlen(s);
    for(int i=0;i<len;i++)
        ret=(ret+base_pow[i]*s[i])%mod;
    return ret;
}
int n,m;
char words[1005][12];
char passa[100005][12];
int bin_id[MOD+2];
int bin[1001];
int ans1=0,ans2=2100000000;

int& cnt(char* s)
{
    return bin[bin_id[Hash(s,base_pow,MOD)]];
}

int have=0;

void ins(int i)
{
    if(cnt(passa[i])==0)
        have++;
    cnt(passa[i])++;
}
void del(int i)
{
    cnt(passa[i])--;
    if(cnt(passa[i])==0)
        have--;
}

#ifdef MAIN
//主函数
int main()
{
    #ifdef DEBUG
        file_mode();
    #endif

    Hash_aux(base_pow,BASE,MOD);
    quickread(n);
    for(int i=1;i<=n;i++)
    {
        cin>>words[i];
        bin_id[Hash(words[i],base_pow,MOD)]=i;
    }
    quickread(m);
    for(int i=1;i<=m;i++)
    {
        cin>>passa[i];
        if(cnt(passa[i])==0)
            ans1++;
        cnt(passa[i])++;
    }
    for(int i=1;i<=n;i++)
        cnt(words[i])=0;
    int l=1,r=1;
    while(r!=m+1)
    {
        while(r!=m+1&&have<ans1)
            ins(r++);
        while(l!=m+1&&have==ans1)
            del(l++);
        ans2=min(ans2,r-l+1);
    }

    quickwrite(ans1);
    quickwrite(ans2);

    #ifdef DEBUG
        for(int i=1;i<=n;i++)
            cout<<Hash(words[i],base_pow,MOD)<<endl;
        cout<<endl;
        for(int i=1;i<=m;i++)
            cout<<Hash(passa[i],base_pow,MOD)<<endl;
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

