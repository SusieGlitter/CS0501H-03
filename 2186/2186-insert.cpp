#include <fstream>
using std::string;
using std::fstream;
using std::ifstream;
using std::ofstream;
#include <string>

const int M=228;
const int L=32;



class ClassNode
{
public:
    bool isLeaf;

    string keys[M];
    //1-based
    int key_val_cnt;

    int sons_index[M+1];

    ClassNode():isLeaf(true),key_val_cnt(0) {}
    ClassNode(bool isLeaf):isLeaf(isLeaf) {};
    ClassNode(const MemoryRiver<ClassNode> &mem,const int &index)
    {
        mem.read(*this,index);
    }
    ClassNode(const ClassNode &that):isLeaf(that.isLeaf),key_val_cnt(that.key_val_cnt) 
    {
        for(int i=0;i<=key_val_cnt;i++)
            sons_index[i]=that.sons_index[i];
    }
    
    int find_son_index(const string &key)
    {
        for(int i=0;i<key_val_cnt;i++)
            if(keys[i]>=key)
                return sons_index[i];
        return sons_index[key_val_cnt];
    }

    void add_key(string key,int index)
    {
        keys[key_val_cnt]=key;
        key_val_cnt++;
        for(int i=key_val_cnt-1;i>=1;i--)
        {
            if(keys[i]>keys[i-1])
            {
                sons_index[i+1]=index;
                break;
            }
            std::swap(keys[i],keys[i-1]);
            std::swap(sons_index[i+1],sons_index[i]);
        }
    }
    string split_into(ClassNode &splitNode)
    {
        int M1=M/2+1;
        key_val_cnt=M1-1;
        splitNode.key_val_cnt=M-M1-1;
        for(int i=M1;i<M;i++)
        {
            splitNode.keys[i-M1]=keys[i];
            splitNode.sons_index[i-M1]=sons_index[i];
        }
        splitNode.sons_index[splitNode.key_val_cnt]=sons_index[M];
        return keys[M1-1];
    }
};

class ClassData
{
public:
    string data_key[L+1];
    int data_val[L+1];
    //1-based
    int data_cnt;

    int prev_index;
    int next_index;

    ClassData():data_cnt(0),prev_index(-1),next_index(-1) {}
    ClassData(const MemoryRiver<ClassData> &mem,const int &index)
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
        {
            data_key[i]=that.data_key[i];
            data_val[i]=that.data_val[i];
        }
    }
    void add_data(const string &key,const int &val)
    {
        data_key[data_cnt]=key;
        data_val[data_cnt]=val;
        data_cnt++;
        for(int i=data_cnt-1;i>=1;i--)
        {
            if(data_key[i]>data_key[i-1]||(data_key[i]==data_key[i-1]&&data_val[i]>data_val[i-1]))
                break;
            std::swap(data_key[i],data_key[i-1]);
            std::swap(data_val[i],data_val[i-1]);
        }
    }
    string split_into(ClassData &splitData)
    {
        int L1=L/2+1;
        data_cnt=L1;
        splitData.data_cnt=L+1-L1;
        for(int i=L1;i<=L;i++)
        {
            splitData.data_key[i-L1]=data_key[i];
            splitData.data_val[i-L1]=data_val[i];
        }
        return splitData.data_key[0];
    }
};


class FreeList
{
public:
    int index;
    FreeList* next;
    FreeList():next(nullptr){}
    FreeList(int index,FreeList* next):index(index),next(next){}
};

FreeList* insert(FreeList* head, int index)
{
    return head = new FreeList(index,head);
}
FreeList* erase(FreeList* head)
{
    FreeList* temp = head;
    head = head->next;
    delete temp;
    return head;
}


template<class T, int info_len = 2>
class MemoryRiver {
private:
    /* your code here */
    FreeList* head;
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
    int write(T &t)const {
        /* your code here */
        file.open(file_name,std::ios::in|std::ios::out);
        if(head!=nullptr)
        {
            //使用已释放空间
            file.seekp(head->index);
            head=erase(head);
        }
        else
        {
            //没有已释放空间
            file.seekp(0,std::ios::end);
        }
        int index = file.tellp();
        file.write(reinterpret_cast<char *>(&t),sizeofT);
        file.close();
        return index;
    }

