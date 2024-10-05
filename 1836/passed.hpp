#ifndef SJTU_PRIORITY_QUEUE_HPP
#define SJTU_PRIORITY_QUEUE_HPP

#include <cstddef>
#include <functional>
#include "exceptions.hpp"

namespace sjtu {

/**
 * a container like std::priority_queue which is a heap internal.
 */
template<typename T, class Compare = std::less<T>>
class priority_queue {
public:
	class node
	{
	public:
		T *data;
		node* son;
		node* bro;
		size_t size;
		node() :data(nullptr), son(nullptr), bro(nullptr), size(1) {}
		node(const T &data, node *son, node *bro) :data(nullptr), son(son), bro(bro), size(1)
		{
			this->data = new T(data);
		}
		node(const node &that) :son(nullptr), bro(nullptr), size(that.size)
		{
			this->data = new T(*(that.data));
		}
		~node()
		{
			clear();
			son = nullptr;
			bro = nullptr;
		}
		node &operator=(const node &that)
		{
			clear();
			size = that.size;
			this->data = new T(*(that.data));
		}
		T &getdata()
		{
			return *data;
		}
		void clear()
		{
			if(data != nullptr)
				delete data;
			data = nullptr;
		}
		void attach2bro(node *that)
		{
			that->bro = this->bro;
			this->bro = that;
		}
		void attach2son(node *that)
		{
			that->bro = this->son;
			this->son = that;
			this->size += that->size;
		}
	};
	/**
	 * TODO constructors
	 */
	priority_queue() :root(nullptr), nodecnt(0), treecnt(0)
	{
		root = new node();
	}
	priority_queue(node *temp) :root(temp), nodecnt(1), treecnt(0)
	{
		std::swap(temp->son, temp->bro);
		while(temp->bro != nullptr)
		{
			temp = temp->bro;
			nodecnt <<= 1;
			treecnt++;
		}
		nodecnt--;
	}
	priority_queue(const priority_queue &other) :root(nullptr), nodecnt(other.nodecnt), treecnt(other.treecnt)
	{
		root = new node();
		copy(root, other.root);
	}
	/**
	 * TODO deconstructor
	 */
	~priority_queue() 
	{
		cleartree(root);
	}
	void cleartree(node *now)
	{
		if(now->son != nullptr)
			cleartree(now->son);
		if(now->bro != nullptr)
			cleartree(now->bro);
		delete now;
	}
	/**
	 * TODO Assignment operator
	 */
	priority_queue &operator=(const priority_queue &other) 
	{
		if(this == &other)return *this;
		cleartree(root);
		root = new node();
		nodecnt = other.nodecnt;
		treecnt = other.treecnt;
		copy(root, other.root);
		return *this;
	}

	void copy(node* me, node *other) 
	{
		if(other->son != nullptr)
		{
			me->son = new node(*(other->son));
			copy(me->son, other->son);
		}
		if(other->bro != nullptr)
		{
			me->bro = new node(*(other->bro));
			copy(me->bro, other->bro);
		}
	}


	/**
	 * get the top of the queue.
	 * @return a reference of the top element.
	 * throw container_is_empty if empty() returns true;
	 */
	const T & top() const 
	{
		if(empty())
			throw container_is_empty();
		return (*topNode())->getdata();
	}

