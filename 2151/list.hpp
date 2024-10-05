#ifndef SJTU_LIST_HPP
#define SJTU_LIST_HPP

#include "exceptions.hpp"
#include "algorithm.hpp"

#include <climits>
#include <cstddef>

namespace sjtu {
/**
 * a data container like std::list
 * allocate random memory addresses for data and they are doubly-linked in a list.
 */
template<typename T>
class list {
protected:
    class node {
    public:
        /**
         * add data members and constructors & destructor
         */
        node *prev;
        node *next;
        T *data;

        node() : prev(nullptr), next(nullptr), data(nullptr) {}
        node(const node &that) : prev(that.prev), next(that.next), data(nullptr)
        {
            if (that.data != nullptr)
                this->data = new T = *(that.data);
        }
        node &operator=(const node &that)
        {
            if (this == &that)
                return *this;
            if(this->data != nullptr)
                delete this->data;
            if(that.data != nullptr)
                this->data = new T(*(that.data));
            else
                this->data = nullptr;
            return *this;
        }
        node(node *prev, node *next) : prev(prev), next(next), data(nullptr) {}
        node(node *prev, node *next, const T &data) : prev(prev), next(next), data(nullptr) 
        {
            this->data = new T(data);
        }
        ~node() 
        {
            prev = next = nullptr;
            if(this->data != nullptr)
            {
                delete this->data;
            }
        }
    };

protected:
    /**
     * add data members for linked list as protected members
     */

    node *head;
    node *tail;
    size_t list_size;

    /**
     * insert node cur before node pos
     * return the inserted node cur
     */
    node *insert(node *pos, node *cur) 
    {
        list_size++;
        cur->prev = pos->prev;
        cur->next = pos;
        pos->prev->next = cur;
        pos->prev = cur;
        return cur;
    }
    /**
     * remove node pos from list (no need to delete the node)
     * return the removed node pos
     */
    node *erase(node *pos) 
    {
        node *ret = pos->next;
        pos->next->prev = pos->prev;
        pos->prev->next = pos->next;
        pos->next = nullptr;
        pos->prev = nullptr;
        // pos->~node();
        delete pos;
        list_size--;
        return ret;
    }

public:
    class const_iterator;
    class iterator {
    private:
        /**
         * TODO add data members
         *   just add whatever you want.
         */
        node *curr;
        size_t pos;
        const list *owner;

    public:
        friend class list;
        friend class list::const_iterator;
        iterator() : curr(nullptr), pos(0), owner(nullptr) {} 
        iterator(node *curr, size_t pos, const list *owner) : curr(curr), pos(pos), owner(owner) {} 
        iterator(const iterator &that) : curr(that.curr), pos(that.pos), owner(that.owner) {} 
        iterator(const const_iterator &that) : curr(that.curr), pos(that.pos), owner(that.owner) {} 
        iterator &operator=(const iterator &that) 
        {
            if(this == &that)
                return *this;
            this->curr = that.curr;
            this->pos = that.pos;
            this->owner = that.owner;
            return *this;
        }
        ~iterator() {} 
        /**
         * iter++
         */
        iterator operator++(int) 
        {
            if(curr->data == nullptr)
                throw invalid_iterator();
            iterator temp = *this;
            // (*this) = iterator(curr->next, pos + 1, owner);
            this->curr = this->curr->next;
            this->pos++;
            return temp;
        }
        /**
         * ++iter
         */
        iterator & operator++() 
        {
            // (*this) = iterator(curr->next, pos + 1, owner);
            this->curr = this->curr->next;
            this->pos++;
            return *this;
        }
        /**
         * iter--
         */
        iterator operator--(int) 
        {
            if(curr->data == nullptr)
                throw invalid_iterator();
            iterator temp = *this;
            // (*this) = iterator(curr->prev, pos - 1, owner);
            this->curr = this->curr->prev;
            this->pos--;
            return temp;
        }
        /**
         * --iter
         */
        iterator & operator--() 
        {
            // (*this) = iterator(curr->prev, pos - 1, owner);
            this->curr = this->curr->prev;
            this->pos--;
            return *this;
        }
        /**
         * TODO *it
         * remember to throw if iterator is invalid
         */
        T & operator *() const 
        {
            if(curr->data == nullptr)
                throw invalid_iterator();
            return *(curr->data);
        }
        /**
         * TODO it->field
         * remember to throw if iterator is invalid
         */
        T * operator ->() const noexcept 
        {
            if(curr->data == nullptr)
                throw invalid_iterator();
            return curr->data;
        }
        /**
         * a operator to check whether two iterators are same (pointing to the same memory).
         */
        bool operator==(const iterator &rhs) const {return this->curr == rhs.curr;}
        bool operator==(const const_iterator &rhs) const {return this->curr == rhs.curr;}
        /**
         * some other operator for iterator.
         */
        bool operator!=(const iterator &rhs) const {return this->curr != rhs.curr;}
        bool operator!=(const const_iterator &rhs) const {return this->curr != rhs.curr;}
    };
    /**
     * TODO
     * has same function as iterator, just for a const object.
     * should be able to construct from an iterator.
     */
    class const_iterator {
    private:
        /**
         * TODO add data members
         *   just add whatever you want.
         */
        node *curr;
        size_t pos;
        const list *owner;

