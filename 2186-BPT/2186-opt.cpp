#include <fstream>
using std::string;
using std::fstream;
using std::ifstream;
using std::ofstream;
#include <cstring>
#include <iostream>
#include<unistd.h>

const int M=256;
const int L=256;

string memData_filename="Data.txt";
string memNode_filename="Node.txt";
char memBPT_filename_char[20]="BPT.txt";
string memBPT_filename="BPT.txt";

template<class T, int info_len = 2>
class MemoryRiver {
public:
    /* your code here */
    fstream file;
    string file_name;
    int sizeofT = sizeof(T);
public:
    MemoryRiver() = default;

    MemoryRiver(const string& file_name) : file_name(file_name) {}

    void initialise(string FN = "") {
        if (FN != "") file_name = FN;
        file.open(file_name, std::ios::out);
        int tmp = 0;
        for (int i = 0; i < info_len; ++i)
            file.write(reinterpret_cast<char *>(&tmp), sizeof(int));
        file.close();
    }

    //读出第n个int的值赋给tmp，1_base
    void get_info(int &tmp, int n) {
        if (n > info_len) return;
        /* your code here */
        file.open(file_name,std::ios::in|std::ios::out);
        file.seekg(sizeof(int)*(n-1));//1_base
        file.read(reinterpret_cast<char *>(&tmp),sizeof(int));
        file.close();
    }

    //将tmp写入第n个int的位置，1_base
    void write_info(int tmp, int n) {
        if (n > info_len) return;
        /* your code here */
        file.open(file_name,std::ios::in|std::ios::out);
        file.seekg(sizeof(int)*(n-1));//1_base
        file.write(reinterpret_cast<char *>(&tmp),sizeof(int));
        file.close();
    }

    //在文件合适位置写入类对象t，并返回写入的位置索引index
    //位置索引意味着当输入正确的位置索引index，在以下三个函数中都能顺利的找到目标对象进行操作
    //位置索引index可以取为对象写入的起始位置
    int write(T &t) {
        /* your code here */
        file.seekp(0,std::ios::end);
        int index = file.tellp();
        file.write(reinterpret_cast<char *>(&t),sizeofT);
        return index;
    }

    //用t的值更新位置索引index对应的对象，保证调用的index都是由write函数产生
    void update(T &t, const int index) {
        /* your code here */
        file.seekp(index);
        file.write(reinterpret_cast<char *>(&t),sizeofT);
    }

    //读出位置索引index对应的T对象的值并赋值给t，保证调用的index都是由write函数产生
    void read(T &t, const int index) {
        /* your code here */
        file.seekg(index);
        file.read(reinterpret_cast<char *>(&t),sizeofT);
    }

    //删除位置索引index对应的对象(不涉及空间回收时，可忽略此函数)，保证调用的index都是由write函数产生
    void Delete(int index) {
        /* your code here */
    }

    void fileopen()
    {
        file.open(file_name,std::ios::in|std::ios::out);
    }

    void fileclose()
    {
        file.close();
    }
};

class MyString
{
public:
    char c[65];
    MyString() {}
    MyString(char *that){strcpy(c,that);}
    MyString(const MyString &that){strcpy(c,that.c);}
    MyString &operator=(const MyString &that)
    {
        strcpy(c,that.c);
        return *this;
    }
    bool operator==(const MyString &that){return strcmp(c,that.c)==0;}
    bool operator!=(const MyString &that){return strcmp(c,that.c)!=0;}
    bool operator>(const MyString &that){return strcmp(c,that.c)>0;}
    bool operator<(const MyString &that){return strcmp(c,that.c)<0;}
    bool operator>=(const MyString &that){return strcmp(c,that.c)>=0;}
    bool operator<=(const MyString &that){return strcmp(c,that.c)<=0;}
    void input(){std::cin>>c;}
};

