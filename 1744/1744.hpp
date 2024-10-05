#ifndef SRC_HPP
#define SRC_HPP
namespace sjtu
{
template <class T>
void sort(T *first, T *last)
{
    // TODO
    // O(nlogn)
    if(last-first==1)return;
    int len=last-first;
    T* mid=first+(len/2);
    sort(first,mid);
    sort(mid,last);

    T*aux=new T[len];
    T*pl,*pr,*pa;
    pl=first;
    pr=mid;
    pa=aux;

    while(pl!=mid&&pr!=last)
    {
        if((*pl)<(*pr))
            *(pa++)=*(pl++);
        else
            *(pa++)=*(pr++);
    }
    while(pl!=mid)
        *(pa++)=*(pl++);
    while(pr!=last)
        *(pa++)=*(pr++);
    
    pl=first;
    pa=aux;
    while(pl!=last)
        *(pl++)=*(pa++);
    
    delete[] aux;
}

template <class T>
T *lower_bound(T *first, T *last, const T &value)
{
    // TODO
    // O(logn)
    while(first<=last)
    {
        T* mid=first+(last-first)/2;
        if((*mid)<value)
            first=mid+1;
        else
            last=mid-1;
    }
    return first;
}

template <class T>
T *upper_bound(T *first, T *last, const T &value)
{
    // TODO
    // O(logn)
    while(first<=last)
    {
        T* mid=first+(last-first)/2;
        if(value<(*mid))
            last=mid-1;
        else
            first=mid+1;
    }
    return first;
}
} // namespace sjtu
#endif