    public:
        friend class list;
        friend class list::iterator;
        const_iterator() : curr(nullptr), pos(0), owner(nullptr) {} 
        const_iterator(node *curr, size_t pos, const list *owner) : curr(curr), pos(pos), owner(owner) {} 
        const_iterator(const iterator &that) : curr(that.curr), pos(that.pos), owner(that.owner) {} 
        const_iterator(const const_iterator &that) : curr(that.curr), pos(that.pos), owner(that.owner) {} 
        const_iterator &operator=(const const_iterator &that) 
        {
            if(this == &that)
                return *this;
            this->curr = that.curr;
            this->pos = that.pos;
            this->owner = that.owner;
            return *this;
        }
        ~const_iterator() {} 
        /**
         * iter++
         */
        const_iterator operator++(int) 
        {
            if(curr->data == nullptr)
                throw invalid_iterator();
            const_iterator temp = *this;
            // (*this) = const_iterator(curr->next, pos + 1, owner);
            this->curr = this->curr->next;
            this->pos++;
            return temp;
        }
        /**
         * ++iter
         */
        const_iterator & operator++() 
        {
            // (*this) = const_iterator(curr->next, pos + 1, owner);
            this->curr = this->curr->next;
            this->pos++;
            return *this;
        }
        /**
         * iter--
         */
        const_iterator operator--(int) 
        {
            if(curr->data == nullptr)
                throw invalid_iterator();
            const_iterator temp = *this;
            // (*this) = const_iterator(curr->prev, pos - 1, owner);
            this->curr = this->curr->prev;
            this->pos--;
            return temp;
        }
        /**
         * --iter
         */
        const_iterator & operator--() 
        {
            // (*this) = const_iterator(curr->prev, pos - 1, owner);
            this->curr = this->curr->next;
            this->pos--;
            return *this;
        }
        /**
         * TODO *it
         * remember to throw if iterator is invalid
         */
        T operator *() const 
        {
            if(curr->data == nullptr)
                throw invalid_iterator();
            return *(curr->data);
        }
        /**
         * TODO it->field
         * remember to throw if iterator is invalid
         */
        T * operator ->() const noexcept 
        {
            if(curr->data == nullptr)
                throw invalid_iterator();
            return curr->data;
        }
        /**
         * a operator to check whether two iterators are same (pointing to the same memory).
         */
        bool operator==(const iterator &rhs) const {return this->curr == rhs.curr;}
        bool operator==(const const_iterator &rhs) const {return this->curr == rhs.curr;}
        /**
         * some other operator for iterator.
         */
        bool operator!=(const iterator &rhs) const {return this->curr != rhs.curr;}
        bool operator!=(const const_iterator &rhs) const {return this->curr != rhs.curr;}
    };
    /**
     * TODO Constructs
     * Atleast two: default constructor, copy constructor
     */
    list() 
    {
        list_size = 0;
        head = new node();
        tail = new node();
        head->prev = nullptr;
        head->next = tail;
        tail->prev = head;
        tail->next = nullptr;
    }
    list(const list &other) 
    {
        // this->list_size = other.list_size;
        this->list_size = 0;
        head = new node();
        tail = new node();
        head->prev = nullptr;
        head->next = tail;
        tail->prev = head;
        tail->next = nullptr;
        for (const_iterator temp = other.cbegin(); temp != other.cend(); temp++)
        {
            push_back(*temp);
        }
    }
    /**
     * TODO Destructor
     */
    virtual ~list() 
    {
        clear();
        delete head;
        delete tail;
    }
    /**
     * TODO Assignment operator
     */
    list &operator=(const list &other) 
    {
        if(this == &other)return *this;
        clear();
        // this->list_size == other.list_size;
        this->list_size = 0;
        for(const_iterator temp = other.cbegin(); temp != other.cend(); temp++)
            push_back(*temp);
        return *this;
    }
    /**
     * access the first / last element
     * throw container_is_empty when the container is empty.
     */
    const T & front() const 
    {
        if (empty())
            throw container_is_empty();
        return *begin();
    }
    const T & back() const 
    {
        if (empty())
            throw container_is_empty();
        return *(--end());
    }
    /**
     * returns an iterator to the beginning.
     */
    iterator begin() const {return iterator(head->next, 1, this);}
    const_iterator cbegin() const {return const_iterator(head->next, 1, this);}
    /**
     * returns an iterator to the end.
     */
    iterator end() const {return iterator(tail, list_size + 1, this);}
    const_iterator cend() const {return const_iterator(tail, list_size + 1, this);}
    /**
     * checks whether the container is empty.
     */
    virtual bool empty() const {return list_size == 0;}
    /**
     * returns the number of elements
     */
    virtual size_t size() const {return list_size;}