class K_V
{
public:
    MyString key;
    int val;
    K_V() {}
    K_V(const MyString &key,const int &val):key(key),val(val) {}
    K_V(const K_V &that):key(that.key),val(that.val) {}
    K_V &operator=(const K_V &that)
    {
        key=that.key;
        val=that.val;
        return *this;
    }
    bool operator==(const K_V &that){return key==that.key?val==that.val:key==that.key;}
    bool operator!=(const K_V &that){return key==that.key?val!=that.val:key!=that.key;}
    bool operator>(const K_V &that){return key==that.key?val>that.val:key>that.key;}
    bool operator<(const K_V &that){return key==that.key?val<that.val:key<that.key;}
    bool operator>=(const K_V &that){return key==that.key?val>=that.val:key>=that.key;}
    bool operator<=(const K_V &that){return key==that.key?val<=that.val:key<=that.key;}
};

class ClassNode
{
public:
    bool isLeaf;
    K_V mini_key_val;
    K_V keys_vals[M];
    //1-based
    int key_val_cnt;

    int sons_index[M+1];

    ClassNode():isLeaf(true),key_val_cnt(0) {}
    ClassNode(bool isLeaf):isLeaf(isLeaf) {};
    ClassNode(MemoryRiver<ClassNode> &mem,int index)
    {
        mem.read(*this,index);
    }
    ClassNode(const ClassNode &that):isLeaf(that.isLeaf),key_val_cnt(that.key_val_cnt) 
    {
        mini_key_val=that.mini_key_val;
        for(int i=0;i<=key_val_cnt;i++)
        {
            keys_vals[i]=that.keys_vals[i];
            sons_index[i]=that.sons_index[i];
        }
    }
    
    int find_son_num(const K_V &key_val)
    {
        for(int i=0;i<key_val_cnt;i++)
            if(keys_vals[i]>key_val)
                return i;
        return key_val_cnt;
    }

    void add_key_val(const K_V &key_val,const int &index)
    {
        keys_vals[key_val_cnt]=key_val;
        key_val_cnt++;
        sons_index[key_val_cnt]=index;
        int i;
        for(i=key_val_cnt-1;i>=1;i--)
        {
            if(keys_vals[i]>keys_vals[i-1])
                break;
            std::swap(keys_vals[i],keys_vals[i-1]);
            std::swap(sons_index[i+1],sons_index[i]);
        }
    }
    void del_key_val_for_prev(const int num)
    {
        key_val_cnt--;
        for(int i=num;i<=key_val_cnt;i++)
        {
            keys_vals[i-1]=keys_vals[i];
            sons_index[i]=sons_index[i+1];
        }
    }
    void del_key_val_for_next(const int num)
    {
        key_val_cnt--;
        for(int i=num;i<key_val_cnt;i++)
        {
            keys_vals[i]=keys_vals[i+1];
            sons_index[i]=sons_index[i+1];
        }
        sons_index[key_val_cnt]=sons_index[key_val_cnt+1];
    }
    K_V split_into(ClassNode &splitNode)
    {
        int M1=M/2+1;
        key_val_cnt=M1-1;
        splitNode.key_val_cnt=M-M1;
        for(int i=M1;i<M;i++)
        {
            splitNode.keys_vals[i-M1]=keys_vals[i];
            splitNode.sons_index[i-M1]=sons_index[i];
        }
        splitNode.sons_index[splitNode.key_val_cnt]=sons_index[M];
        splitNode.mini_key_val=keys_vals[M1-1];
        return keys_vals[M1-1];
    }
    void merge_next(ClassNode &nextNode)
    {
        for(int i=key_val_cnt+1;i<=key_val_cnt+nextNode.key_val_cnt;i++)
        {
            keys_vals[i]=nextNode.keys_vals[i-key_val_cnt-1];
            sons_index[i]=nextNode.sons_index[i-key_val_cnt-1];
        }
        keys_vals[key_val_cnt]=nextNode.mini_key_val;
        sons_index[key_val_cnt+nextNode.key_val_cnt+1]=nextNode.sons_index[nextNode.key_val_cnt];
        key_val_cnt=key_val_cnt+nextNode.key_val_cnt+1;
    }
    void merge_prev(ClassNode &prevNode)
    {
        sons_index[key_val_cnt+prevNode.key_val_cnt+1]=sons_index[key_val_cnt];
        for(int i=key_val_cnt-1;i>=0;i--)
        {
            keys_vals[i+prevNode.key_val_cnt+1]=keys_vals[i];
            sons_index[i+prevNode.key_val_cnt+1]=sons_index[i];
        }
        keys_vals[prevNode.key_val_cnt]=mini_key_val;
        for(int i=0;i<prevNode.key_val_cnt;i++)
        {
            keys_vals[i]=prevNode.keys_vals[i];
            sons_index[i]=prevNode.sons_index[i];
        }
        sons_index[prevNode.key_val_cnt]=prevNode.sons_index[prevNode.key_val_cnt];
        mini_key_val=prevNode.mini_key_val;
        key_val_cnt=key_val_cnt+prevNode.key_val_cnt+1;
    }
};

