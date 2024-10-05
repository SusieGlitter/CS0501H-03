#ifndef SJTU_LIST_HPP
#define SJTU_LIST_HPP

#include "exceptions.hpp"
#include "algorithm.hpp"

#include <climits>
#include <cstddef>
#include <memory>

namespace sjtu {
/**
 * a data container like std::list
 * allocate random memory addresses for data and they are doubly-linked in a list.
 */
    template<typename T>
    class list {
    protected:
        class node {
            std::allocator<T> alloc;
        public:
            T *val;
            node *next, *prev;
            bool sentry;
            explicit node(const T &other) {
                sentry = false;

                char buffer[sizeof(T)];

                val = alloc.allocate(1);
                std::allocator_traits<decltype(alloc)>::construct(alloc, val, other);
                next = prev = nullptr;

            }

            explicit node(node *t) {
                val = nullptr;
                prev = next = nullptr;
                sentry = true;

            }


            node(const node &other) {
                sentry = other.sentry;
                prev = other.prev;
                next = other.next;
                if (other.sentry == false) {
                    val = alloc.allocate(1);
                    std::allocator_traits<decltype(alloc)>::construct(alloc, val, *(other.val));
                } else
                    val = nullptr;

            }

            node &operator=(const node &other){
                if(this == &other)
                    return *this;
                else {
                    if (sentry == false) {
                        std::allocator_traits<decltype(alloc)>::destroy(alloc, val);
                        alloc.deallocate(val, 1);
                    }

                    sentry = other.sentry;
                    prev = other.prev;
                    next = other.next;
                    if (other.sentry == false) {
                        val = alloc.allocate(1);
                        std::allocator_traits<decltype(alloc)>::construct(alloc, val, *(other.val));
                    } else
                        val = nullptr;


                }

                return *this;
            }
            ~node() {
                next = prev = nullptr;
                if (sentry == false) {
                    std::allocator_traits<decltype(alloc)>::destroy(alloc, val);
                    alloc.deallocate(val, 1);
                }

            }

            T &value() {
                return *val;
            }

            T const_value() {
                return *val;
            }
            /**
             * add data members and constructors & destructor
             */

        };

    protected:
        std::allocator<node> memAlloc;

        node *head, *tail;
        int length;
        /**
         * add data members for linked list as protected members
         */

        /**
         * insert node cur before node pos
         * return the inserted node cur
         */
        node *insert(node *pos, node *cur) {
            node *last = pos->prev;

            cur->prev = last;
            cur->next = pos;

            last->next = cur;
            pos->prev = cur;
            length++;
            return cur;
        }

        /**
         * remove node pos from list (no need to delete the node)
         * return the removed node pos
         */
        node *erase(node *pos) {
            length--;
            node *last = pos->prev, *nxt = pos->next;

            last->next = pos->next;
            nxt->prev = last;

            return pos;

        }

    public:
        class const_iterator;

        class iterator {
        public:
           node *listHead;
           node *iter;

        public:
            /**
             * iter++
             */
            explicit iterator(node *it, node *head) {
                iter = it;
                listHead = head;
            }

            iterator(const iterator &other) {
                iter = other.iter;
                listHead=other.listHead;
            }

            explicit iterator(const const_iterator &other) {
                iter = other.iter;
                listHead=other.listHead;
            }

            iterator &operator=(const iterator &other) {
                if (this == &other)
                    return *this;

                listHead=other.listHead;
                iter = other.iter;
                return *this;
            }

            iterator operator++(int) {
                if(iter->next == nullptr || iter->prev == nullptr){

                    throw invalid_iterator();
                }
                iterator ret = *this;
                iter = iter->next;
                return ret;
            }

            /**
             * ++iter
             */
            iterator &operator++() {
                if(iter->next == nullptr){

                    throw invalid_iterator();
                }
                iter = iter->next;
                return *this;
            }

            /**
             * iter--
             */
            iterator operator--(int) {
                if(iter->next == nullptr )
                    throw invalid_iterator();
                iterator ret = *this;
                iter = iter->prev;
                return ret;
            }

            /**
             * --iter
             */
            iterator &operator--() {
                if(iter->prev == nullptr)
                    throw invalid_iterator();
                iter = iter->prev;
                return *this;
            }

            /**
             * TODO *it
             * remember to throw if iterator is invalid
             */
            T &operator*() const {
                if (iter->sentry == true)
                    throw invalid_iterator();

                return iter->value();
            }

            /**
             * TODO it->field
             * remember to throw if iterator is invalid
             */
            T *operator->() const noexcept {
                if (iter->sentry == true )
                    throw invalid_iterator();

                return iter->val;

            }

            /**
             * a operator to check whether two iterators are same (pointing to the same memory).
             */
            bool operator==(const iterator &rhs) const {
                if (iter == rhs.iter)
                    return true;
                else
                    return false;
            }

            bool operator==(const const_iterator &rhs) const {
                if (iter == rhs.iter)
                    return true;
                else
                    return false;

            }

            /**
             * some other operator for iterator.
             */
            bool operator!=(const iterator &rhs) const {
                if (iter != rhs.iter)
                    return true;
                else
                    return false;
            }

