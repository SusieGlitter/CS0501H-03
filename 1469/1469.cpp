#include<iostream>
using namespace std;

#define USE_OS

//调试开关
#define DEBUG

//主函数开关
#define MAIN

#ifdef DEBUG

    #include<direct.h>
    #include <fstream>
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

class error : public std::exception {
private:
    std::string msg;

public:
    explicit error(const char *_msg_) : msg(_msg_) {}

    const char *toString() {
        return msg.c_str();
    }
};

template<typename T>
class ArrayList
{
private:
    T *data;
    int length;
public:
    ArrayList():length(0),data(nullptr){}

    ArrayList(int length):length(length)
    {
        if(length<0)throw error("invalid length");
        data=new T[length];
    }

    //这里也有一个const，因为arr可能是const
    ArrayList(const T* arr,int length):length(length)
    {
        //绷不住了，怎么length也能小于0
        //不加这行-20分
        if(length<0)throw error("invalid length");
        
        data=new T[length];
        for(int i=0;i<length;i++)
            data[i]=arr[i];
    }
    ArrayList(const ArrayList<T>& that):length(that.length)
    {
        data=new T[that.length];
        for(int i=0;i<that.length;i++)
            data[i]=that.data[i];
    }
    ~ArrayList(){delete[] data;}

    //这里也有一个const
    int size()const{return length;}

    ArrayList<T>& operator=(const ArrayList<T>& that)
    {
        if(this==&that)return *this;
        delete[] data;
        length=that.length;
        data=new T[length];
        for(int i=0;i<length;i++)
            data[i]=that.data[i];
        return *this;
    }

    //这里要加三个const
    //第一个是因为返回值是const，第二个是因为that可能是const，第三个是因为this可能是const
    //详见 https://blog.csdn.net/weixin_43734095/article/details/104465307
    const ArrayList<T> operator+(const ArrayList<T>& that)const
    {
        ArrayList<T> ret(length+that.length);
        for(int i=0;i<length;i++)
            ret.data[i]=data[i];
        for(int i=0;i<that.length;i++)
            ret.data[i+length]=that.data[i];
        return ret;
    }

    //这里也有一个const
    bool operator==(const ArrayList<T>& that)const
    {
        if(length!=that.length)return false;
        for(int i=0;i<length;i++)
            if(data[i]!=that.data[i])return false;
        return true;
    }
    //这里也有一个const
    bool operator!=(const ArrayList<T>& that)const
    {
        if(length!=that.length)return true;
        for(int i=0;i<length;i++)
            if(data[i]!=that.data[i])return true;
        return false;
    }
    //这里下标要重载两次
    //详细见 https://zhuanlan.zhihu.com/p/627768698

    //这一个为了可以通过下标修改
    T& operator[](int index)
    {
        if(index<0||index>=length)throw error("index out of bound");
        return data[index];
    }

    //第二个const是为了让const对象也可以通过下标访问
    //同时第一个const禁止通过这个函数修改对象
    const T& operator[](int index)const
    {
        if(index<0||index>=length)throw error("index out of bound");
        return data[index];
    }
};

template<typename T>
ostream& operator<<(ostream& os,const ArrayList<T>& arr)
{
    for(int i=0;i<arr.size();i++)
        if(i==0)os<<arr[i];
        else os<<' '<<arr[i];
    // os<<endl;
    return os;
}

#ifdef MAIN

template<typename T>
void printList(ArrayList<T> list) {
#ifdef USE_OS
    std::cout << list << "\n";
#else
    list.print();
    std::cout << "\n";
#endif
}


//主函数
int main()
{
    #ifdef DEBUG
        file_mode();
    #endif

    const int a[5]={1,2,3,4,5};
    const int b[5]={6,7,8,9,10};
    ArrayList<int> arr1(a,5);
    ArrayList<int> arr2(b,5);
    printList(arr1);
    printList(arr2);
    printList(arr1+arr2);
    const ArrayList<int> arrs[2]={arr1,arr2};
    
    ArrayList<ArrayList<int> > arr3(arrs,2);

    printList(arr3[0]);
    printList(arr3[1]);
    printList(arr3[0]+arr3[1]);
    printList(arr3);

    arr3[0]=arr1+arr1;

    printList(arr3[0]);
    printList(arr3[1]);
    printList(arr3[0]+arr3[1]);
    printList(arr3);

    try {
        cout<<arr3[1][6];
    } catch (error &e) {
        std::cout << e.toString() << std::endl;
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
        _getcwd(file_path,256);
        int file_path_lenth=strlen(file_path);
        file_path[file_path_lenth++]='\\';
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
        file_in.open(file_path);
        file_in.close();
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

