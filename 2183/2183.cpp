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
const int MAXN=102;
#endif
#ifndef SMALL
const int MAXN=200005;
#endif


struct node
{
    int data;
    int id;
    int rank;
}nums[MAXN],tool[MAXN];


void mergesort(int s,int t)
{
    if(s==t)return;
    int mid=(s+t)>>1;
    mergesort(s,mid);
    mergesort(mid+1,t);
    int i=s,j=mid+1,k=s;
    while(i<=mid||j<=t)
        if(i<=mid&&(j>t||nums[i].data<nums[j].data))
            tool[k++]=nums[i++];
        else
            tool[k++]=nums[j++];
    for(int i=s;i<=t;i++)
        nums[i]=tool[i];
}

int n,m;
int a[MAXN],ha[MAXN];
int bin[MAXN];
int L[MAXN],len[MAXN];
int l,r;
int ans,subans;

int search(int l,int r)
{
    // for(int i=l;i<=r;i++)
    //     if(L[i]>=l)
    //         return i;
    // return r+1;

    if(L[r]<l)return r+1;
    int s=l,t=r;
    while(s<t)
    {
        int mid=(s+t)>>1;
        if(L[mid]<l)
            s=mid+1;
        else
            t=mid;
    }
    return s;
}

const int MAXINDEX=30;
int Index;
int Log[MAXN];
int st[MAXINDEX][MAXN];
int maxlen(int l,int r)
{
    // int ret=0;
    // for(int i=l;i<=r;i++)
    //     ret=max(ret,len[i]);
    // return ret;

    if(l>r)return 0;
    int ind=Log[r-l+1];
    return max(st[ind][l],st[ind][r-(1<<ind)+1]);
}

void stinit(int n)
{
    Log[1]=0;
    for(int i=2;i<=n;i++)
        Log[i]=Log[i/2]+1;
    
    Index=Log[n]+1;
    
    for(int j=1;j<=n;j++)
        st[0][j]=len[j];
    for(int i=1;i<=Index;i++)
        for(int j=1;j+(1<<i)-1<=n;j++)
            st[i][j]=max(st[i-1][j],st[i-1][j+(1<<(i-1))]);
}

#ifdef MAIN
//主函数
int main()
{
    #ifdef DEBUG
        file_mode();
    #endif

    quickread(n);
    quickread(m);

    for(int i=1;i<=n;i++)
    {
        quickread(a[i]);
        nums[i].data=a[i];
        nums[i].id=i;
    }
    mergesort(1,n);
    for(int i=1;i<=n;i++)
    {
        if(nums[i].data!=nums[i-1].data)
            nums[i].rank=nums[i-1].rank+1;
        else
            nums[i].rank=nums[i-1].rank;
        ha[nums[i].id]=nums[i].rank;
    }

    l=1;
    for(r=1;r<=n;r++)
    {
        bin[ha[r]]++;
        if(bin[ha[r]]==2)
            while(bin[ha[r]]==2)
                bin[ha[l++]]--;
        L[r]=l;
        len[r]=r-l+1;
    }
    stinit(n);
    for(int i=1;i<=m;i++)
    {
        ans=subans=0;
        quickread(l);l++;
        quickread(r);r++;
        
        int m=search(l,r);
        subans=max(m-l,maxlen(m,r));
        ans=max(ans,subans);
        quickwrite(ans);
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

