#ifndef SJTU_VECTOR_HPP
#define SJTU_VECTOR_HPP

#include "exceptions.hpp"

#include <climits>
#include <cstddef>
#include <memory>
namespace sjtu {
/**
 * a data container like std::vector
 * store data in a successive memory and support random access.
 */
    template<typename T>
    class vector {
    public:

        class const_iterator;

        class iterator {
        public:
            using difference_type = std::ptrdiff_t;
            using value_type = T;
            using pointer = T *;
            using reference = T &;
            using iterator_category = std::output_iterator_tag;

        private:
            T *iter;
            T *head;
        public:
            /**
             * return a new iterator which pointer n-next elements
             * as well as operator-
             */

            iterator(T *p, T *head) {
                this->head = head;
                iter = p;
            }

            explicit iterator(T *p) {
                this->head = p;
                iter = p;
            }
            const int position() const{
                int ret=iter-head;
                return ret;
            }
            iterator operator+(const int &n) const {
                iterator ret(iter + n, head);
                return ret;
                //TODO
            }

            iterator operator-(const int &n) const {
                iterator ret(iter - n, head);
                return ret;
                //TODO
            }

            // return the distance between two iterators,
            // if these two iterators point to different vectors, throw invaild_iterator.
            int operator-(const iterator &rhs) const {
                if (head != rhs.head)
                    throw invalid_iterator();
                int ret = iter - rhs.iter;
                return ret;
                //TODO
            }

            iterator &operator+=(const int &n) {
                iter += n;
                return *this;
                //TODO
            }

            iterator &operator-=(const int &n) {
                iter -= n;
                return *this;
                //TODO
            }

            /**
             * TODO iter++
             */
            iterator operator++(int) {
                iterator ret = *this;
                iter++;
                return ret;
            }

            /**
             * TODO ++iter
             */
            iterator &operator++() {
                iter++;
                return *this;
            }

            /**
             * TODO iter--
             */
            iterator operator--(int) {
                iterator ret = *this;
                iter--;
                return ret;
            }

            /**
             * TODO --iter
             */
            iterator &operator--() {
                iter--;
                return *this;
            }

            /**
             * TODO *it
             */
            T &operator*() const {
                return *iter;
            }

            /**
             * a operator to check whether two iterators are same (pointing to the same memory address).
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
                else return false;

            }

            bool operator!=(const const_iterator &rhs) const {
                if (iter != rhs.iter)
                    return true;
                else return false;
            }
        };

        /**
         * TODO
         * has same function as iterator, just for a const object.
         */
        class const_iterator {
        public:
            using difference_type = std::ptrdiff_t;
            using value_type = T;
            using pointer = T *;
            using reference = T &;
            using iterator_category = std::output_iterator_tag;

        private:
            /*TODO*/
            const T *iter;
            const T *head;
        public:
            const_iterator(T *p, T *head) {
                iter = p;
                this->head = head;
            }

            const_iterator(T *p) {
                iter = p;
                head = p;
            }

            const int position() const{
                int ret=iter-head;
                return ret;
            }

            const_iterator operator+(const int &n) const {
                const_iterator ret(iter + n, head);
                return ret;
            }

            const_iterator operator-(const int &n) const {
                const_iterator ret(iter - n, head);
                return ret;
                //TODO
            }

            // return the distance between two iterators,
            // if these two iterators point to different vectors, throw invaild_iterator.
            int operator-(const const_iterator &rhs) const {
                if (head != rhs.head)
                    throw invalid_iterator();
                int ret = iter - rhs.iter;
                return ret;
            }

            const_iterator &operator+=(const int &n) {
                iter += n;
                return *this;
            }

            const_iterator &operator-=(const int &n) {
                iter -= n;
                return *this;
                //TODO
            }

            /**
             * TODO iter++
             */
            const_iterator operator++(int) {
                iterator ret = *this;
                iter++;
                return ret;
            }

            /**
             * TODO ++iter
             */
            const_iterator &operator++() {
                iter++;
                return *this;
            }

            /**
             * TODO iter--
             */
            const_iterator operator--(int) {
                iterator ret = *this;
                iter--;
                return ret;
            }

