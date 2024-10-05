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

const int BASE=26;
const int MOD=10000019;

int base_pow[4000005];
void Hash_aux(int* base_pow,int base,int mod,int len)
{
    base_pow[0]=1;
    for(int i=1;i<=len;i++)
        base_pow[i]=base_pow[i-1]*base%mod;
}

void Hash_head(int& ha,char new_char,int base=BASE,int mod=MOD)
{
    ha=(ha*base+(new_char-97))%mod;
}
void Hash_tail(int& ha,char new_char,int len,int base=BASE,int mod=MOD)
{
    ha=(ha+(new_char-97)*base_pow[len])%mod;
}
char s[4000005];
int len;
int ha_head,ha_tail;
int ans;
#ifdef MAIN
//主函数
int main()
{
    #ifdef DEBUG
        file_mode();
    #endif
    cin>>s;
    len=strlen(s);
    Hash_aux(base_pow,BASE,MOD,len);

    ans=len;
    for(int i=len-1;i>=0;i--)
    {
        Hash_head(ha_head,s[i]);
        Hash_tail(ha_tail,s[i],len-1-i);
        #ifdef DEBUG
            cout<<ha_head<<' '<<ha_tail<<endl;
        #endif
        if(ha_head==ha_tail)
            ans=min(ans,i);
        #ifdef DEBUG
            cout<<ans<<endl;
        #endif
    }
    quickwrite(ans);

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

