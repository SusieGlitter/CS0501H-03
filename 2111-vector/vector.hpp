#ifndef SJTU_VECTOR_HPP
#define SJTU_VECTOR_HPP

#include "exceptions.hpp"

#include <climits>
#include <cstddef>

namespace sjtu
{
/**
 * a data container like std::vector
 * store data in a successive memory and support random access.
 */
template <typename T>
class vector
{
public:
	/**
	 * TODO
	 * a type for actions of the elements of a vector, and you should write
	 *   a class named const_iterator with same interfaces.
	 */
	/**
	 * you can see RandomAccessIterator at CppReference for help.
	 */
	class const_iterator;
	class iterator
	{
		// The following code is written for the C++ type_traits library.
		// Type traits is a C++ feature for describing certain properties of a type.
		// For instance, for an iterator, iterator::value_type is the type that the
		// iterator points to.
		// STL algorithms and containers may use these type_traits (e.g. the following
		// typedef) to work properly. In particular, without the following code,
		// @code{std::sort(iter, iter1);} would not compile.
		// See these websites for more information:
		// https://en.cppreference.com/w/cpp/header/type_traits
		// About value_type: https://blog.csdn.net/u014299153/article/details/72419713
		// About iterator_category: https://en.cppreference.com/w/cpp/iterator
	public:
		using difference_type = std::ptrdiff_t;
		using value_type = T;
		using pointer = T *;
		using reference = T &;
		using iterator_category = std::output_iterator_tag;

	private:
		/**
		 * TODO add data members
		 *   just add whatever you want.
		 */
		T* curr;
		size_t pos;
	public:
		/**
		 * return a new iterator which pointer n-next elements
		 * as well as operator-
		 */
		iterator(T *curr, size_t pos) : curr(curr), pos(pos) {}
		iterator(const iterator &other) : curr(other.curr), pos(other.pos) {}
		iterator operator+(const int &n) const
		{
			// TODO
			return iterator(curr + n, pos + n);
		}
		iterator operator-(const int &n) const
		{
			// TODO
			return iterator(curr - n, pos - n);
		}
		// return the distance between two iterators,
		// if these two iterators point to different vectors, throw invaild_iterator.
		int operator-(const iterator &rhs) const
		{
			// TODO
			int ret = (*this).pos - rhs.pos;
			if (ret != (curr) - &(*rhs)) throw("invaild_iterator");
			return ret;
		}
		iterator &operator+=(const int &n)
		{
			// TODO
			(*this) = iterator(curr + n, pos + n);
			return *this;
		}
		iterator &operator-=(const int &n)
		{
			// TODO
			(*this) = iterator(curr - n, pos - n);
			return *this;
		}
		/**
		 * TODO iter++
		 */
		iterator operator++(int) 
		{
			iterator temp = *this;
			++(*this);
			return temp;
		}
		/**
		 * TODO ++iter
		 */
		iterator &operator++() 
		{
			(*this) = iterator(curr + 1, pos + 1);
			return *this;
		}
		/**
		 * TODO iter--
		 */
		iterator operator--(int) 
		{
			iterator temp = *this;
			--(*this);
			return temp;
		}
		/**
		 * TODO --iter
		 */
		iterator &operator--() 
		{
			(*this) = iterator(curr - 1, pos - 1);
			return *this;
		}
		/**
		 * TODO *it
		 */
		T &operator*() const
		{
			return *curr;
		}
		/**
		 * a operator to check whether two iterators are same (pointing to the same memory address).
		 */
		bool operator==(const iterator &rhs) const { return &curr == &(*rhs); }
		bool operator==(const const_iterator &rhs) const { return &curr == &(*rhs); }
		/**
		 * some other operator for iterator.
		 */
		bool operator!=(const iterator &rhs) const { return curr != &(*rhs); }
		bool operator!=(const const_iterator &rhs) const { return curr != &(*rhs); }
	};
	/**
	 * TODO
	 * has same function as iterator, just for a const object.
	 */
	class const_iterator
	{
	public:
		using difference_type = std::ptrdiff_t;
		using value_type = T;
		using pointer = T *;
		using reference = T &;
		using iterator_category = std::output_iterator_tag;

