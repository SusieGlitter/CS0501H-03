#include<iostream>
using namespace std;
//总调试开关
// #define DEBUG
#define DEBUG2

#ifdef DEBUG
    //这些头文件实际上没有被使用
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


//!链表节点类
template<typename T>
class Node
{

private:
    //前向指针
    Node *prev;
    //后向指针
    Node *next;
    //数据
    T data;

public:
    Node();
    Node(T data);
    Node(Node<T>& that);
    ~Node();
    //前向指针
    Node* getPrev();
    //后向指针
    Node* getNext();

    //节点读取
    T getData();
    //节点赋值
    void setData(T data);
    //插入于前
    void insPrev(Node<T>* ins);
    //插入于后
    void insNext(Node<T>* ins);
    //删除节点
    T popNode();
};

template<typename T>
Node<T>::Node():prev(nullptr),next(nullptr){}

template<typename T>
Node<T>::Node(T data):data(data),prev(nullptr),next(nullptr){}

template<typename T>
Node<T>::Node(Node<T>& that):data(that.data),prev(nullptr),next(nullptr){}

template<typename T>
Node<T>::~Node(){}

template<typename T>
Node<T>* Node<T>::getPrev(){return this->prev;}

template<typename T>
Node<T>* Node<T>::getNext(){return this->next;}

template<typename T>
T Node<T>::getData(){return data;}

template<typename T>
void Node<T>::setData(T data){this->data=data;return;}

template<typename T>
void Node<T>::insPrev(Node<T>* ins)
{
    #ifdef DEBUG
        cout<<this->getData()<<"insPrev"<<ins->getData()<<endl;
    #endif
    if((this->prev)!=nullptr)
    {
        this->prev->next=ins;
        ins->prev=this->prev;
    }
    this->prev=ins;
    ins->next=this;
    return;
}

template<typename T>
void Node<T>::insNext(Node<T>* ins)
{
    #ifdef DEBUG
        cout<<this->getData()<<"insNext"<<ins->getData()<<endl;
    #endif
    if((this->next)!=nullptr)
    {
        this->next->prev=ins;
        ins->next=this->next;
    }
    this->next=ins;
    ins->prev=this;
    return;
}

template<typename T>
T Node<T>::popNode()
{
    #ifdef DEBUG
        cout<<"popNode"<<this->getData()<<endl;
    #endif
    if(this->next!=nullptr)
        this->next->prev=this->prev;
    if(this->prev!=nullptr)
        this->prev->next=this->next;
    this->prev=nullptr;
    this->next=nullptr;
    return this->data;
}




//!链表类
template<typename T>
class LinkedList
{

private:
    Node<T>* head;
    Node<T>* tail;
    int listSize;

public:
    LinkedList();
    LinkedList(const LinkedList<T> & that);
    ~LinkedList();
    //重构赋值
    LinkedList<T>& operator=(const LinkedList<T> & that);
    //返回表头
    Node<T>* getHead();
    //返回表尾
    Node<T>* getTail();
    //返回长度
    int size();
    //表头插入
    void pushFront(T ins);
    //表尾插入
    void pushBack(T ins);
    //表头删除
    T popFront();
    //表尾删除
    T popBack();
    //打印元素
    void print();
    //返回类型
    virtual const char* name();
    //查询操作
    virtual T peak();
    //删除操作
    virtual T pop();
    //插入操作
    virtual void push(T ins);
};

template<typename T>
LinkedList<T>::LinkedList():listSize(0){}

template<typename T>
LinkedList<T>::LinkedList(const LinkedList<T> & that)
{
    this->listSize=that.listSize;
    Node<T>* pthis,pthat,pnew;
    pthis=this->head;
    pthat=that.head;

    if(pthat==nullptr)return;

    //第一个节点的插入
    pnew=new Node<T>(*pthat);
    this->head=pnew;
    
    pthat=pthat.getNext();

    //后续节点的插入
    while(pthat!=nullptr)
    {
        pnew=new Node<T>(*pthat);
        pthis->insNext(*pnew);

        pthis=pthis->getNext();
        pthat=pthat->getNext();
    }

    this->tail=pthis;
    return;
}

template<typename T>
LinkedList<T>::~LinkedList()
{
    while(this->listSize)
        this->popBack();
    this->head=nullptr;
    this->tail=nullptr;
    return;
}

template<typename T>
Node<T>* LinkedList<T>::getHead(){return this->head;}

template<typename T>
Node<T>* LinkedList<T>::getTail(){return this->tail;}

template<typename T>
int LinkedList<T>::size(){return this->listSize;}

template<typename T>
void LinkedList<T>::pushFront(T ins)
{
    Node<T>* newNode=new Node<T>(ins);
    this->listSize++;

    //新的链表
    if(this->listSize==1)
    {
        this->head=newNode;
        this->tail=newNode;
        return;
    }
    
    this->head->insPrev(newNode);
    this->head=this->head->getPrev();
    return;
}

