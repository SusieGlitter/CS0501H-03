#include<iostream>
using namespace std;
//总调试开关
// #define DEBUG
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

//节点
template<typename T>
class Node
{
public:
    T data;
    Node<T>* prev;
    Node<T>* next;
    Node():prev(nullptr),next(nullptr){}
    Node(const T& data,Node<T>* prev=nullptr,Node<T>* next=nullptr):data(data),prev(prev),next(next){}
};

//双向迭代器
template<typename T>
class Iterator
{
public:
    Node<T>* curr;
    Iterator():curr(nullptr){}
    Iterator(Node<T>* curr):curr(curr){}
    Iterator(const Iterator<T>& that):curr(that.curr){}

    Iterator& operator++(){curr=curr->next;return *this;}
    Iterator operator++(int){Iterator temp=*this;++(*this);return temp;}

    Iterator& operator--(){curr=curr->prev;return *this;}
    Iterator operator--(int){Iterator temp=*this;--(*this);return temp;}

    T& operator*(){return curr->data;}
    T* operator->(){return &(curr->data);}

    const bool operator==(const Iterator<T>& that)const{return curr==that.curr;}
    const bool operator!=(const Iterator<T>& that)const{return curr!=that.curr;}
};

//链表
template<typename T>
class LinkedList
{
private:
    Node<T>* head;
    Node<T>* tail;
    int list_size;
public:
    typedef Iterator<T> iterator;
    typedef const Iterator<T> const_iterator;

    LinkedList()
    {
        head=new Node<T>();
        tail=new Node<T>();
        head->next=tail;
        tail->prev=head;
        list_size=0;
        return;
    }
    LinkedList(const LinkedList<T>& that)
    {
        this->list_size=that.list_size;
        head=new Node<T>();
        tail=new Node<T>();
        head->next=tail;
        tail->prev=head;
        for(iterator temp=that.Begin();temp!=that.End();temp++)
            pushBack(*temp);
        return;
    }
    ~LinkedList()
    {
        Clear();
        delete head;
        delete tail;
        return;
    }

    LinkedList<T>& operator=(const LinkedList<T>& that)
    {
        if(this==&that)return *this;
        Clear();
        this->list_size=that.list_size;
        for(iterator temp=that.Begin();temp!=that.End();temp++)
        {
            push_back(*temp);
        }
        return *this;
    }

    iterator Erase(iterator del)
    {
        Node<T>* temp=del.curr;
        temp->prev->next=temp->next;
        temp->next->prev=temp->prev;
        list_size--;
        Node<T>* next(temp->next);
        delete temp;
        return iterator(next);
    }

    void Clear()
    {
        iterator temp=Begin();
        while(temp!=End())
            temp=Erase(temp);
        return;
    }

    iterator Insert(iterator itr,const T& data)
    {
        Node<T>* oldNode=itr.curr;
        Node<T>* newNode=new Node<T>(data,oldNode->prev,oldNode);
        oldNode->prev->next=newNode;
        oldNode->prev=newNode;
        list_size++;
        return iterator(newNode);
    }

    iterator Begin(){return iterator(head->next);}
    const_iterator Begin()const{return const_iterator(head->next);}

    iterator End(){return iterator(tail);}
    const_iterator End()const{return const_iterator(tail);}

    T& Front(){return *Begin();}
    const T& Front()const{return *Begin();}

    T& Back(){return *(--End());}
    const T& Back()const{return *(--End());}

    int size()const{return list_size;}

    void pushFront(const T& data){Insert(Begin(),data);return;}
    void pushBack(const T& data){Insert(End(),data);return;}

    T popFront(){T ret=Front();Erase(Begin());return ret;}
    T popBack(){T ret=Back();Erase(--End());return ret;}

    void print()
    {
        int i=1;
        for(iterator temp=Begin();temp!=End();temp++,i++)
            if(i==1)cout<<*temp;
            else cout<<' '<<*temp;
        cout<<endl;
        return;
    }

    virtual const char* name(){return "";}
    virtual T peak(){T ret;return ret;}
    virtual T pop(){T ret;return ret;}
    virtual void push(const T& data){return;}
};

template<typename T>
ostream& operator<<(ostream& os,const LinkedList<T>& list)
{
    int i=1;
    for(Iterator<T> temp=list.Begin();temp!=list.End();temp++,i++)
        if(i==1)os<<*temp;
        else os<<' '<<*temp;
    os<<endl;
    return os;
}

template<typename T>
class Stack:public LinkedList<T>
{
public:
    const char* name(){return "Stack";}
    T peak(){T ret=this->Back();return ret;}
    T pop(){T ret=this->Back();this->popBack();return ret;}
    void push(const T& data){this->pushBack(data);return;}
};

template<typename T>
class Queue:public LinkedList<T>
{
public:
    const char* name(){return "Queue";}
    T peak(){T ret=this->Front();return ret;}
    T pop(){T ret=this->Front();this->popFront();return ret;}
    void push(const T& data){this->pushBack(data);return;}
};


#ifdef MAIN

//主函数
int main()
{
    #ifdef DEBUG
        file_mode();
    #endif

    LinkedList<int> * list1 = new LinkedList<int>;
    LinkedList<int> * list2 = new LinkedList<int>;
    LinkedList<int> * list3 = new LinkedList<int>;
    LinkedList<int> * list4 = new LinkedList<int>;
    
    list1->pushBack(1);
    list2->pushBack(2);
    list3->pushBack(3);
    list4->pushBack(4);
    list4->pushBack(4);

    LinkedList<LinkedList<int> > * list = new LinkedList<LinkedList<int> >;

    list->pushBack(*list1);
    list->pushBack(*list2);
    list->pushBack(*list3);
    list->pushBack(*list4);

    list->print();



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