class ClassData
{
public:
    K_V datas[L+1];
    //1-based
    int data_cnt;

    int prev_index;
    int next_index;

    ClassData():data_cnt(0),prev_index(-1),next_index(-1) {}
    ClassData(MemoryRiver<ClassData> &mem,int index)
    {
        prev_index=-1;
        next_index=-1;
        mem.read(*this,index);
    }
    ClassData(const ClassData &that):data_cnt(data_cnt)
    {
        prev_index=-1;
        next_index=-1;
        for(int i=0;i<=data_cnt;i++)
            datas[i]=that.datas[i];
    }
    void add_data(const K_V &key_val)
    {
        datas[data_cnt]=key_val;
        data_cnt++;
        for(int i=data_cnt-1;i>=1;i--)
        {
            if(datas[i]>datas[i-1])
                break;
            std::swap(datas[i],datas[i-1]);
        }
    }
    bool del_data(const K_V &key_val)
    {
        bool found=false;
        for(int i=0;i<data_cnt;i++)
        {
            if(datas[i]==key_val)
            {
                found=true;
                for(int j=i+1;j<data_cnt;j++)
                    datas[j-1]=datas[j];
                break;
            }
        }
        if(found)
            data_cnt--;
        return found;
    }
    K_V split_into(ClassData &splitData)
    {
        int L1=L/2+1;
        data_cnt=L1;
        splitData.data_cnt=L+1-L1;
        for(int i=L1;i<=L;i++)
            splitData.datas[i-L1]=datas[i];
        return splitData.datas[0];
    }
    void merge_next(ClassData &nextData)
    {
        for(int i=data_cnt;i<data_cnt+nextData.data_cnt;i++)
            datas[i]=nextData.datas[i-data_cnt];
        data_cnt=data_cnt+nextData.data_cnt;
    }
    void merge_prev(ClassData &prevData)
    {
        for(int i=data_cnt-1;i>=0;i--)
            datas[i+prevData.data_cnt]=datas[i];
        for(int i=0;i<prevData.data_cnt;i++)
            datas[i]=prevData.datas[i];
        data_cnt=data_cnt+prevData.data_cnt;
    }
};


class BPT
{
public:
    int root_index;
    int stack_num[64];
    int stack_index[64];
    ClassNode *stack_node[64];
    int stack_top;
    MemoryRiver<ClassData> memData;
    MemoryRiver<ClassNode> memNode;
    MemoryRiver<BPT> memBPT;

    BPT()
    {
        //存写初始化
        memData.file_name=memData_filename;
        memNode.file_name=memNode_filename;
        memBPT.file_name=memBPT_filename;
        std::ofstream file;
        if(access(memBPT_filename_char,F_OK))
        {
            //新的BPT
            file.open(memBPT_filename_char);
            memData.initialise();
            memNode.initialise();
            memBPT.initialise();
            file.close();
            //空节点生成
            ClassNode root(true);
            root.key_val_cnt=0;

            ClassData tempData;
            tempData.data_cnt=0;

            //写入内存
            memData.fileopen();
            root.sons_index[0]=memData.write(tempData);
            memData.fileclose();

            memNode.fileopen();
            root_index=memNode.write(root);
            memNode.fileclose();

            memBPT.write_info(root_index,1);
        }
        //旧的BPT
        memBPT.get_info(root_index,1);
    }
    ~BPT() {}