	private:
		/*TODO*/
		T* curr;
		size_t pos;
	public:
		const_iterator(T *curr, size_t pos) : curr(curr), pos(pos) {}
		const_iterator(const const_iterator &other) : curr(other.curr), pos(other.pos) {}
		const_iterator operator+(const int &n) const
		{
			// TODO
			return const_iterator(curr + n, pos + n);
		}
		const_iterator operator-(const int &n) const
		{
			// TODO
			return const_iterator(curr - n, pos - n);
		}

		int operator-(const const_iterator &rhs) const
		{
			// TODO
			int ret = (*this).pos - rhs.pos;
			if (ret != (curr) - &(*rhs)) throw("invaild_iterator");
			return ret;
		}
		const_iterator &operator+=(const int &n)
		{
			// TODO
			(*this) = const_iterator(curr + n, pos + n);
			return *this;
		}
		const_iterator &operator-=(const int &n)
		{
			// TODO
			(*this) = const_iterator(curr - n, pos - n);
			return *this;
		}

		const_iterator operator++(int) 
		{
			const_iterator temp = *this;
			++(*this);
			return temp;
		}
		const_iterator &operator++() 
		{
			(*this) = const_iterator(curr + 1, pos + 1);
			return *this;
		}
		const_iterator operator--(int) 
		{
			const_iterator temp = *this;
			--(*this);
			return temp;
		}
		const_iterator &operator--() 
		{
			(*this) = const_iterator(curr - 1, pos - 1);
			return *this;
		}
		T &operator*() const
		{
			return *curr;
		}

		bool operator==(const iterator &rhs) const { return curr == &(*rhs); }
		bool operator==(const const_iterator &rhs) const { return curr == &(*rhs); }
		
		bool operator!=(const iterator &rhs) const { return curr != &(*rhs); }
		bool operator!=(const const_iterator &rhs) const { return curr != &(*rhs); }
	};
	/**
	 * TODO Constructs
	 * At least two: default constructor, copy constructor
	 */
	vector() : maxLen(1), len(0)
	{
		data = alloc.allocate(maxLen);
		return;
	}
	vector(const vector &other) : maxLen(other.maxLen), len(other.len)
	{
		data = alloc.allocate(maxLen);
		iterator it_this = this->begin();
		for (const_iterator it_other = other.cbegin(); it_other != other.cend(); it_other++)
		{
			std::allocator_traits<decltype(alloc)>::construct(alloc, &*it_this, *it_other);
			it_this++;
		}
	}
	/**
	 * TODO Destructor
	 */
	~vector() 
	{
		clear();
		alloc.deallocate(data, maxLen);
	}