            /**
             * TODO --iter
             */
            const_iterator &operator--() {
                iter--;
                return *this;
            }

            /**
             * TODO *it
             */
            T operator*() const {
                const T ret = *iter;
                return ret;
            }

            /**
             * a operator to check whether two iterators are same (pointing to the same memory address).
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
                else return false;

            }

            bool operator!=(const const_iterator &rhs) const {
                if (iter != rhs.iter)
                    return true;
                else return false;
            }

        };

        /**
         * TODO Constructs
         * At least two: default constructor, copy constructor
         */

    private:
        long long curLength, maxSize;
        T *data;
        std::allocator<T> memAlloc;

    public:

        vector() {
            curLength = 0;
            maxSize = 2;
            data = memAlloc.allocate(2);
        }

        vector(const vector &other) {
//            if(data!=NULL) {
//                for(int i=0;i<curLength;i++)
//                    std::allocator_traits<decltype(memAlloc)>::destroy(memAlloc,data+i);
//                memAlloc.deallocate(data,maxSize);
//            }
            maxSize = other.maxSize;
            curLength = other.curLength;
            data = memAlloc.allocate(maxSize);
            for (int i = 0; i < curLength; i++){
                std::allocator_traits<decltype(memAlloc)>::construct(memAlloc,data+i,other.data[i]);
            }

        }

        /**
         * TODO Destructor
         */
        ~vector() {
            for(int i=0;i<curLength;i++)
                std::allocator_traits<decltype(memAlloc)>::destroy(memAlloc,data+i);
            memAlloc.deallocate(data,maxSize);
        }


        /**
         * TODO Assignment operator
         */
        vector &operator=(const vector &other) {
            if (this == &other)
                return *this;
            for(int i=0;i<curLength;i++)
                std::allocator_traits<decltype(memAlloc)>::destroy(memAlloc,data+i);
            memAlloc.deallocate(data,maxSize);

            curLength = other.curLength;
            maxSize = other.maxSize;

            data=memAlloc.allocate(maxSize);

            for (int i = 0; i < curLength; i++)
                std::allocator_traits<decltype(memAlloc)>::construct(memAlloc, data + i, other.data[i]);


            return *this;
        }

        /**
         * assigns specified element with bounds checking
         * throw index_out_of_bound if pos is not in [0, size)
         */
        T &at(const size_t &pos) {
            if(pos<0 || pos>=curLength)
                throw index_out_of_bound();
            else
                return data[pos];
        }

        const T &at(const size_t &pos) const {
            if(pos<0 || pos>=curLength)
                throw index_out_of_bound();
            else
                return data[pos];
        }

        /**
         * assigns specified element with bounds checking
         * throw index_out_of_bound if pos is not in [0, size)
         * !!! Pay attentions
         *   In STL this operator does not check the boundary but I want you to do.
         */
        T &operator[](const size_t &pos) {
            if(pos>=curLength || pos<0)
                throw index_out_of_bound();
            else
                return data[pos];
        }

        const T &operator[](const size_t &pos) const {
            if(pos>=curLength || pos<0)
                throw index_out_of_bound();
            else
                return data[pos];

        }

        /**
         * access the first element.
         * throw container_is_empty if size == 0
         */
        const T &front() const {
            if(curLength==0)
                throw container_is_empty();
            return data[0];
        }

        /**
         * access the last element.
         * throw container_is_empty if size == 0
         */
        const T &back() const {
            if(curLength==0)
                throw container_is_empty();
            return data[curLength-1];

        }

        /**
         * returns an iterator to the beginning.
         */
        iterator begin() {
            iterator ret(data,data);
            return ret;
        }

        const_iterator cbegin() const {
            const_iterator ret(data,data);
            return ret;
        }

        /**
         * returns an iterator to the end.
         */
        iterator end() {
            iterator ret(data+curLength,data);
            return ret;
        }

        const_iterator cend() const {
            const_iterator ret(data+curLength,data);
            return ret;

        }

        /**
         * checks whether the container is empty
         */
        bool empty() const {
            if(curLength==0)
                return true;
            else return false;
        }