    //用t的值更新位置索引index对应的对象，保证调用的index都是由write函数产生
    void update(T &t, const int index)const {
        /* your code here */
        file.open(file_name,std::ios::in|std::ios::out);
        file.seekp(index);
        file.write(reinterpret_cast<char *>(&t),sizeofT);
        file.close();
    }

    //读出位置索引index对应的T对象的值并赋值给t，保证调用的index都是由write函数产生
    void read(T &t, const int index)const {
        /* your code here */
        file.open(file_name,std::ios::in|std::ios::out);
        file.seekg(index);
        file.read(reinterpret_cast<char *>(&t),sizeofT);
        file.close();
    }

    //删除位置索引index对应的对象(不涉及空间回收时，可忽略此函数)，保证调用的index都是由write函数产生
    void Delete(int index)const {
        /* your code here */
        file.open(file_name,std::ios::in|std::ios::out);
        head=insert(head,index);
        file.close();
    }
};



class BPT
{
public:
    int root_index;
    static int stack_index[6];
    static ClassNode *stack[6];
    static int stack_top;
    MemoryRiver<ClassData> memData;
    MemoryRiver<ClassNode> memNode;
    int cntData;

    BPT()
    {
        //存写初始化
        memData.initialise("Data.txt");
        memNode.initialise("Node.txt");

        //空节点生成
        ClassNode root(true);
        root.key_val_cnt=0;

        ClassData tempData;
        tempData.data_cnt=0;

        //写入内存
        root.sons_index[0]=memData.write(tempData);

        root_index=memNode.write(root);

    }
    ~BPT() {}

    void INSERT(string key,int val)
    {
        //储存查询路径
        stack_index[0]=root_index;
        stack_top=0;
        stack[stack_top]=new ClassNode(memNode,root_index);
        while((*stack[stack_top]).isLeaf==false)
        {
            stack_index[stack_top+1]=(*stack[stack_top]).find_son_index(key);
            stack_top++;
            stack[stack_top]=new ClassNode(memNode,root_index);
        }

        //开始处理data插入
        int data_index=(*stack[stack_top]).find_son_index(key);

        //插入排序 第一关键字key 第二关键字val
        ClassData tempData(memData,data_index);
        tempData.add_data(key,val);

        //判断数据块是否要裂开
        if(tempData.data_cnt==L+1)
        {
            ClassData splitData;
            string split_key=tempData.split_into(splitData);
            int split_index=memData.write(splitData);
            (*stack[stack_top]).add_key(split_key,split_index);

            //更新链接关系
            splitData.next_index=tempData.next_index;
            tempData.next_index=split_index;

            splitData.prev_index=data_index;
            if(splitData.next_index!=-1)
            {
                ClassData nextData(memData,splitData.next_index);
                nextData.prev_index=split_index;
                memData.update(nextData,splitData.next_index);
            }
        }
        //更新
        memData.update(tempData,data_index);

        while(stack_top!=0)
        {
            //判断非根节点是否需要裂开
            if((*stack[stack_top]).key_val_cnt==M)
            {
                ClassNode splitNode((*stack[stack_top]).isLeaf);
                string split_key=(*stack[stack_top]).split_into(splitNode);
                int split_index=memNode.write(splitNode);
                (*stack[stack_top-1]).add_key(split_key,split_index);
            }
            //更新
            memNode.update((*stack[stack_top]),stack_index[stack_top]);
            delete stack[stack_top];
            stack_top--;
        }
        //判断根是否要裂开
        if((*stack[0]).key_val_cnt==M)
        {
            ClassNode splitNode((*stack[0]).isLeaf);
            string split_key=(*stack[0]).split_into(splitNode);
            int split_index=memNode.write(splitNode);
            ClassNode root(false);
            root.key_val_cnt=1;
            root.keys[0]=split_key;
            root.sons_index[0]=stack_index[0];
            root.sons_index[1]=split_index;
        }
        //更新
        memNode.update((*stack[0]),stack_index[0]);
        delete stack[0];
        stack_top--;
    }

};


int main()
{
    BPT bpt;
    
}