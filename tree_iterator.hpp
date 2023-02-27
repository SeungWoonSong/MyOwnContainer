#ifndef TREE_ITERATOR_HPP
#define TREE_ITERATOR_HPP

#include "rbtree.hpp"

namespace ft{

template <typename T, typename Ref, typename Point>
class rb_tree_iterator
{
public:
	typedef ft::bidirectional_iterator_tag		        iterator_category;
	typedef T			        						value_type;
	typedef ptrdiff_t                                   difference_type;
	typedef Point			        					pointer;
	typedef Ref		        							reference;

	typedef rb_tree_node<value_type>                    node_type;
	typedef rb_tree_node<value_type>*                   node_ptr;

protected:
	node_ptr    m_node;
	node_ptr    m_root;
	node_ptr    m_nil;

public:
	rb_tree_iterator() : m_node(), m_nil() {}
	rb_tree_iterator(node_ptr node, node_ptr root, node_ptr NIL)
	{
		m_node = node;
		m_root = root;
		m_nil = NIL;
	}

	rb_tree_iterator(const rb_tree_iterator<value_type, value_type&, value_type*>& node)
	: m_node(node.base()), m_root(node.get_root()), m_nil(node.get_nil()) {}


	reference operator*() const { return ((m_node->_data)); }
	pointer operator->() const { return (&(operator*())); }

	rb_tree_iterator& operator++()
	{
		increment();
		return *this;
	}

	rb_tree_iterator operator++(int)
	{
		rb_tree_iterator temp = *this;
		increment();
		return (temp);
	}

	rb_tree_iterator& operator--()
	{
		decrement();
		return *this;
	}

	rb_tree_iterator operator--(int)
	{
		rb_tree_iterator temp = *this;
		decrement();
		return (temp);
	}

	node_ptr base() const { return (m_node); }
	node_ptr get_root() const { return (m_root); }
	node_ptr get_nil() const { return (m_nil); }

	private:
	void    increment()
	{
		if (m_node == m_nil)
			m_node = minimum(m_root, m_nil);
		if (m_node->_right != m_nil)
		{
			m_node = m_node->_right;
			while (m_node->_left != m_nil)
				m_node = m_node->_left;
		}
		else
		{
			node_ptr y = m_node->_parent;
			while (m_node == y->_right && y != m_nil)
			{
				m_node = y;
				y = y->_parent;
			}
			m_node = y;
		}
	}

	void    decrement()
	{
		if (m_node == m_nil)
			m_node = maximum(m_root, m_nil);
		else
		{
			if (m_node->_left != m_nil)
			{
				m_node = m_node->_left;
				while (m_node->_right != m_nil)
					m_node = m_node->_right;
			}
			else
			{
				node_ptr y = m_node->_parent;
				while (m_node == y->_left && y != m_nil)
				{
					m_node = y;
					y = y->_parent;
				}
				m_node = y;
			}
		}
	}

	node_ptr minimum(node_ptr node, node_ptr m_nil)
	{
		node_ptr x = node;
		while (x->_left != m_nil)
			x = x->_left;
		return (x);
	}

	node_ptr maximum(node_ptr node, node_ptr m_nil)
	{
		node_ptr x = node;
		while (x->_right != m_nil)
			x = x->_right;
		return (x);
	}

};

template<class Iterator1, class Iterator2>
bool operator==(const rb_tree_iterator<Iterator1, Iterator1&, Iterator1*>& x,
				const rb_tree_iterator<Iterator2, Iterator2&, Iterator2*>& y)
{
	return (x.base() == y.base());
}

template<class Iterator1, class Iterator2>
bool operator==(const rb_tree_iterator<Iterator1, const Iterator1&, const Iterator1*>& x,
				const rb_tree_iterator<Iterator2, Iterator2&, Iterator2*>& y)
{
	return (x.base() == y.base());
}

template<class Iterator1, class Iterator2>
bool operator==(const rb_tree_iterator<Iterator1, Iterator1&, Iterator1*>& x,
				const rb_tree_iterator<Iterator2, const Iterator2&, const Iterator2*>& y)
{
	return (x.base() == y.base());
}

template<class Iterator1, class Iterator2>
bool operator==(const rb_tree_iterator<Iterator1, const Iterator1&, const Iterator1*>& x,
				const rb_tree_iterator<Iterator2, const Iterator2&, const Iterator2*>& y)
{
	return (x.base() == y.base());
}

template<class Iterator1, class Iterator2>
bool operator!=(const rb_tree_iterator<Iterator1, Iterator1&, Iterator1*>& x,
				const rb_tree_iterator<Iterator2, Iterator2&, Iterator2*>& y)
{
	return (x.base() != y.base());
}

template<class Iterator1, class Iterator2>
bool operator!=(const rb_tree_iterator<Iterator1, const Iterator1&, const Iterator1*>& x,
				const rb_tree_iterator<Iterator2, Iterator2&, Iterator2*>& y)
{
	return (x.base() != y.base());
}

template<class Iterator1, class Iterator2>
bool operator!=(const rb_tree_iterator<Iterator1, Iterator1&, Iterator1*>& x,
				const rb_tree_iterator<Iterator2, const Iterator2&, const Iterator2*>& y)
{
	return (x.base() != y.base());
}

template<class Iterator1, class Iterator2>
bool operator!=(const rb_tree_iterator<Iterator1, const Iterator1&, const Iterator1*>& x,
				const rb_tree_iterator<Iterator2, const Iterator2&, const Iterator2*>& y)
{
	return (x.base() != y.base());
}





};

#endif