    void INSERT(K_V key_val)
    {
        //储存查询路径
        memNode.fileopen();
        stack_index[0]=root_index;
        stack_top=0;
        stack_node[stack_top]=new ClassNode(memNode,root_index);
        while(stack_node[stack_top]->isLeaf==false)
        {
            stack_num[stack_top+1]=stack_node[stack_top]->find_son_num(key_val);
            stack_index[stack_top+1]=stack_node[stack_top]->sons_index[stack_num[stack_top+1]];
            stack_top++;
            stack_node[stack_top]=new ClassNode(memNode,stack_index[stack_top]);
        }
        memNode.fileclose();
        memData.fileopen();
        //开始处理data插入
        int data_num=stack_node[stack_top]->find_son_num(key_val);
        int data_index=stack_node[stack_top]->sons_index[data_num];

        //插入排序 第一关键字key 第二关键字val
        ClassData tempData(memData,data_index);
        tempData.add_data(key_val);

        //维护first_key_val
        if(data_num==0)
        {
            stack_node[stack_top]->mini_key_val=tempData.datas[0];
        }
        
        //判断数据块是否要裂开
        if(tempData.data_cnt==L+1)
        {
            //分裂
            ClassData splitData;
            K_V split_key_val=tempData.split_into(splitData);

            //更新自己链接关系
            splitData.next_index=tempData.next_index;
            splitData.prev_index=data_index;

            //储存新节点
            int split_index=memData.write(splitData);

            //插入新key_val
            stack_node[stack_top]->add_key_val(split_key_val,split_index);

            //更新邻居链接关系
            tempData.next_index=split_index;
            if(splitData.next_index!=-1)
            {
                ClassData nextData(memData,splitData.next_index);
                nextData.prev_index=split_index;
                memData.update(nextData,splitData.next_index);
            }
        }
        
        memData.update(tempData,data_index);
        memData.fileclose();
        memNode.fileopen();
        while(stack_top!=0)
        {
            //判断非根节点是否需要裂开
            if(stack_node[stack_top]->key_val_cnt==M)
            {
                ClassNode splitNode(stack_node[stack_top]->isLeaf);
                K_V split_key_val=stack_node[stack_top]->split_into(splitNode);
                int split_index=memNode.write(splitNode);
                stack_node[stack_top-1]->add_key_val(split_key_val,split_index);
            }
            if(stack_num[stack_top]==0)
                stack_node[stack_top-1]->mini_key_val=stack_node[stack_top]->mini_key_val;
            //更新
            memNode.update((*stack_node[stack_top]),stack_index[stack_top]);
            delete stack_node[stack_top];
            stack_top--;
        }
        //判断根是否要裂开
        if(stack_node[0]->key_val_cnt==M)
        {
            ClassNode splitNode(stack_node[0]->isLeaf);
            K_V split_key_val=stack_node[0]->split_into(splitNode);
            int split_index=memNode.write(splitNode);
            ClassNode root(false);
            root.key_val_cnt=1;
            root.keys_vals[0]=split_key_val;
            root.sons_index[0]=stack_index[0];
            root.sons_index[1]=split_index;
            root.mini_key_val=stack_node[0]->mini_key_val;
            root_index=memNode.write(root);
            memBPT.write_info(root_index,1);
        }
        //更新
        memNode.update((*stack_node[0]),stack_index[0]);
        delete stack_node[0];
        memNode.fileclose();
    }