    /**
     * clears the contents
     */
    virtual void clear() 
    {
        while (!empty())
            pop_back();
    }
    /**
     * insert value before pos (pos may be the end() iterator)
     * return an iterator pointing to the inserted value
     * throw if the iterator is invalid
     */
    virtual iterator insert(iterator pos, const T &value) 
    {
        if(this != pos.owner)
            throw invalid_iterator();
        list_size++;
        node *cur = new node(pos.curr->prev, pos.curr, value);
        cur->prev->next = cur;
        cur->next->prev = cur;
        return iterator(cur, pos.pos, this);
    }
    /**
     * remove the element at pos (the end() iterator is invalid)
     * returns an iterator pointing to the following element, if pos pointing to the last element, end() will be returned.
     * throw if the container is empty, the iterator is invalid
     */
    virtual iterator erase(iterator pos) 
    {
        if(empty())
            throw container_is_empty();
        if(this != pos.owner)
            throw invalid_iterator();
        pos.curr->prev->next = pos.curr->next;
        pos.curr->next->prev = pos.curr->prev;
        iterator ret = iterator(pos.curr->next, pos.pos, this);
        // pos.curr->~node();
        delete pos.curr;
        list_size--;
        return ret;
    }
    /**
     * adds an element to the end
     */
    void push_back(const T &value) {insert(end(), value);}
    /**
     * removes the last element
     * throw when the container is empty.
     */
    void pop_back() 
    {
        if(empty())
            throw container_is_empty();
        erase(--end());
    }
    /**
     * inserts an element to the beginning.
     */
    void push_front(const T &value) {insert(begin(), value);}
    /**
     * removes the first element.
     * throw when the container is empty.
     */
    void pop_front() 
    {
        if(empty())
            throw container_is_empty();
        erase(begin());
    }
    /**
     * sort the values in ascending order with operator< of T
     */
    void mergesort(iterator s, iterator t)
    {
        if((s==t) || (s.curr->next == t.curr))
            return;
        iterator slow = s;
        iterator fast = s;
        fast++;
        while(fast != t && fast.curr->next != t.curr)
        {
            slow++;
            fast++;
            fast++;
        }
        slow++;
        iterator mems = s;
        --mems;
        mergesort(s, slow);
        ++mems;

        iterator memslow = slow;
        --memslow;
        mergesort(slow, t);
        ++memslow;

        mergebetween(mems, memslow, memslow, t);
    }
    void sort() 
    {
        mergesort(begin(), end());
/*
        char *datas = new char[list_size * sizeof(T)];
        int pos=0;
        T *datasT = (T*)datas;
        for(iterator it = begin(); it != end(); it++, pos++)
            new(datasT + pos) T(*it);
        sjtu::sort(datas, datas + list_size, {std::less<T>()});
        pos = 0;
        for(iterator it = begin(); it != end(); it++, pos++)
            (*it) = *(datasT + pos);
        delete datas;
*/
/*
        clear();
        
        for(int i = 0; i < list_size; i++)
        {
            push_back(*(datasT + i));
            delete (datasT + i);
        }
        delete datas;
*/
    }
    /**
     * merge two sorted lists into one (both in ascending order)
     * compare with operator< of T
     * container other becomes empty after the operation
     * for equivalent elements in the two lists, the elements from *this shall always precede the elements from other
     * the order of equivalent elements of *this and other does not change.
     * no elements are copied or moved
     */
    void mergebetween(iterator ita, iterator itat, iterator itb, iterator itbt)
    {
        iterator t = itbt;
        node tempat(itat.curr->prev, nullptr);
        // node tempbt(itbt.curr->prev, nullptr);
        itat = iterator(&tempat, itat.pos, this);
        // itbt = iterator(&tempbt, itbt.pos, this);
        itat.curr->prev->next = itat.curr;
        // itbt.curr->prev->next = itbt.curr;

        iterator itc(ita.curr->prev, ita.pos - 1, this);

        while(ita != itat || itb != itbt)
        {
            if(itb != itbt && ((ita == itat) || ((*itb) < (*ita))))
            {
                itb.curr->prev = itc.curr;
                itc.curr->next = itb.curr;
                itc = itb;
                ++itb;
            }
            else
            {
                ita.curr->prev = itc.curr;
                itc.curr->next = ita.curr;
                itc = ita;
                ++ita;
            }
        }

        itc.curr->next = t.curr;
        t.curr->prev = itc.curr;
        tempat.~node();
    }
    void merge(list &other) 
    {
        iterator ita = this->begin();
        iterator itat = this->end();

        iterator itb = other.begin();
        iterator itbt = other.end();

        iterator itc(this->head, 0, this);

        while(ita != itat || itb != itbt)
        {
            if(itb != itbt && ((ita == itat) || ((*itb) < (*ita))))
            {
                itb.curr->prev = itc.curr;
                itc.curr->next = itb.curr;
                ++itb;
                ++itc;
            }
            else
            {
                ita.curr->prev = itc.curr;
                itc.curr->next = ita.curr;
                ++ita;
                ++itc;
            }
        }

        itc.curr->next = this->tail;
        this->tail->prev = itc.curr;

        other.head->next = other.tail;
        other.tail->prev = other.head;

        this->list_size += other.list_size;
        other.list_size = 0;
    }
    /**
     * reverse the order of the elements
     * no elements are copied or moved
     */
    void reverse() 
    {
        if(list_size == 0)
            return;
        iterator ita(head, 0, this);
        iterator itb = begin();
        iterator itc = ++begin();
        ita.curr->next = nullptr;
        while(itc != end())
        {
            ita.curr->prev = itb.curr;
            itb.curr->next = ita.curr;
            ita = itb;
            itb = itc;
            itc++;
        }
        ita.curr->prev = itb.curr;
        itb.curr->prev = itc.curr;
        itb.curr->next = ita.curr;
        itc.curr->prev = nullptr;
        itc.curr->next = itb.curr;
        std::swap(head, tail);
    }
    /**
     * remove all consecutive duplicate elements from the container
     * only the first element in each group of equal elements is left
     * use operator== of T to compare the elements.
     */
    void unique() 
    {
        iterator it = begin();
        while(it != end())
        {
            iterator it2 = it;
            it2++;
            while(it2!=end() && *it == *it2)
                it2 = erase(it2);
            it++;
        }
    }
};

}

#endif //SJTU_LIST_HPP