        /**
         * returns the number of elements
         */
        size_t size() const {
            return curLength;
        }

        /**
         * clears the contents
         */
        void clear() {
            for(int i=0;i<curLength;i++)
                std::allocator_traits<decltype(memAlloc)>::destroy(memAlloc,data+i);
            curLength=0;
            return ;
        }

        /**
         * inserts value before pos
         * returns an iterator pointing to the inserted value.
         */
        void doubleSpace(){
            T *tempData;
            tempData = memAlloc.allocate(maxSize*2);
            for (int i = 0; i < curLength; i++){
                std::allocator_traits<decltype(memAlloc)>::construct(memAlloc, tempData + i, data[i]);
            }
            for (int i = 0; i < curLength; i++){
                std::allocator_traits<decltype(memAlloc)>::destroy(memAlloc, data + i);
            }
//            for(int i=0;i<curLength;i++){
//                new(tempData+i)T(data[i]);
//            }
//            for(int i=0;i<curLength;i++){
//                data[i].~T();
//            }
            memAlloc.deallocate(data, maxSize); // Deallocate previous memory
            maxSize*=2;
            data = tempData;
        }

        iterator insert(iterator pos, const T &value) {
            if(curLength==maxSize)
                doubleSpace();

            int ind=pos.position();
            curLength++;
            if(ind==curLength-1){
                std::allocator_traits<decltype(memAlloc)>::construct(memAlloc,data+curLength-1,value);
                return pos;
            }
            else{
                std::allocator_traits<decltype(memAlloc)>::construct(memAlloc,data+curLength-1,data[curLength-2]);
                for(int i=curLength-1;i>ind;i--)   // multiple assignment?
                    data[i]=data[i-1];
                data[ind]=value;
                return pos;
            }
        }

        /**
         * inserts value at index ind.
         * after inserting, this->at(ind) == value
         * returns an iterator pointing to the inserted value.
         * throw index_out_of_bound if ind > size (in this situation ind can be size because after inserting the size will increase 1.)
         */
        iterator insert(const size_t &ind, const T &value) {
            if(curLength==maxSize)
                doubleSpace();
            curLength++;
            if(ind==curLength-1){
                std::allocator_traits<decltype(memAlloc)>::construct(memAlloc,data+curLength-1,value);
                iterator ret(data+ind,data);
                return ret;
            }
            else {
                std::allocator_traits<decltype(memAlloc)>::construct(memAlloc,data+curLength-1,data[curLength-2]);
                for(int i=curLength-1;i>ind;i--)
                    data[i]=data[i-1];
                iterator ret(data+ind,data);
                return ret;
            }
        }

        /**
         * removes the element at pos.
         * return an iterator pointing to the following element.
         * If the iterator pos refers the last element, the end() iterator is returned.
         */
        iterator erase(iterator pos) {
            int ind=pos.position();
            curLength--;
            for(int i=ind;i<=curLength-1;i++)
                data[i]=data[i+1];
            std::allocator_traits<decltype(memAlloc)>::destroy(memAlloc,data+curLength);
            return pos;

        }

        /**
         * removes the element with index ind.
         * return an iterator pointing to the following element.
         * throw index_out_of_bound if ind >= size
         */
        iterator erase(const size_t &ind) {
            if(ind>=curLength)
                throw index_out_of_bound();
            curLength--;
            for(int i=ind;i<=curLength-1;i++)
                data[i]=data[i+1];

            std::allocator_traits<decltype(memAlloc)>::destroy(memAlloc,data+curLength);
            iterator ret(data+ind,data);
            return ret;

        }

        /**
         * adds an element to the end.
         */
        void push_back(const T &value) {
            if (curLength == maxSize) {
                doubleSpace();
            }
            curLength++;
            std::allocator_traits<decltype(memAlloc)>::construct(memAlloc,data+curLength-1,value);
        }

        /**
         * remove the last element from the end.
         * throw container_is_empty if size() == 0
         */
        void pop_back() {
            if(curLength==0)
                throw container_is_empty();
            curLength--;
            std::allocator_traits<decltype(memAlloc)>::destroy(memAlloc,data+curLength);
        }
    };


}

#endif