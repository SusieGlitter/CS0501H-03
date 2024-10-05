//参考：https://www.luogu.com.cn/article/ky9xnld6 Z函数
//参考：https://www.luogu.com.cn/article/bti82yh8 本题算法
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

const int MAX_L=30000005;
char source[MAX_L];int slen;
int z[MAX_L];

void getZ()
{
    //z[0]
    z[0]=slen;
    int now=0;//now是t上的位置 这里t即是s
    //z[1]
    while(now+1<slen&&source[now]==source[now+1])
        now++;
    z[1]=now;
    //z[i]
    int p=1;//p代表最长匹配的起点
    for(int i=2;i<slen;i++)
    {
        if(i+z[i-p]<p+z[p])//未超过最长匹配
            z[i]=z[i-p];
        else
        {
            now=max(p+z[p]-i,0);
            while(now+1<slen&&source[now]==source[now+i])
                now++;
            z[i]=now;
            p=i;//成为最佳匹配
        }
    }

    //留出C
    for(int i=0;i<slen;i++)
        if(i+z[i]==slen)
            z[i]--;
}

int pre_cnt[50],suf_cnt[50];
int pre_odd,suf_odd,all_odd;

int tr[30];

inline int lowbit(int x)
{
    return x&-x;
}
void update(int x)
{
    while(x<=27)
    {
        tr[x]++;
        x+=lowbit(x);
    }
}
int getsum(int x)
{
    int ret=0;
    while(x>0)
    {
        ret+=tr[x];
        x-=lowbit(x);
    }
    return ret;
}
void init()
{
    for(int i=0;i<26;i++)
        suf_cnt[i]=pre_cnt[i]=tr[i]=0;
    pre_odd=suf_odd=all_odd=0;

    //桶
    for(int i=0;i<slen;i++)
        suf_cnt[source[i]-'a']++;
    for(int i=0;i<26;i++)
        if(suf_cnt[i]%2)
            all_odd++;
    suf_odd=all_odd;
}

long long solve()
{
    long long ans=0;
    //维护前缀后缀
    for(int i=0;i<slen;i++)
    {
        suf_odd+=(((suf_cnt[source[i]-'a']--)%2)?-1:1);
        pre_odd+=(((pre_cnt[source[i]-'a']++)%2)?-1:1);
        if(i!=0&&i!=slen-1)//ABC非空
        {
            long long maxCycle=z[i+1]/(i+1)+1;
            long long Cycle_odd=maxCycle-maxCycle/2;
            long long Cycle_even=maxCycle/2;
            ans+=Cycle_odd*(getsum(suf_odd+1))
                +Cycle_even*getsum(all_odd+1);
        }
        update(pre_odd+1);
    }

    return ans;
}
int n;
#ifdef MAIN
//主函数
int main()
{
    #ifdef DEBUG
        file_mode();
    #endif
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        getchar();
        cin>>source;
        slen=strlen(source);
        getZ();
        init();
        cout<<solve()<<endl;
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