	/**
	 * TODO Assignment operator
	 */
	vector &operator=(const vector &other) 
	{
		if (this == &other) return *this;
		clear();
		alloc.deallocate(data, maxLen);
		maxLen = other.maxLen;
		len = other.len;
		data = alloc.allocate(maxLen);
		iterator it_this = this->begin();
		for (const_iterator it_other = other.cbegin(); it_other != other.cend(); it_other++)
		{
			std::allocator_traits<decltype(alloc)>::construct(alloc, &*it_this, *it_other);
			it_this++;
		}
		return *this;
	}
	/**
	 * assigns specified element with bounds checking
	 * throw index_out_of_bound if pos is not in [0, size)
	 */
	T &at(const size_t &pos) 
	{
		if (pos < 0 || pos >= len) throw("index_out_of_bound");
		return data[pos];
	}
	const T &at(const size_t &pos) const 
	{
		if (pos < 0 || pos >= len) throw("index_out_of_bound");
		return data[pos];
	}
	/**
	 * assigns specified element with bounds checking
	 * throw index_out_of_bound if pos is not in [0, size)
	 * !!! Pay attentions
	 *   In STL this operator does not check the boundary but I want you to do.
	 */
	T &operator[](const size_t &pos) 
	{
		if (pos < 0 || pos >= len) throw("index_out_of_bound");
		return data[pos];
	}
	const T &operator[](const size_t &pos) const 
	{
		if (pos < 0 || pos >= len) throw("index_out_of_bound");
		return data[pos];
	}
	/**
	 * access the first element.
	 * throw container_is_empty if size == 0
	 */
	const T &front() const 
	{
		if (len == 0) throw("container_is_empty");
		return data[0];
	}
	/**
	 * access the last element.
	 * throw container_is_empty if size == 0
	 */
	const T &back() const 
	{
		if (len == 0) throw("container_is_empty");
		return data[len-1];
	}
	/**
	 * returns an iterator to the beginning.
	 */
	iterator begin() 
	{
		return iterator(data, 0);
	}
	const_iterator cbegin() const 
	{
		return const_iterator(data, 0);
	}
	/**
	 * returns an iterator to the end.
	 */
	iterator end() 
	{
		return iterator(data + len, len);
	}
	const_iterator cend() const 
	{
		return const_iterator(data + len, len);
	}
	/**
	 * checks whether the container is empty
	 */
	bool empty() const 
	{
		return len == 0;
	}
	/**
	 * returns the number of elements
	 */
	size_t size() const 
	{
		return len;
	}
	/**
	 * clears the contents
	 */
	void clear() 
	{
		for(iterator it = begin(); it !=end(); it++)
		{
			std::allocator_traits<decltype(alloc)>::destroy(alloc,&*it);
		}
		len = 0;
	}
	/**
	 * inserts value before pos
	 * returns an iterator pointing to the inserted value.
	 */
	iterator insert(iterator pos, const T &value) 
	{
		if (maxLen == len)
		{
			size_t ind = pos - begin();
			doubleSpace();
			pos = iterator(data + ind, ind);
		}
		std::allocator_traits<decltype(alloc)>::construct(alloc, &*end(), *(end() - 1));
		for (iterator it = end() -1; it != pos; it--)
		{
			*it = *(it - 1);
		}
		*pos = value;
		len++;
		return pos;
	}
	/**
	 * inserts value at index ind.
	 * after inserting, this->at(ind) == value
	 * returns an iterator pointing to the inserted value.
	 * throw index_out_of_bound if ind > size (in this situation ind can be size because after inserting the size will increase 1.)
	 */
	iterator insert(const size_t &ind, const T &value) 
	{
		if (ind > len) throw("index_out_of_bound");
		if (maxLen == len) doubleSpace();
		iterator pos(data + ind, ind);
		std::allocator_traits<decltype(alloc)>::construct(alloc, &*end(), *(end() - 1));
		for (iterator it = end() - 1; it != pos; it--)
		{
			*it = *(it - 1);
		}
		*pos = value;
		len++;
		return pos;
	}
	/**
	 * removes the element at pos.
	 * return an iterator pointing to the following element.
	 * If the iterator pos refers the last element, the end() iterator is returned.
	 */
	iterator erase(iterator pos) 
	{
		for (iterator it = pos; it != end() - 1; it++)
		{
			*it = *(it + 1);
		}
		len--;
		std::allocator_traits<decltype(alloc)>::destroy(alloc,&*end());
		return pos;
	}
	/**
	 * removes the element with index ind.
	 * return an iterator pointing to the following element.
	 * throw index_out_of_bound if ind >= size
	 */
	iterator erase(const size_t &ind) 
	{
		if (ind >= len) throw("index_out_of_bound");
		iterator pos(data + ind, ind);
		for (iterator it = pos; it != end() - 1; it++)
		{
			*it = *(it + 1);
		}
		len--;
		std::allocator_traits<decltype(alloc)>::destroy(alloc,&*end());
		return pos;
	}
	/**
	 * adds an element to the end.
	 */
	void push_back(const T &value) 
	{
		if(maxLen == len) doubleSpace();
		std::allocator_traits<decltype(alloc)>::construct(alloc, &*end(), value);
		len++;
	}
	/**
	 * remove the last element from the end.
	 * throw container_is_empty if size() == 0
	 */
	void pop_back() 
	{
		if (len == 0) throw("container_is_empty");
		len--;
		std::allocator_traits<decltype(alloc)>::destroy(alloc,&*end());
	}

private:
	size_t maxLen;
	size_t len;
	T *data;
	std::allocator<T> alloc;

	void doubleSpace() 
	{
		// TODO
		T *tempData;
		size_t tempLen = len;
		tempData = alloc.allocate(maxLen * 2);
		const_iterator it_temp(tempData, 0);
		for(iterator it = begin(); it != end(); it++)
		{
			std::allocator_traits<decltype(alloc)>::construct(alloc, &*it_temp, *it);
			it_temp++;
		}
		clear();
		alloc.deallocate(data, maxLen);
		maxLen *= 2;
		len = tempLen;
		data = tempData;
	}
};

}

#endif
