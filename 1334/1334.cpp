#include<iostream>
#include<stdio.h>
#include<cstring>
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
const int MAXN=10000007;
#endif

int n,m,k;
const int MAXMEM=20;
std::string rubbish,end=">";
class myClass
{
public:
    std::string name;
    std::string temp[MAXMEM];
    int tempcnt;
    class myFriend
    {
    public:
        std::string name;
        std::string uniq[MAXMEM];
        int uniqcnt;
        std::string list[MAXMEM];
        int listcnt;
    };
    myFriend frie[MAXMEM];
    int friecnt;
    void read()
    {
        std::string rubbish,end=">";
        tempcnt=0;
        std::cin>>rubbish;
        do
        {
            std::cin>>temp[tempcnt++];
        }while(temp[tempcnt-1]!=end);
        tempcnt--;
        std::cin>>name;

        quickread(friecnt);
        for(int i=0;i<friecnt;i++)
        {
            frie[i].uniqcnt=0;
            std::cin>>rubbish;
            do
            {
                std::cin>>frie[i].uniq[frie[i].uniqcnt++];
            }while(frie[i].uniq[frie[i].uniqcnt-1]!=end);
            frie[i].uniqcnt--;

            std::cin>>frie[i].name;

            
            frie[i].listcnt=0;
            std::cin>>rubbish;
            do
            {
                std::cin>>frie[i].list[frie[i].listcnt++];
            }while(frie[i].list[frie[i].listcnt-1]!=end);
            frie[i].listcnt--;


        }
        
    }
}classlist[101];


std::string aname;
std::string atemp[MAXMEM];
int atempcnt;
std::string bname;
std::string btemp[MAXMEM];
int btempcnt;

bool check()
{
    // class定位
    for(int b=0;b<n;b++)
    {
        if(classlist[b].name!=bname||classlist[b].tempcnt!=btempcnt)
            continue;

        // frie定位
        for(int a=0;a<classlist[b].friecnt;a++)
        {
            bool isfrie=true;
            if(classlist[b].frie[a].name!=aname||classlist[b].frie[a].listcnt!=atempcnt)
                continue;
            // 枚举参数
            for(int i=0;i<classlist[b].frie[a].listcnt;i++)
            {
                // bool haverule=false;
                // 尝试在temp中寻找
                for(int j=0;j<classlist[b].tempcnt;j++)
                {
                    if(classlist[b].frie[a].list[i]!=classlist[b].temp[j])
                        continue;
                    // haverule=true;
                    if(atemp[i]!=btemp[j])
                    {
                        isfrie=false;
                        break;
                    }
                }
                if(!isfrie)break;
                // 寻找相同的
                for(int j=0;j<i;j++)
                {
                    if(classlist[b].frie[a].list[i]!=classlist[b].frie[a].list[j])
                        continue;
                    // haverule=true;
                    if(atemp[i]!=atemp[j])
                    {
                        isfrie=false;
                        break;
                    }
                }
                if(!isfrie)break;
            }
            if(isfrie)
                return true;
        }
    }
    return false;
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

    for(int i=0;i<n;i++)
    {
        classlist[i].read();
    }

    for(int i=1;i<=m;i++)
    {

        std::cin>>aname;
        atempcnt=0;
        std::cin>>rubbish;
        do
        {
            std::cin>>atemp[atempcnt++];
        }while(atemp[atempcnt-1]!=end);
        atempcnt--;

        std::cin>>bname;
        btempcnt=0;
        std::cin>>rubbish;
        do
        {
            std::cin>>btemp[btempcnt++];
        }while(btemp[btempcnt-1]!=end);
        btempcnt--;

        if(check())
            std::cout<<"Yes"<<std::endl;
        else
            std::cout<<"No"<<std::endl;
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