    void FIND(K_V key_val)
    {
        memNode.fileopen();
        bool isNull=true;
        //储存查询路径
        stack_index[0]=root_index;
        stack_top=0;
        stack_node[stack_top]=new ClassNode(memNode,root_index);
        while(stack_node[stack_top]->isLeaf==false)
        {
            stack_num[stack_top+1]=stack_node[stack_top]->find_son_num(key_val);
            stack_index[stack_top+1]=stack_node[stack_top]->sons_index[stack_num[stack_top+1]];
            stack_top++;
            stack_node[stack_top]=new ClassNode(memNode,stack_index[stack_top]);
        }
        memNode.fileclose();
        memData.fileopen();
        //开始处理data查找
        int data_num=(*stack_node[stack_top]).find_son_num(key_val);
        int data_index=(*stack_node[stack_top]).sons_index[data_num];

        bool one_more_time_one_more_chance=true;
        while(data_index!=-1)
        {
            ClassData tempData(memData,data_index);
            data_index=-1;
            for(int i=0;i<tempData.data_cnt;i++)
            {
                //查询结束
                if(tempData.datas[i].key>key_val.key)
                    break;
                //匹配成功
                if(tempData.datas[i].key==key_val.key)
                {
                    one_more_time_one_more_chance=false;
                    isNull=false;
                    std::cout<<tempData.datas[i].val<<' ';
                    //下一个块可能还有
                    if(i==tempData.data_cnt-1)
                    {
                        data_index=tempData.next_index;
                    }
                }
            }
            if(one_more_time_one_more_chance)
            {
                one_more_time_one_more_chance=false;
                data_index=tempData.next_index;
            }
        }
        if(isNull)
            std::cout<<"null";
        std::cout<<std::endl;
        memData.fileclose();
        while(stack_top>=0)
        {
            delete stack_node[stack_top];
            stack_top--;
        }
    }