            bool operator!=(const const_iterator &rhs) const {
                if (iter != rhs.iter)
                    return true;
                else
                    return false;
            }
        };

        /**
         * TODO
         * has same function as iterator, just for a const object.
         * should be able to construct from an iterator.
         */
        class const_iterator {
        public:
            node *iter;
            const node *listHead;
        public:
            /**
             * iter++
             */
            explicit const_iterator(node *other ,node *head) {
                listHead=head;
                iter = other;
            }

            explicit const_iterator(const iterator &other) {
                listHead=other.listHead;
                iter = other.iter;
            }

            const_iterator(const const_iterator &other) {
                listHead=other.listHead;
                iter = other.iter;
            }

            const_iterator &operator=(const const_iterator &other) {
                if (this == &other)
                    return *this;
                listHead=other.listHead;
                iter = other.iter;
                return *this;
            }

            const_iterator operator++(int) {

                iterator ret = *this;
                iter = iter->next;
                return ret;
            }

            /**
             * ++iter
             */
            const_iterator &operator++() {

                iter = iter->next;
                return *this;
            }

            /**
             * iter--
             */
            const_iterator operator--(int) {
                if(iter->prev == nullptr)
                    throw index_out_of_bound();

                iterator ret = *this;
                iter = iter->prev;
                return ret;
            }

            /**
             * --iter
             */
            const_iterator &operator--() {
                if(iter->prev == nullptr)
                    throw index_out_of_bound();
                iter = iter->prev;
                return *this;
            }

            /**
             * TODO *it
             * remember to throw if iterator is invalid
             */
            T operator*() const {
                if (iter->sentry == true)
                    throw invalid_iterator();

                return iter->const_value();
            }

            /**
             * TODO it->field
             * remember to throw if iterator is invalid
             */
            T *operator->() const noexcept {
                if (iter->sentry == true)
                    throw invalid_iterator();

                return iter->val;

            }

            /**
             * a operator to check whether two iterators are same (pointing to the same memory).
             */
            bool operator==(const iterator &rhs) const {
                if (iter == rhs.iter)
                    return true;
                else
                    return false;
            }

            bool operator==(const const_iterator &rhs) const {
                if (iter == rhs.iter)
                    return true;
                else
                    return false;

            }

            /**
             * some other operator for iterator.
             */
            bool operator!=(const iterator &rhs) const {
                if (iter != rhs.iter)
                    return true;
                else
                    return false;
            }

            bool operator!=(const const_iterator &rhs) const {
                if (iter != rhs.iter)
                    return true;
                else
                    return false;
            }
        };

        /**
         * TODO Constructs
         * Atleast two: default constructor, copy constructor
         */
        list() {
            length = 0;

            head =new node(nullptr);
            tail =new node(nullptr);
            head->next = tail;
            head->prev = nullptr;

            tail->next = nullptr;
            tail->prev = head;
        }

        list(const list &other) {
            head = new node(nullptr);
            tail = new node(nullptr);

            head->next = tail;
            head->prev = nullptr;
            tail->next = nullptr;
            tail->prev = head;

            node *cur = (other.head)->next;

            while (cur != other.tail) {

                node *newInsert = new node(*cur);

                insert(tail,newInsert);
                cur=cur->next;
            }

            length = other.length;
        }

        /**
         * TODO Destructor
         */
        virtual ~list() {
            node *cur = head->next;

            while (cur != tail) {
                node *tmp = cur->next;

                delete cur;
                cur = tmp;
            }

            delete head;
            delete tail;
//
        }

        /**
         * TODO Assignment operator
         */
        list &operator=(const list &other) {
            if (this == &other)
                return *this;

            if (head->next != tail) {
                node *cur = head->next;
                while (cur != tail) {
                    node *tmp = tail->next;
                    delete cur;
                    cur = tmp;
                }

                head->next = tail;
                tail->prev = head;
            }

            node *cur = (other.head)->next;

            while (cur != other.tail) {

                node *newInsert = new node(*cur);

                insert(tail , newInsert);
                cur=cur->next;
            }
            length = other.length;

            return *this;
        }

        /**
         * access the first / last element
         * throw container_is_empty when the container is empty.
         */
        const T &front() const {
            if (head->next == tail || length == 0)
                throw container_is_empty();

            node *cur = head->next;

            return cur->value();
        }

        const T &back() const {
            if (head->next == tail || length == 0)
                throw container_is_empty();

            node *cur = tail->prev;

            return cur->value();
        }

        /**
         * returns an iterator to the beginning.
         */
        iterator begin() {
            node *p = head->next;
            iterator ret(p,head);
            return ret;
        }

        const_iterator cbegin() const {
            const_iterator ret(head->next,head);
            return ret;
        }

        /**
         * returns an iterator to the end.
         */
        iterator end() {
            iterator ret(tail,head);
            return ret;

        }

        const_iterator cend() const {
            const_iterator ret(tail,head);
            return ret;
        }

        /**
         * checks whether the container is empty.
         */
        virtual bool empty() const {
            if (head->next == tail)
                return true;
            return false;
        }

