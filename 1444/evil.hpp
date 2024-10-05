#ifndef EVIL_HPP
#define EVIL_HPP

#include <iostream>
using namespace std;

class Evil{
private:
    int st, ed, val;
    int *data;

public:

//构造函数
    Evil():st(0),ed(0),val(0)
    {
        data=new int[1];
        (*this)[0]=0;
    }
    Evil(int st,int ed,int val):st(st),ed(ed),val(val)
    {
        data=new int[ed-st+1];
        for(int i=st;i<=ed;i++)
            (*this)[i]=0;
    }
    Evil(const Evil& that):st(that.st),ed(that.ed),val(that.val)
    {
        data=new int[ed-st+1];
        for(int i=st;i<=ed;i++)
            (*this)[i]=that[i];
    }
//下标运算符重载
    int& operator[](int i)
    {
        if(i<st||i>ed)return data[0];
        return data[i-st];
    }
    const int& operator[](int i)const
    {
        if(i<st||i>ed)return data[0];
        return data[i-st];
    }
//赋值运算符重载
    Evil& operator=(const Evil& that)
    {
        if(this==&that)return *this;
        st=that.st;
        ed=that.ed;
        val=that.val;
        delete[] data;
        data=new int[ed-st+1];
        for(int i=st;i<=ed;i++)
            (*this)[i]=that[i];
        return *this;
    }
//前缀++重载
    Evil& operator++()
    {
        this->val++;
        return *this;
    }
//后缀++重载
    const Evil operator++(int i)
    {
        Evil temp=*this;
        this->val++;
        return temp;
    }
//输出重载
    friend ostream& operator<<(ostream& os,Evil e)
    {
        os<<e.val<<' ';
        for(int i=e.st;i<=e.ed;i++)
            if(i==e.st)os<<e[i];
            else os<<' '<<e[i];
        os<<'\n';
        return os;
    }
//析构函数
    ~Evil()
    {
        delete[] data;
    }
    void Print(){
        cout << val << " ";
        for(int i = 0;i < ed-st+1;++i)
            cout << data[i] <<" ";
        cout << endl;
    }
};

#endif//EVIL_HPP    