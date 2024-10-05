#include<iostream> 
#include<stdio.h>
#include<cstring> 
#include<map>
#include<vector>
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

const int MAXN=1003;
const int MAXM=10004;

string types[5]={"Can not Fetch","Private","Protected","Public","None"};
// None 4
// public 3
// protected 2
// private 1
// Can not Fetch 0

map<string,int> classmap,membermap,typemap;
int membercount=0;
class Class
{
public:
    vector<int> classpublic;
    vector<int> classprotected;
    vector<int> classprivate;
}classes[MAXN];
class Member
{
public:
    int belong;
    int type;
}members[MAXM];

void ins(int son,int fat,int type)
{
    switch (type)
    {
    case 3:
        classes[son].classpublic.push_back(fat);
        break;
    case 2:
        classes[son].classprotected.push_back(fat);
        break;
    case 1:
        classes[son].classprivate.push_back(fat);
        break;
    }
}

int search(int now,const int &targetclass,const int &targetmember)
{
    if(now==targetclass)
        return members[targetmember].type;
    int ret=4;
    for(auto son:classes[now].classpublic)
    {
        int res=search(son,targetclass,targetmember);
        if(res!=4)
            ret=min(ret,min(res,3));
        if(res==1)
            ret=0;

    }
    for(auto son:classes[now].classprotected)
    {
        int res=search(son,targetclass,targetmember);
        if(res!=4)
            ret=min(ret,min(res,2));
        if(res==1)
            ret=0;

    }
    for(auto son:classes[now].classprivate)
    {
        int res=search(son,targetclass,targetmember);
        if(res!=4)
            ret=min(ret,min(res,1));
        if(res==1)
            ret=0;

    }
    return ret;
}

int n,m;
string s1,s2,s3;
int k0,k1;

#ifdef MAIN
//主函数
int main()
{
    #ifdef DEBUG
        file_mode();
    #endif
    typemap.insert(pair<string,int>("public",3));
    typemap.insert(pair<string,int>("protected",2));
    typemap.insert(pair<string,int>("private",1));

    quickread(n);
    for(int i=1;i<=n;i++)
    {
        cin>>s1;
        classmap.insert(pair<string,int>(s1,i));
        quickread(k0);
        for(int j=1;j<=k0;j++)
        {
            cin>>s2>>s3;
            ins(i,classmap.find(s3)->second,typemap.find(s2)->second);
        }
        quickread(k1);
        for(int j=1;j<=k1;j++)
        {
            cin>>s2>>s3;
            membermap.insert(pair<string,int>(s3,++membercount));
            members[membercount].belong=i;
            members[membercount].type=typemap.find(s2)->second;
        }
    }

    quickread(m);
    for(int i=1;i<=m;i++)
    {
        cin>>s1>>s2;
        int sourceid=classmap.find(s1)->second;
        int memberid=membermap.find(s2)->second;
        int targetid=members[memberid].belong;
        int ans=members[memberid].type;
        if(sourceid!=targetid)
        {
            ans=search(sourceid,targetid,memberid);
        }
        cout<<types[ans]<<endl;
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