    void DELETE(K_V key_val)
    {
        //储存查询路径
        memNode.fileopen();
        stack_index[0]=root_index;
        stack_top=0;
        stack_node[stack_top]=new ClassNode(memNode,root_index);
        while(stack_node[stack_top]->isLeaf==false)
        {
            stack_num[stack_top+1]=stack_node[stack_top]->find_son_num(key_val);
            stack_index[stack_top+1]=stack_node[stack_top]->sons_index[stack_num[stack_top+1]];
            stack_top++;
            stack_node[stack_top]=new ClassNode(memNode,stack_index[stack_top]);
        }
        memNode.fileclose();
        memData.fileopen();

        //开始处理data删除
        int data_num=stack_node[stack_top]->find_son_num(key_val);
        int data_index=stack_node[stack_top]->sons_index[data_num];

        ClassData tempData(memData,data_index);

        //debug
        // ClassData prevData,nextData;
        // if(tempData.prev_index!=-1)
        //     memData.read(prevData,tempData.prev_index);
        // if(tempData.next_index!=-1)
        //     memData.read(nextData,tempData.next_index);

        bool deleted=tempData.del_data(key_val);
        //判断数据块是否要领养或合并
        if(deleted&&tempData.data_cnt>=(L+1)/2)
            memData.update(tempData,data_index);
        while(deleted&&tempData.data_cnt<(L+1)/2)
        {
            //准备工作
            bool have_prev=data_num>0;
            bool have_next=data_num<stack_node[stack_top]->key_val_cnt;
            ClassData prevData,nextData;
            if(tempData.prev_index!=-1)
                memData.read(prevData,tempData.prev_index);
            if(tempData.next_index!=-1)
                memData.read(nextData,tempData.next_index);
            
            //尝试领养
            if(have_prev&&prevData.data_cnt>(L+1)/2)
            {
                //可领养prevData
                prevData.data_cnt--;
                for(int i=tempData.data_cnt;i>=1;i--)
                    tempData.datas[i]=tempData.datas[i-1];
                tempData.datas[0]=prevData.datas[prevData.data_cnt];
                stack_node[stack_top]->keys_vals[data_num-1]=tempData.datas[0];
                tempData.data_cnt++;
                memData.update(prevData,tempData.prev_index);
                memData.update(tempData,data_index);
                break;
            }
            if(have_next&&nextData.data_cnt>(L+1)/2)
            {
                //可领养nextData
                nextData.data_cnt--;
                tempData.datas[tempData.data_cnt]=nextData.datas[0];
                for(int i=0;i<nextData.data_cnt;i++)
                    nextData.datas[i]=nextData.datas[i+1];
                stack_node[stack_top]->keys_vals[data_num]=nextData.datas[0];
                tempData.data_cnt++;
                memData.update(nextData,tempData.next_index);
                memData.update(tempData,data_index);
                if(data_num==0)
                    stack_node[stack_top]->mini_key_val=tempData.datas[0];
                break;
            }

            //尝试合并
            if(have_prev&&prevData.data_cnt==(L+1)/2)
            {
                //可合并prevData
                prevData.merge_next(tempData);
                prevData.next_index=tempData.next_index;
                memData.update(prevData,tempData.prev_index);
                stack_node[stack_top]->del_key_val_for_prev(data_num);
                if(tempData.next_index!=-1)
                {
                    nextData.prev_index=tempData.prev_index;
                    memData.update(nextData,tempData.next_index);
                }
                memData.Delete(data_index);
                break;
            }
            if(have_next&&nextData.data_cnt==(L+1)/2)
            {
                //可合并nextData
                nextData.merge_prev(tempData);
                nextData.prev_index=tempData.prev_index;
                memData.update(nextData,tempData.next_index);
                stack_node[stack_top]->del_key_val_for_next(data_num);
                if(tempData.prev_index!=-1)
                {
                    prevData.next_index=tempData.next_index;
                    memData.update(prevData,tempData.prev_index);
                }
                memData.Delete(data_index);
                if(data_num==0)
                    stack_node[stack_top]->mini_key_val=nextData.datas[0];
                break;
            }
            memData.update(tempData,data_index);
            break;
        }
        memData.fileclose();
        memNode.fileopen();
        while(stack_top!=0)
        {
            //判断非根节点是否需要领养或合并
            if(stack_node[stack_top]->key_val_cnt<(M-1)/2)
            {
                int node_num=stack_num[stack_top];
                bool have_prev=node_num>0;
                bool have_next=node_num<stack_node[stack_top-1]->key_val_cnt;
                ClassNode prevNode,nextNode;
                if(have_prev)
                    memNode.read(prevNode,stack_node[stack_top-1]->sons_index[node_num-1]);
                if(have_next)
                    memNode.read(nextNode,stack_node[stack_top-1]->sons_index[node_num+1]);
                    
                //尝试领养
                if(have_prev&&prevNode.key_val_cnt>(M-1)/2)
                {
                    // std::cout<<"一";
                    //可领养prevNode
                    //TODO
                    prevNode.key_val_cnt--;

                    for(int i=stack_node[stack_top]->key_val_cnt;i>=1;i--)
                    {
                        stack_node[stack_top]->keys_vals[i]=stack_node[stack_top]->keys_vals[i-1];
                        stack_node[stack_top]->sons_index[i+1]=stack_node[stack_top]->sons_index[i];
                    }
                    stack_node[stack_top]->sons_index[1]=stack_node[stack_top]->sons_index[0];
                    stack_node[stack_top]->sons_index[0]=prevNode.sons_index[prevNode.key_val_cnt+1];
                    stack_node[stack_top]->keys_vals[0]=stack_node[stack_top]->mini_key_val;
                    stack_node[stack_top]->mini_key_val=prevNode.keys_vals[prevNode.key_val_cnt];
                    stack_node[stack_top-1]->keys_vals[stack_num[stack_top]-1]=stack_node[stack_top]->mini_key_val;
                    
                    stack_node[stack_top]->key_val_cnt++;

                    memNode.update(prevNode,stack_node[stack_top-1]->sons_index[node_num-1]);
                    memNode.update((*stack_node[stack_top]),stack_index[stack_top]);

                    delete stack_node[stack_top];
                    stack_top--;
                    continue;
                }
                if(have_next&&nextNode.key_val_cnt>(M-1)/2)
                {
                    // std::cout<<"二";
                    //可领养nextNode
                    nextNode.key_val_cnt--;

                    stack_node[stack_top]->keys_vals[stack_node[stack_top]->key_val_cnt]=nextNode.mini_key_val;
                    nextNode.mini_key_val=nextNode.keys_vals[0];
                    stack_node[stack_top]->sons_index[stack_node[stack_top]->key_val_cnt+1]=nextNode.sons_index[0];
                    nextNode.sons_index[0]=nextNode.sons_index[1];
                    for(int i=0;i<nextNode.key_val_cnt;i++)
                    {
                        nextNode.keys_vals[i]=nextNode.keys_vals[i+1];
                        nextNode.sons_index[i+1]=nextNode.sons_index[i+2];
                    }

                    stack_node[stack_top]->key_val_cnt++;
                    
                    if(stack_num[stack_top]==0)
                        stack_node[stack_top-1]->mini_key_val=stack_node[stack_top]->mini_key_val;
                    stack_node[stack_top-1]->keys_vals[stack_num[stack_top]]=nextNode.mini_key_val;
                    memNode.update(nextNode,stack_node[stack_top-1]->sons_index[node_num+1]);
                    memNode.update((*stack_node[stack_top]),stack_index[stack_top]);
                    delete stack_node[stack_top];
                    stack_top--;
                    continue;
                }
                //尝试合并
                if(have_prev&&prevNode.key_val_cnt==(M-1)/2)
                {
                    // std::cout<<"三";
                    //可合并prevNode
                    //TODO
                    prevNode.merge_next(*stack_node[stack_top]);
                    memNode.update(prevNode,stack_node[stack_top-1]->sons_index[node_num-1]);
                    stack_node[stack_top-1]->del_key_val_for_prev(stack_num[stack_top]);
                    memNode.Delete(stack_index[stack_top]);
                    delete stack_node[stack_top];
                    stack_top--;
                    continue;
                }
                if(have_next&&nextNode.key_val_cnt==(M-1)/2)
                {
                    // std::cout<<"四";
                    //可合并nextNode
                    //TODO
                    nextNode.merge_prev(*stack_node[stack_top]);
                    memNode.update(nextNode,stack_node[stack_top-1]->sons_index[node_num+1]);
                    stack_node[stack_top-1]->del_key_val_for_next(stack_num[stack_top]);
                    memNode.Delete(stack_index[stack_top]);
                    if(stack_num[stack_top]==0)
                        stack_node[stack_top-1]->mini_key_val=nextNode.mini_key_val;
                    delete stack_node[stack_top];
                    stack_top--;
                    continue;
                }
            }
            //更新
            memNode.update((*stack_node[stack_top]),stack_index[stack_top]);
            if(stack_num[stack_top]==0)
                stack_node[stack_top-1]->mini_key_val=stack_node[stack_top]->mini_key_val;
            delete stack_node[stack_top];
            stack_top--;

        }
        //判断根节点是否需要消失
        if(stack_node[0]->isLeaf==false&&stack_node[0]->key_val_cnt==0)
        {
            //TODO
            memNode.Delete(root_index);
            root_index=stack_node[0]->sons_index[0];
            memBPT.write_info(root_index,1);
        }
        //更新
        memNode.update((*stack_node[0]),stack_index[0]);
        delete stack_node[0];
        memNode.fileclose();
    }
};

int q;
string opt;
MyString key;
int val; 
int main()
{
    BPT bpt;
    // char aaa[10]="aaa";
    // char bbb[10]="bbb";

    // // for(int i=1;i<=3000;i++)
    // for(int i=3000;i>=1;i--)
    //     bpt.INSERT(K_V(MyString(aaa),i));
    // std::cout<<"ok"<<std::endl;

    // bpt.FIND(K_V(MyString(aaa),1<<31));

    // for(int i=1;i<=3000;i++)
    // // for(int i=3000;i>=1;i--)
    // {
    //     bpt.DELETE(K_V(MyString(aaa),i));std::cout<<'\n';
        
    //     bpt.FIND(K_V(MyString(aaa),1<<31));
    // }

    std::cin>>q;
    while(q--)
    {
        // std::cout<<"ok"<<std::endl;
        std::cin>>opt;
        key.input();
        switch (opt[0])
        {
        case 'i':
            std::cin>>val;
            bpt.INSERT(K_V(key,val));
            break;
        case 'd':
            std::cin>>val;
            bpt.DELETE(K_V(key,val));
            break;
        case 'f':
            val=1<<31;
            bpt.FIND(K_V(key,val));
            break;
        
        default:
            break;
        }
    }
}