template<typename T>
void LinkedList<T>::pushBack(T ins)
{
    Node<T>* newNode=new Node<T>(ins);
    this->listSize++;

    //新的链表
    if(this->listSize==1)
    {
        this->head=newNode;
        this->tail=newNode;
        return;
    }
    
    this->tail->insNext(newNode);
    this->tail=this->tail->getNext();
    return;
}

template<typename T>
T LinkedList<T>::popFront()
{
    this->listSize--;
    T ret;
    ret=this->head->getData();
    //空了
    if(this->listSize==0)
    {
        this->head->popNode();
        delete this->head;
        this->head=nullptr;
        this->tail=nullptr;
        return ret;
    }
    //没空（有下一个节点）
    Node<T>* pdel=this->head;
    this->head=this->head->getNext();
    pdel->popNode();
    delete pdel;
    return ret;
}

template<typename T>
T LinkedList<T>::popBack()
{
    this->listSize--;
    T ret;
    ret=this->tail->getData();
    //空了
    if(this->listSize==0)
    {
        this->tail->popNode();
        delete this->tail;
        this->head=nullptr;
        this->tail=nullptr;
        return ret;
    }
    //没空（有上一个节点）
    Node<T>* pdel=this->tail;
    this->tail=this->tail->getPrev();
    pdel->popNode();
    delete pdel;
    return ret;
}

template<typename T>
ostream& operator<< (ostream& os,LinkedList<T> & L)
{
    Node<T>* pprint;
    pprint=L.getHead();
    if(pprint==nullptr)
    {
        os<<endl;
        return os;
    }
    os<<pprint->getData();

    pprint=pprint->getNext();

    while(pprint!=nullptr)
    {
        os<<' '<<pprint->getData();
        pprint=pprint->getNext();
    }
    os<<endl;
    return os;
}


template<typename T>
ostream& operator<< (ostream& os,Node<T> & Node)
{
    os<<Node.getData();
    return os;
}

template<typename T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T> & that)
{

    if(this==&that)return *this;
    while(this->listSize)
        this->popBack();


    this->listSize=that.listSize;
    Node<T>* pthis,pthat,pnew;
    pthis=this->head;
    pthat=that.head;

    if(pthat==nullptr)return *this;

    //第一个节点的插入
    pnew=new Node<T>(*pthat);
    this->head=pnew;
    
    pthat=pthat.getNext();

    //后续节点的插入
    while(pthat!=nullptr)
    {
        pnew=new Node<T>(*pthat);
        pthis->insNext(*pnew);

        pthis=pthis->getNext();
        pthat=pthat->getNext();
    }

    this->tail=pthis;
    return *this;
}

template<typename T>
void LinkedList<T>::print()
{
    cout<<*this;
}

template<typename T>
const char* LinkedList<T>::name()
{
    return "";
}

template<typename T>
T LinkedList<T>::peak()
{
    T ret;
    return ret;
}

template<typename T>
T LinkedList<T>::pop()
{
    T ret;
    return ret;
}

template<typename T>
void LinkedList<T>::push(T ins){}



//!栈类
template<typename T>
class Stack:public LinkedList<T>
{
private:
public:
    //返回类型
    const char* name();
    //查询操作
    T peak();
    //删除操作
    T pop();
    //插入操作
    void push(T ins);
};
template<typename T>
const char* Stack<T>::name()
{
    return "Stack";
}

template<typename T>
T Stack<T>::peak()
{
    T ret;
    ret=this->getTail()->getData();
    return ret;
}

template<typename T>
T Stack<T>::pop()
{
    T ret;
    ret=this->popBack();
    return ret;
}

template<typename T>
void Stack<T>::push(T ins)
{
    this->pushBack(ins);
}




//!队类
template<typename T>
class Queue:public LinkedList<T>
{
private:
public:
    //返回类型
    const char* name();
    //查询操作
    T peak();
    //删除操作
    T pop();
    //插入操作
    void push(T ins);
};
template<typename T>
const char* Queue<T>::name()
{
    return "Queue";
}

template<typename T>
T Queue<T>::peak()
{
    T ret;
    ret=this->getHead()->getData();
    return ret;
}

template<typename T>
T Queue<T>::pop()
{
    T ret;
    ret=this->popFront();
    return ret;
}

template<typename T>
void Queue<T>::push(T ins)
{
    this->pushBack(ins);
}



#ifdef DEBUG2
//主函数
int main()
{
    #ifdef DEBUG
        file_mode();
    #endif
    // LinkedList<int>* list1=new LinkedList<int>;
    // list1->pushFront(1);
    // LinkedList<int>* list2=new LinkedList<int>;
    // list2->pushFront(2);
    // LinkedList<int>* list3=new LinkedList<int>;
    // list3->pushFront(3);
    // LinkedList<int>* list4=new LinkedList<int>;
    // list4->pushFront(4);

    // cout<<*list1;

    LinkedList<LinkedList<int> >* listoflist = new LinkedList<LinkedList<int> >;

    // listoflist->pushFront(*list1);
    // listoflist->pushFront(*list2);
    // listoflist->pushFront(*list3);
    // listoflist->pushFront(*list4);

    // cout<<*listoflist;

    return 0;
    #ifdef DEBUG
        fclose(stdin);
    #endif
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

