#include <iostream>
#include <cstdlib>
#include <cstdio>
using namespace std;
const int month_days[] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
class Date
{
private:
    int _year;
    int _month;
    int _day;
public:
    //构造函数
    Date():_year(1900),_month(1),_day(1){}
    Date(int year,int month,int day):_year(year),_month(month),_day(day)
    {
        if(!legal())
        {
            _year=1900;
            _month=1;
            _day=1;
        }
    }
    ~Date(){}
    //判断是否为闰年
    bool isLeapYear(){return _year%400==0||_year%100!=0&&_year%4==0;}
    //这月有几天
    int monthDays()
    {
        if(_month==2&&isLeapYear())
            return 29;
        else
            return month_days[_month];
    }
    //是否合法
    bool legal()
    {
        if(_year<1900||_year>2030)return false;
        if(_month<1||_month>12)return false;
        return _day>=1&&_day<=monthDays();
    }
    //一个日期加上一个天数
    void tomorrow()
    {
        if(_day==monthDays())
        {
            _day=1;
            if(_month==12)
            {
                _month=1;
                _year++;
            }
            else
                _month++;
        }
        else
            _day++;
    }
    const Date operator+(const int& plus)const
    {
        if(plus==0)return *this;
        if(plus<0)
            return *this-(-plus);
        Date temp=*this;
        int p=plus;
        while(p)
        {
            if(_day==1)
                break;
            p--;
            temp.tomorrow();
        }
        while(p>=temp.monthDays())
        {
            p-=temp.monthDays();
            temp._month++;
            if(temp._month==13)
            {
                temp._month=1;
                temp._year++;
            }
        }
        while(p)
        {
            p--;
            temp.tomorrow();
        }
        return temp;
    }
    //一个日期减去一个天数
    void yesterday()
    {
        if(_day==1)
        {
            if(_month==1)
            {
                _month=12;
                _year--;
            }
            else
                _month--;
            _day=monthDays();
        }
        else
            _day--;
    }
    const Date operator-(const int& subt)const
    {
        if(subt==0)return *this;
        if(subt<0)
            return *this+(-subt);
        Date temp=*this;
        int s=subt;
        while(s)
        {
            if(_day==temp.monthDays())
                break;
            s--;
            temp.yesterday();
        }
        while(s>=temp.monthDays())
        {
            s-=temp.monthDays();
            temp._month--;
            if(temp._month==0)
            {
                temp._month=12;
                temp._year--;
            }
        }
        while(s)
        {
            s--;
            temp.yesterday();
        }
        return temp;
    }
    //前置++
    Date& operator++()
    {
        tomorrow();
        return *this;
    }
    //后置++
    const Date operator++(int)
    {
        Date temp=*this;
        tomorrow();
        return temp;
    }
    //前置--
    Date& operator--()
    {
        yesterday();
        return *this;
    }
    //后置--
    const Date operator--(int)
    {
        Date temp=*this;
        yesterday();
        return temp;
    }
    //<>重载
    const bool operator<(const Date& that)const
    {
        if(_year<that._year)return true;
        if(_year>that._year)return false;
        if(_month<that._month)return true;
        if(_month>that._month)return false;
        return _day<that._day;
    }
    const bool operator>(const Date& that)const
    {
        return that<*this;
    }
    //==!=重载
    const bool operator==(const Date& that)const
    {
        return _year==that._year&&_month==that._month&&_day==that._day;
    }
    const bool operator!=(const Date& that)const
    {
        return !(*this==that);
    }
    //-重载
    const int operator-(const Date& that)const
    {
        int ret=0;
        Date a=*this,b=that;
        if(a==b)
            return 0;
        if(a>b)
            swap(a,b);
        while(a._year<b._year||a._month<b._month)
        {
            if(a._day==1)
                break;
            ret++;
            a.tomorrow();
        }
        while(a._year<b._year||a._month<b._month)
        {
            ret+=a.monthDays();
            a._month++;
            if(a._month==13)
            {
                a._month=1;
                a._year++;
            }
        }
        if(a==b)
            return ret;
        while(a!=b)
        {
            ret++;
            a.tomorrow();
        }
        return ret;
    }
    //重载输出运算符
    friend ostream& operator<<(ostream& os,const Date& d)
    {
        os<<d._year<<'-'<<d._month<<'-'<<d._day;
        return os;
    }
    //以上仅为提示，不代表你需要完成所有，你也可以添加其他需要的函数。
};

void Test()
{
    int op;
    cin >> op;
    int yy, mm, dd;
    if (op == 1 || op == 0)
    {
        Date d0;
        Date d1(2000, 2, 29);
        Date d2(1900, 2, 29);
        cout << d0 << endl;
        cout << d1 << endl;
        cout << d2 << endl;
        //d0.out(); d1.out(); d2.out();
    }
    if (op == 2 || op == 0)
    {
        cin >> yy >> mm >> dd;
        Date d0(yy, mm, dd);
        for (int i=0;i<5;++i) cout << ++d0 << endl; //(++d0).out();
        for (int i=0;i<5;++i) cout << d0++ << endl; //(d0++).out();
        for (int i=0;i<5;++i) cout << d0-- << endl; //(d0--).out();
        for (int i=0;i<2;++i) cout << --d0 << endl; //(--d0).out();
        cout << d0 << endl;
        //d0.out();
    }
    if (op == 3 || op == 0)
    {
        cin >> yy >> mm >> dd;
        Date d0(yy, mm, dd);
        cout << d0 + 100 << endl;
        // (d0+100).out();
        cout << d0 - 1000 << endl;
        // (d0-1000).out();
    }
    if (op == 4 || op == 0)
    {
        cin >> yy >> mm >> dd;
        Date d0(yy, mm, dd);
        Date d1(2020, 12, 21);
        cout << (d0 < d1) << endl;
    }
    if (op == 5 || op == 0)
    {
        cin >> yy >> mm >> dd;
        Date d0(yy, mm, dd);
        Date d1(1912, 6, 23);
        cout << d0 - d1 << endl;
    }
}
int main()
{
    Test();
    return 0;
}