/**
 * implement a container like std::linked_hashmap
 */
#ifndef SJTU_LINKEDHASHMAP_HPP
#define SJTU_LINKEDHASHMAP_HPP

// only for std::equal_to<T> and std::hash<T>
#include <functional>
#include <cstddef>
#include "utility.hpp"
#include "exceptions.hpp"

namespace sjtu {
    /**
     * In linked_hashmap, iteration ordering is differ from map,
     * which is the order in which keys were inserted into the map.
     * You should maintain a doubly-linked list running through all
     * of its entries to keep the correct iteration order.
     *
     * Note that insertion order is not affected if a key is re-inserted
     * into the map.
     */
    
template<
	class Key,
	class T,
	class Hash = std::hash<Key>, 
	class Equal = std::equal_to<Key>
> class linked_hashmap {
public:


	/**
	 * the internal type of data.
	 * it should have a default constructor, a copy constructor.
	 * You can use sjtu::linked_hashmap as value_type by typedef.
	 */
	typedef pair<const Key, T> value_type;


	class hashmap_node;

	/*
	 * list_node
	*/
	class list_node {
    public:
        /**
         * add data members and constructors & destructor
         */
        list_node *prev;
        list_node *next;
        value_type *data;
		linked_hashmap::hashmap_node *back;

        list_node() : prev(nullptr), next(nullptr), data(nullptr) {}
        list_node(const list_node &that) : prev(that.prev), next(that.next), data(nullptr)
        {
            if (that.data != nullptr)
                this->data = new value_type = *(that.data);
        }
        list_node &operator=(const list_node &that)
        {
            if (this == &that)
                return *this;
            if(this->data != nullptr)
                delete this->data;
            if(that.data != nullptr)
                this->data = new value_type(*(that.data));
            else
                this->data = nullptr;
            return *this;
        }
        list_node(list_node *prev, list_node *next) : prev(prev), next(next), data(nullptr) {}
        list_node(list_node *prev, list_node *next, const value_type &data) : prev(prev), next(next), data(nullptr) 
        {
            this->data = new value_type(data);
        }
        ~list_node() 
        {
            prev = next = nullptr;
            if(this->data != nullptr)
            {
                delete this->data;
            }
        }
		void pointback(linked_hashmap::hashmap_node *back)
		{
			this->back = back;
		}
    };
	class iterator;
	class hashmap_node {
    public:
        /**
         * add data members and constructors & destructor
         */
        hashmap_node *prev;
        hashmap_node *next;
        linked_hashmap::iterator it;

        hashmap_node() : prev(nullptr), next(nullptr) {}
        hashmap_node(const hashmap_node &that) : prev(that.prev), next(that.next), it(that.it) {} 
        hashmap_node &operator=(const hashmap_node &that)
        {
            if (this == &that)
                return *this;
            this->it = that.it;
            return *this;
        }
        hashmap_node(hashmap_node *prev, hashmap_node *next) : prev(prev), next(next) {}
        hashmap_node(hashmap_node *prev, hashmap_node *next, const iterator &it) : prev(prev), next(next), it(it) {} 
        ~hashmap_node() {} 
    };

	class hashmap_bucket{
	public:
		linked_hashmap::hashmap_node *bucket_head;
		linked_hashmap::hashmap_node *bucket_tail;
		hashmap_bucket()
		{
			bucket_head = new linked_hashmap::hashmap_node;
			bucket_tail = new linked_hashmap::hashmap_node;
			bucket_head->prev = nullptr;
			bucket_head->next = bucket_tail;
			bucket_tail->prev = bucket_head;
			bucket_tail->next = nullptr;
		}
		~hashmap_bucket()
		{
			// while(bucket_head->next != bucket_tail)
			// {
			// 	linked_hashmap::hashmap_node *del;
			// 	del = bucket_head->next;
			// 	del->prev->next = del->next;
			// 	del->next->prev = del->prev;
			// 	delete del;
			// }
			delete bucket_head;
			delete bucket_tail;
		}
	};


	/**
	 * see BidirectionalIterator at CppReference for help.
	 *
	 * if there is anything wrong throw invalid_iterator.
	 *     like it = linked_hashmap.begin(); --it;
	 *       or it = linked_hashmap.end(); ++end();
	 */
	class const_iterator;
	class iterator {
	private:
		/**
		 * TODO add data members
		 *   just add whatever you want.
		 */
		list_node *curr;
		size_t pos;
		const linked_hashmap *owner;
	public:
		// The following code is written for the C++ type_traits library.
		// Type traits is a C++ feature for describing certain properties of a type.
		// For instance, for an iterator, iterator::value_type is the type that the 
		// iterator points to. 
		// STL algorithms and containers may use these type_traits (e.g. the following 
		// typedef) to work properly. 
		// See these websites for more information:
		// https://en.cppreference.com/w/cpp/header/type_traits
		// About value_type: https://blog.csdn.net/u014299153/article/details/72419713
		// About iterator_category: https://en.cppreference.com/w/cpp/iterator
		using difference_type = std::ptrdiff_t;
		using value_type = typename linked_hashmap::value_type;
		using pointer = value_type*;
		using reference = value_type&;
		using iterator_category = std::output_iterator_tag;

		friend class linked_hashmap;
		friend class linked_hashmap::const_iterator;
		friend class linked_hashmap::hashmap_node;
		iterator() : curr(nullptr), pos(0), owner(nullptr) {}
        iterator(list_node *curr, size_t pos, const linked_hashmap *owner) : curr(curr), pos(pos), owner(owner) {} 
		iterator(const iterator &other) : curr(other.curr), pos(other.pos), owner(other.owner) {} 
        iterator(const const_iterator &other) : curr(other.curr), pos(other.pos), owner(other.owner) {} 
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
		 * TODO iter++
		 */
		iterator operator++(int) 
		{
			if(pos >= owner->linked_hashmap_size + 1)
                throw invalid_iterator();
            iterator temp = *this;
            this->curr = this->curr->next;
            this->pos++;
            return temp;
		}
		/**
		 * TODO ++iter
		 */
		iterator & operator++() 
		{
			if(pos >= owner->linked_hashmap_size + 1)
                throw invalid_iterator();
            this->curr = this->curr->next;
            this->pos++;
            return *this;
		}
		/**
		 * TODO iter--
		 */
		iterator operator--(int) 
		{
			if(pos == 0)
                throw invalid_iterator();
            iterator temp = *this;
            this->curr = this->curr->prev;
            this->pos--;
            return temp;
		}
		/**
		 * TODO --iter
		 */
		iterator & operator--() 
		{
			if(pos == 0)
                throw invalid_iterator();
			this->curr = this->curr->prev;
            this->pos--;
            return *this;
		}
		value_type & operator*() const 
		{
			if(curr->data == nullptr)
                throw invalid_iterator();
            return *(curr->data);
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

		/**
		 * for the support of it->first. 
		 * See <http://kelvinh.github.io/blog/2013/11/20/overloading-of-member-access-operator-dash-greater-than-symbol-in-cpp/> for help.
		 */
		value_type* operator->() const noexcept 
		{
			if(curr->data == nullptr)
                throw invalid_iterator();
            return curr->data;
		}
	};
 
	class const_iterator {
		// it should has similar member method as iterator.
		//  and it should be able to construct from an iterator.
		private:
		/**
		 * TODO add data members
		 *   just add whatever you want.
		 */
		list_node *curr;
		size_t pos;
		const linked_hashmap *owner;
	public:
		// The following code is written for the C++ type_traits library.
		// Type traits is a C++ feature for describing certain properties of a type.
		// For instance, for an iterator, iterator::value_type is the type that the 
		// iterator points to. 
		// STL algorithms and containers may use these type_traits (e.g. the following 
		// typedef) to work properly. 
		// See these websites for more information:
		// https://en.cppreference.com/w/cpp/header/type_traits
		// About value_type: https://blog.csdn.net/u014299153/article/details/72419713
		// About iterator_category: https://en.cppreference.com/w/cpp/iterator
		using difference_type = std::ptrdiff_t;
		using value_type = typename linked_hashmap::value_type;
		using pointer = value_type*;
		using reference = value_type&;
		using iterator_category = std::output_iterator_tag;

		friend class linked_hashmap;
		friend class linked_hashmap::iterator;
		const_iterator() : curr(nullptr), pos(0), owner(nullptr) {}
        const_iterator(list_node *curr, size_t pos, const linked_hashmap *owner) : curr(curr), pos(pos), owner(owner) {} 
		const_iterator(const iterator &other) : curr(other.curr), pos(other.pos), owner(other.owner) {} 
        const_iterator(const const_iterator &other) : curr(other.curr), pos(other.pos), owner(other.owner) {} 
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
		 * TODO iter++
		 */
		const_iterator operator++(int) 
		{
			if(pos >= owner->linked_hashmap_size + 1)
                throw invalid_iterator();
            const_iterator temp = *this;
            this->curr = this->curr->next;
            this->pos++;
            return temp;
		}
		/**
		 * TODO ++iter
		 */
		const_iterator & operator++() 
		{
			if(pos >= owner->linked_hashmap_size + 1)
                throw invalid_iterator();
            this->curr = this->curr->next;
            this->pos++;
            return *this;
		}
		/**
		 * TODO iter--
		 */
		const_iterator operator--(int) 
		{
			if(pos == 0)
                throw invalid_iterator();
            const_iterator temp = *this;
            this->curr = this->curr->prev;
            this->pos--;
            return temp;
		}
		/**
		 * TODO --iter
		 */
		const_iterator & operator--() 
		{
			if(pos == 0)
                throw invalid_iterator();
			this->curr = this->curr->prev;
            this->pos--;
            return *this;
		}
		value_type operator*() const 
		{
			if(curr->data == nullptr)
                throw invalid_iterator();
            return *(curr->data);
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

		/**
		 * for the support of it->first. 
		 * See <http://kelvinh.github.io/blog/2013/11/20/overloading-of-member-access-operator-dash-greater-than-symbol-in-cpp/> for help.
		 */
		value_type* operator->() const noexcept 
		{
			if(curr->data == nullptr)
                throw invalid_iterator();
            return curr->data;
		}
	};
 
	/**
	 * TODO two constructors
	 */
	linked_hashmap() 
	{
		//linked
		linked_hashmap_size = 0;
        list_head = new list_node();
        list_tail = new list_node();
        list_head->prev = nullptr;
        list_head->next = list_tail;
        list_tail->prev = list_head;
        list_tail->next = nullptr;
		
		//hashmap
		// TODO//
		loadfactor = 4;
		capacity = 1024;
		bucket = new hashmap_bucket[capacity];
	}
	linked_hashmap(const linked_hashmap &other) 
	{
		//linked
		this->linked_hashmap_size = 0;
        list_head = new list_node();
        list_tail = new list_node();
        list_head->prev = nullptr;
        list_head->next = list_tail;
        list_tail->prev = list_head;
        list_tail->next = nullptr;
		//hashmap
		// TODO//
		capacity = other.capacity;
		loadfactor = other.loadfactor;
		bucket = new hashmap_bucket[capacity];

        for (const_iterator temp = other.cbegin(); temp != other.cend(); temp++)
            insert_without_checking(*temp);

	}
 
	/**
	 * TODO assignment operator
	 */
    linked_hashmap &operator=(const linked_hashmap &other) 
    {
		//linked
        if(this == &other)return *this;
        clear();
        this->linked_hashmap_size = 0;
		//hashmap
		// TODO//
		capacity = other.capacity;
		loadfactor = other.loadfactor;
		delete[] bucket;
		bucket = new hashmap_bucket[capacity];

        for(const_iterator temp = other.cbegin(); temp != other.cend(); temp++)
            insert_without_checking(*temp);
        return *this;
    }
 
	/**
	 * TODO Destructors
	 */
	~linked_hashmap() 
	{
		//linked
		clear();
        delete list_head;
        delete list_tail;
		//hashmap
		//TODO//
		delete[] bucket;
	}

	void doublesize()
	{
		hashmap_bucket *new_bucket;
		new_bucket = new hashmap_bucket[2*capacity];

		for (const_iterator temp = cbegin(); temp != cend(); temp++)
		{
			linked_hashmap::hashmap_node *tran = temp.curr->back;
			tran->prev->next = tran->next;
			tran->next->prev = tran->prev;
			size_t ha = std_hash((*(tran->it)).first) & (capacity * 2 - 1);
			tran->prev = new_bucket[ha].bucket_tail->prev;
			tran->next = new_bucket[ha].bucket_tail;
			tran->prev->next = tran;
			tran->next->prev = tran;
		}
		
		delete[] bucket;
		bucket = new_bucket;
		capacity *= 2;
	}
	void halfsize()
	{
		if(capacity <= 1024)
			return;
		hashmap_bucket *new_bucket;
		new_bucket = new hashmap_bucket[capacity / 2];

		for (const_iterator temp = cbegin(); temp != cend(); temp++)
		{
			linked_hashmap::hashmap_node *tran = temp.curr->back;
			tran->prev->next = tran->next;
			tran->next->prev = tran->prev;
			size_t ha = std_hash((*(tran->it)).first) & (capacity / 2 - 1);
			tran->prev = new_bucket[ha].bucket_tail->prev;
			tran->next = new_bucket[ha].bucket_tail;
			tran->prev->next = tran;
			tran->next->prev = tran;
		}
		
		delete[] bucket;
		bucket = new_bucket;
		capacity /= 2;
	}

	
 
	/**
	 * TODO
	 * access specified element with bounds checking
	 * Returns a reference to the mapped value of the element with key equivalent to key.
	 * If no such element exists, an exception of type `index_out_of_bound'
	 */
	T & at(const Key &key) 
	{
		iterator exist = find(key);
		if(exist == end())
			throw index_out_of_bound();
		return (*exist).second;
	}
	const T & at(const Key &key) const 
	{
		iterator exist = find(key);
		if(exist == cend())
			throw index_out_of_bound();
		return (*exist).second;
	}
 
	/**
	 * TODO
	 * access specified element 
	 * Returns a reference to the value that is mapped to a key equivalent to key,
	 *   performing an insertion if such key does not already exist.
	 */
	T & operator[](const Key &key) 
	{
		iterator exist = find(key);
		if(exist == end())
		{
			T t;
			return (*(insert(value_type(key, t)).first)).second;
		}
		return (*exist).second;
	}
 
	/**
	 * behave like at() throw index_out_of_bound if such key does not exist.
	 */
	const T & operator[](const Key &key) const 
	{
		iterator exist = find(key);
		if(exist == cend())
			throw index_out_of_bound();
		return (*exist).second;
	}
 
	/**
	 * return a iterator to the beginning
	 */
	iterator begin() {return iterator(list_head->next, 0, this);}
	const_iterator cbegin() const {return const_iterator(list_head->next, 0, this);}
 
	/**
	 * return a iterator to the end
	 * in fact, it returns past-the-end.
	 */
	iterator end() {return iterator(list_tail, linked_hashmap_size + 1, this);}
	const_iterator cend() const {return const_iterator(list_tail, linked_hashmap_size + 1, this);}
 
	/**
	 * checks whether the container is empty
	 * return true if empty, otherwise false.
	 */
	bool empty() const {return linked_hashmap_size == 0;}
 
	/**
	 * returns the number of elements.
	 */
	size_t size() const {return linked_hashmap_size;}
 
	/**
	 * clears the contents
	 */
	void clear() 
	{
		//linked
		while(!empty())
			erase(--end());
	}
 
	/**
	 * insert an element.
	 * return a pair, the first of the pair is
	 *   the iterator to the new element (or the element that prevented the insertion), 
	 *   the second one is true if insert successfully, or false.
	 */
	pair<iterator, bool> insert(const value_type &value) 
	{
		iterator exist = find(value.first);
		if(exist != end())
			return pair<iterator, bool>(exist, false);
		
		//linked
		linked_hashmap_size++;
		list_node *cur = new list_node((--end()).curr, end().curr, value);
		cur->prev->next = cur;
		cur->next->prev = cur;
		//hashmap
		//TODO
		size_t ha = std_hash(value.first) & (capacity - 1);

		linked_hashmap::hashmap_node *ins = new linked_hashmap::hashmap_node;
		ins->it = linked_hashmap::iterator(cur, linked_hashmap_size, this);
		ins->prev = bucket[ha].bucket_tail->prev;
		ins->next = bucket[ha].bucket_tail;
		ins->prev->next = ins;
		ins->next->prev = ins;

		cur->pointback(ins);

		if((capacity * loadfactor) < linked_hashmap_size)
			doublesize();

		return pair<iterator, bool>(iterator(cur, linked_hashmap_size, this), true);
	}
	pair<iterator, bool> insert_without_checking(const value_type &value) 
	{
		
		//linked
		linked_hashmap_size++;
		list_node *cur = new list_node((--end()).curr, end().curr, value);
		cur->prev->next = cur;
		cur->next->prev = cur;
		//hashmap
		//TODO
		size_t ha = std_hash(value.first) & (capacity - 1);

		linked_hashmap::hashmap_node *ins = new linked_hashmap::hashmap_node;
		ins->it = linked_hashmap::iterator(cur, linked_hashmap_size, this);
		ins->prev = bucket[ha].bucket_tail->prev;
		ins->next = bucket[ha].bucket_tail;
		ins->prev->next = ins;
		ins->next->prev = ins;

		cur->pointback(ins);

		return pair<iterator, bool>(iterator(cur, linked_hashmap_size, this), true);
	}
 
	/**
	 * erase the element at pos.
	 *
	 * throw if pos pointed to a bad element (pos == this->end() || pos points an element out of this)
	 */
	void erase(iterator pos) 
	{
		if(empty())
			throw container_is_empty();
		if(pos == end())
			throw invalid_iterator();
		if(this != pos.owner)
			throw invalid_iterator();
		
		//linked
        pos.curr->prev->next = pos.curr->next;
        pos.curr->next->prev = pos.curr->prev;

		//hashmap
		// TODO//
		linked_hashmap::hashmap_node *del = pos.curr->back;

		del->prev->next = del->next;
		del->next->prev = del->prev;
		delete del;

        delete pos.curr;
        linked_hashmap_size--;

		if((capacity / 2 * loadfactor) > linked_hashmap_size)
			halfsize();
	}
 
	/**
	 * Returns the number of elements with key 
	 *   that compares equivalent to the specified argument,
	 *   which is either 1 or 0 
	 *     since this container does not allow duplicates.
	 */
	size_t count(const Key &key) const 
	{
		const_iterator exist = find(key);
		if(exist != cend())
			return 1;
		return 0;
	}
 
	/**
	 * Finds an element with key equivalent to key.
	 * key value of the element to search for.
	 * Iterator to an element with key equivalent to key.
	 *   If no such element is found, past-the-end (see end()) iterator is returned.
	 */
	iterator find(const Key &key) 
	{
		size_t ha = std_hash(key) & (capacity - 1);
		for(linked_hashmap::hashmap_node *i = bucket[ha].bucket_head->next; i != bucket[ha].bucket_tail; i = i->next)
		{
			linked_hashmap::iterator it = i->it;
			if(std_equal((*it).first, key))
				return it;
		}
		return end();
	}
	const_iterator find(const Key &key) const 
	{
		size_t ha = std_hash(key) & (capacity - 1);
		for(linked_hashmap::hashmap_node *i = bucket[ha].bucket_head->next; i != bucket[ha].bucket_tail; i = i->next)
		{
			linked_hashmap::const_iterator it = i->it;
			if(std_equal((*it).first, key))
				return it;
		}
		return cend();
	}


private:
	list_node *list_head;
	list_node *list_tail;
	size_t linked_hashmap_size;

	hashmap_bucket *bucket;
	size_t capacity;
	double loadfactor;

	Hash std_hash;
	Equal std_equal;
};

}

#endif