        /**
         * returns the number of elements
         */
        virtual size_t size() const {
            return length;
        }

        /**
         * clears the contents
         */
        virtual void clear() {
            node *cur = head->next;

            while (cur != tail) {
                node *tmp = cur->next;

                delete  cur;
                cur = tmp;
            }

            head->next = tail;
            tail->prev = head;

            length = 0;
        }

        /**
         * insert value before pos (pos may be the end() iterator)
         * return an iterator pointing to the inserted value
         * throw if the iterator is invalid
         */
        virtual iterator insert(iterator pos, const T &value) {
            if(pos.listHead != head)
                throw invalid_iterator();
            node *newNode, *p = pos.iter;
            newNode =new node(value);
            node *ans;
            ans = insert(p, newNode);
            iterator ret(ans,head);

            return ret;
        }

        /**
         * remove the element at pos (the end() iterator is invalid)
         * returns an iterator pointing to the following element, if pos pointing to the last element, end() will be returned.
         * throw if the container is empty, the iterator is invalid
         */
        virtual iterator erase(iterator pos) {
            if ((pos.iter)->sentry == true)
                throw invalid_iterator();
            if (head->next == tail)
                throw container_is_empty();

            iterator ret((pos.iter)->next , head);

            node *cur = erase(pos.iter);
            delete cur;
            return ret;


        }

        /**
         * adds an element to the end
         */
        void push_back(const T &value) {


            node *newNode=new node(value);
            insert(tail, newNode);

        }

        /**
         * removes the last element
         * throw when the container is empty.
         */
        void pop_back() {
            if (head->next == tail || length == 0)
                throw container_is_empty();

            node *cur = erase(tail->prev);
            delete  cur;
        }

        /**
         * inserts an element to the beginning.
         */
        void push_front(const T &value) {

            node *newNode=new node(value);
            insert(head->next, newNode);

        }

        /**
         * removes the first element.
         * throw when the container is empty.
         */
        void pop_front() {
            if (head->next == tail || length == 0)
                throw container_is_empty();

            node *cur;
            cur = erase(head->next);
            delete cur;
        }

        /**
         * sort the values in ascending order with operator< of T
         */





        void mergeArr(T *data[], int left, int mid, int right) {
            T *tmp[right - left +1];
            int i=left , j=mid+1;
            int k=0;
            while(i<=mid && j<=right){
                if(*data[i]<*data[j]){
                    tmp[k]=data[i];
                    k++;
                    i++;
                }
                else {
                    tmp[k]=data[j];
                    k++;
                    j++;
                }
            }

            while(i<=mid){
                tmp[k]=data[i];
                k++;
                i++;
            }

            while(j<=right){
                tmp[k]=data[j];
                k++;
                j++;
            }

            for(int m = left, n = 0; m <= right; m++, n++)//读取临时数组中的数
                data[m] = tmp[n];
        }

        void mergeSort(T *data[], int left, int right) {
            if (left == right)
                return;
            int mid =(left + right )/2;

            mergeSort(data, left, mid);
            mergeSort(data, mid + 1, right);
            mergeArr(data, left, mid, right);
        }


        void sort() {
            node *cur = head->next;
            T *data[length + 10];
            int cnt = 0;
            while (cur != tail) {
                data[cnt++] = cur->val;
                cur = cur->next;
            }

            cur = head->next;
            int tot = 0;

            mergeSort(data, 0, cnt-1);
            while (cur != tail) {
                cur->val = data[tot];
                tot++;
                cur = cur->next;
            }

        }
        /**
         * merge two sorted lists into one (both in ascending order)
         * compare with operator< of T
         * container other becomes empty after the operation
         * for equivalent elements in the two lists, the elements from *this shall always precede the elements from other
         * the order of equivalent elements of *this and other does not change.
         * no elements are copied or moved
         */
        void merge(list &other) {
            node *cur = head->next;


            while (cur != tail) {
                node *other_first = (other.head)->next;
                while(other_first != other.tail && other_first->value() < cur->value()){
                    node *newInsert = other.erase(other_first);
                    insert(cur,newInsert);
                    other_first=(other.head)->next;
                }
                cur=cur->next;
            }

            node *other_first = (other.head)->next;
            while(other_first != other.tail ){
                node *newInsert = other.erase(other_first);
                insert(tail,newInsert);
                other_first=(other.head)->next;
            }
        }

        /**
         * reverse the order of the elements
         * no elements are copied or moved
         */
        void reverse() {
            node *flag = head->next;

            node *cur = tail->prev;

            while (cur != flag) {
                erase(cur);
                insert(flag, cur);
                cur = tail->prev;
            }
        }

        /**
         * remove all consecutive duplicate elements from the container
         * only the first element in each group of equal elements is left
         * use operator== of T to compare the elements.
         */
        void unique() {
            node *cur=head->next;
            while(cur != tail){
                node *tmp=cur->next;
                if(cur!=head->next){
                    node *last=cur->prev;
                    if(last->value() == cur->value()){
                        erase(cur);
                        if(cur!=NULL)
                            delete cur;
                    }
                }
                cur=tmp;
            }
        }

    };

};

#endif //SJTU_LIST_HPP