	node **topNode() const
	{
		node *temp = root->bro;
		node **ret = &(root->bro);
		T maxi = temp->getdata();
		while(temp->bro != nullptr)
		{
			if(stdless(maxi, temp->bro->getdata()))
			{
				maxi = temp->bro->getdata();
				ret = &(temp->bro);
			}
			temp = temp->bro;
		}
		return ret;
	}
	/**
	 * TODO
	 * push new element to the priority queue.
	 */
	void push(const T &e) 
	{
		priority_queue that;
		that.root->bro = new node(e, nullptr, nullptr);
		that.nodecnt = 1;
		that.treecnt = 1;
		merge(that);
	}
	/**
	 * TODO
	 * delete the top element.
	 * throw container_is_empty if empty() returns true;
	 */
	void pop() 
	{
		if(empty())
			throw container_is_empty();
		node **temp = topNode();
		node *thatroot = *temp;
		*temp = thatroot->bro;
		thatroot->clear();
		thatroot->bro = nullptr;
		priority_queue that(thatroot);
		this->nodecnt -= that.nodecnt + 1;
		this->treecnt--;
		merge(that);
	}
	/**
	 * return the number of the elements.
	 */
	size_t size() const 
	{
		return nodecnt;
	}
	/**
	 * check if the container has at least an element.
	 * @return true if it is empty, false if it has at least an element.
	 */
	bool empty() const 
	{
		return nodecnt == 0;
	}
	/**
	 * merge two priority_queues with at least O(logn) complexity.
	 * clear the other priority_queue.
	 */
	void merge(priority_queue &other) 
	{
		if(other.nodecnt == 0)return;
		if(this->nodecnt == 0)
		{
			std::swap(this->root, other.root);
			std::swap(this->nodecnt, other.nodecnt);
			std::swap(this->treecnt, other.treecnt);
			return;
		}
		size_t mergetreecnt = this->treecnt + other.treecnt;
		// node **nodestack = new node*[mergetreecnt];
		node *nodestackroot = new node();

		// size_t *sizestack = new size_t[mergetreecnt];

		long long stacktop = -1;

		// 已优化
		// size_t thissize = 1, othersize = 1;
		// while((thissize <<= 1) <= this->nodecnt);
		// thissize >>=1;
		// while((othersize <<= 1) <= other.nodecnt);
		// othersize >>=1;

		// 归并排序树并且储存大小
		node *pa = this->root->bro, *pb = other.root->bro;
		this->root->bro = nullptr;
		other.root->bro = nullptr;
		while(pa != nullptr || pb != nullptr)
		{
			// if(pa != nullptr && (pb == nullptr || thissize >= othersize))
			if(pa != nullptr && (pb == nullptr || pa->size >= pb->size))
			{
				// 节点栈 链表储存
				stacktop++;
				// nodestack[stacktop] = pa;
				node *temp = pa->bro;
				nodestackroot->attach2bro(pa);

				// 大小栈 数组储存(已优化)
				// sizestack[stacktop] = thissize;
				// thissize >>= 1;
				// while(thissize !=0 && (thissize & this->nodecnt) == 0)thissize >>= 1;

				pa = temp;

				// (nodestack[stacktop])->bro = nullptr;
			}
			else
			{
				// 节点栈 链表储存
				stacktop++;
				// nodestack[stacktop] = pb;
				node *temp =pb->bro;
				nodestackroot->attach2bro(pb);

				// 大小栈 数组储存(已优化)
				// sizestack[stacktop] = othersize;
				// othersize >>= 1;
				// while(othersize !=0 && (othersize & other.nodecnt) == 0)othersize >>= 1;

				pb = temp;

				// (nodestack[stacktop])->bro = nullptr;
			}
		}
		
		// 合并树
		while(stacktop >= 1)
		{
			// if((sizestack[stacktop] == sizestack[stacktop - 1]) && !(stacktop >= 2 && sizestack[stacktop] == sizestack[stacktop - 2]))
			if(nodestackroot->bro->size == nodestackroot->bro->bro->size 
				&& !(stacktop >= 2 && nodestackroot->bro->size == nodestackroot->bro->bro->bro->size))
			{
				// 两颗等大树 判断大小进行合并

				// if(stdless(nodestack[stacktop - 1]->getdata(), nodestack[stacktop]->getdata()))
				// 	std::swap(nodestack[stacktop], nodestack[stacktop - 1]);
				// (nodestack[stacktop - 1])->attach2son(nodestack[stacktop]);

				if(stdless(nodestackroot->bro->getdata(), nodestackroot->bro->bro->getdata()))
				{
					// 深的比较大
					node *temp = nodestackroot->bro->bro;
					nodestackroot->bro->bro->attach2son(nodestackroot->bro);
					nodestackroot->bro = temp;
				}
				else
				{
					// 浅的比较大
					node *temp = nodestackroot->bro->bro->bro;
					nodestackroot->bro->attach2son(nodestackroot->bro->bro);
					nodestackroot->bro->bro = temp;
				}

				mergetreecnt--;
				// sizestack[stacktop - 1] <<= 1;
				stacktop--;
			}
			else
			{
				// 一或三颗等大树 直接挂一颗上去
				node *temp = nodestackroot->bro->bro;

				// this->root->attach2bro(nodestack[stacktop]);
				this->root->attach2bro(nodestackroot->bro);
				stacktop--;

				nodestackroot->bro = temp;
			}
		}

		if(stacktop == 0)
		{
			// this->root->attach2bro(nodestack[stacktop]);
			this->root->attach2bro(nodestackroot->bro);
			stacktop--;
		}

		this->nodecnt += other.nodecnt;
		this->treecnt = mergetreecnt;

		other.nodecnt = 0;
		other.treecnt = 0;

		// delete[] nodestack;
		delete nodestackroot;
		// delete[] sizestack;
	}

private:
	node *root;
	size_t nodecnt;
	size_t treecnt;
	Compare stdless;
};

}

#endif