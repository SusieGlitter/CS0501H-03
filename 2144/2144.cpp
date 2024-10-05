#include<iostream>
#include<stdio.h>
#include<cstring>
using namespace std;
//调试开关
// #define DEBUG

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

class InNode
{
private:
    long long a,b,stage;
public:
    InNode(long long a=0,long long b=0,long long stage=0):a(a),b(b),stage(stage){}
    void nextStage(){stage++;}
    long long getStage(){return stage;}
    long long geta(){return a;}
    long long getb(){return b;}
};
class RetNode
{
private:
    long long ret;
public:
    long long getRet(){return ret;}
    void setRet(long long x){ret=x;}
}ret;
const int MAXD=10000; 
class Stack
{
private:
    InNode stack[MAXD];
    int len=0;
public:
    void push(InNode x)
    {
        stack[++len]=x;
    }
    InNode pop()
    {
        return stack[len--];
    }
    InNode top_debug()
    {
        InNode temp=stack[len];
        return temp;
    }
    InNode top()
    {
        InNode temp=stack[len];
        stack[len].nextStage();
        return temp;
    }
    bool empty()
    {
        return len==0;
    }
}stk;

long long a,b;

#ifdef MAIN
//主函数
int main()
{
    #ifdef DEBUG
        file_mode();
    #endif
    cin>>a>>b;
    if(a<b)swap(a,b);
    stk.push(InNode(a,b,0));
    while(!stk.empty())
    {
        InNode curr=stk.top();
        if(curr.getStage()==0)
        {
            if(curr.getb())
                stk.push(InNode(curr.getb(),curr.geta()%curr.getb(),0));
            else
                ret.setRet(curr.geta());
        }
        else if(curr.getStage()==1)
        {
            RetNode newRet=RetNode();
            newRet.setRet(ret.getRet());
            stk.pop();
        }
    }
    cout<<ret.getRet();

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

