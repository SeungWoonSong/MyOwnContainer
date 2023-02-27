#ifndef SET_HPP
#define SET_HPP

#include "rbtree.hpp"
#include "vector_iterator.hpp"
#include "iterator.hpp"
#include "pair.hpp"
#include "util.hpp"

namespace ft{
template < class T, class Compare = ft::less<T>, class Alloc = std::allocator<T> >
class set
{
public:
	typedef T																key_type;
	typedef T																value_type;
	typedef Compare															value_compare;
	typedef Compare															key_compare;
	typedef Alloc															allocator_type;
	typedef typename allocator_type::reference 								reference;
	typedef typename allocator_type::const_reference 						const_reference;
	typedef typename allocator_type::pointer 								pointer;
	typedef typename allocator_type::const_pointer 							const_pointer;

	typedef ft::rb_tree<key_type, value_type, key_with_value<value_type>,
		key_compare, allocator_type>  						tree_type;

	typedef typename tree_type::node_type									node_type;
	typedef typename tree_type::const_iterator								iterator;
	typedef typename tree_type::const_iterator								const_iterator;
	typedef ft::reverse_iterator<iterator>									reverse_iterator;
	typedef ft::reverse_iterator<const_iterator>							const_reverse_iterator;

	typedef typename allocator_type::difference_type						difference_type;
	typedef typename allocator_type::size_type								size_type;

protected:
	tree_type m_tree;

public:
	set (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type())
	: m_tree(tree_type(comp, alloc)) {}

	template <class InputIterator>
	set (InputIterator first, InputIterator last,
		const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type())
	: m_tree(tree_type(first, last, comp, alloc)) {}

	set (const set& x)
	{
		if (this != &x){
		m_tree.clear();
		m_tree.dealloc_nil();
		m_tree = tree_type(x.begin(), x.end(), x.key_comp(), x.get_allocator());
		}
	}

	~set(){
		m_tree.clear();
		m_tree.dealloc_nil();
	}

	set& operator= (const set& x){
		if (this != &x){
			clear();
			m_tree.dealloc_nil();
			m_tree = tree_type(x.begin(), x.end(), x.key_comp(), x.get_allocator());
		}
		return (*this);
	}

	iterator begin(){
		return (m_tree.begin());
	}

	const_iterator begin() const{
		return (m_tree.begin());
	}

	iterator end(){
		return (m_tree.end());
	}

	const_iterator end() const{
		return (m_tree.end());
	}

	reverse_iterator rbegin(){
		return (m_tree.rbegin());
	}

	const_reverse_iterator rbegin() const{
		return (m_tree.rbegin());
	}

	reverse_iterator rend(){
		return (m_tree.rend());
	}

	const_reverse_iterator rend() const{
		return (m_tree.rend());
	}

	bool empty() const { return (m_tree.is_empty()); }
	size_type size() const { return (m_tree.get_size()); }
	size_type max_size() const { return (m_tree.max_size()); }

	pair<iterator,bool> insert (const value_type& val){
		if (count(val))
			return (ft::make_pair(find(val), false));
		return (ft::make_pair(m_tree.insert_node(val), true));
	}

	iterator insert (iterator position, const value_type& val){
		iterator iter;

		if (count(val))
			return (find(val));
		if (m_tree.is_hint(position, val))
			iter = m_tree.insert_node(position, val);
		else
			iter = m_tree.insert_node(val);
		return (iter);
	}

	template <class InputIterator>
	void insert (InputIterator first, InputIterator last){
		while (first != last)
		{
			insert(*first);
			first++;
		}
	}

	void erase (iterator position){
		key_type k = position.base()->m_data;
		if (count(k))
		m_tree.delete_node(m_tree.find_node(k));

	}

	size_type erase (const key_type& k){
		if (count(k))
		{
			m_tree.delete_node(m_tree.find_node(k));
			return (1);
		}
		return (0);
	}

	void erase (iterator first, iterator last){
		key_type k;
		while (first != last)
		{
			k = (*first);
			first++;
			m_tree.delete_node(m_tree.find_node(k));
		}
	}

	void swap (set& obj){
		m_tree.swap(obj.m_tree);
	}

	void clear(){
		erase(begin(), end());
	}

	key_compare key_comp() const { return (m_tree.get_comp()); }

	value_compare value_comp() const { return (m_tree.get_comp()); }

	iterator find (const key_type& k) const{
		return (iterator(m_tree.find_node(k), m_tree.get_root(), m_tree.get_nil()));
	}

	size_type count (const key_type& k) const{
		return (m_tree.is_exist(k));
	}

	iterator lower_bound(const key_type& k){
		return (m_tree.lower_bound(k));
	}

	const_iterator lower_bound(const key_type& k) const{
		return (m_tree.lower_bound(k));
	}

	iterator upper_bound (const key_type& k){
		return (m_tree.upper_bound(k));
	}

	const_iterator upper_bound (const key_type& k) const{
		return (m_tree.upper_bound(k));
	}

	pair<const_iterator,const_iterator> equal_range (const key_type& k) const{
		return (make_pair(lower_bound(k), upper_bound(k)));
	}

	pair<iterator,iterator> equal_range (const key_type& k){
		return (make_pair(lower_bound(k), upper_bound(k)));
	}

	allocator_type get_allocator() const { return (m_tree.get_allocator()); }
};

template <class T, class Compare, class Alloc>
bool operator== ( const set<T,Compare,Alloc>& left,
				const set<T,Compare,Alloc>& right )
{
	if (left.size() == right.size())
		return (ft::equal(left.begin(), left.end(), right.begin()));
	return (false);

}

template <class T, class Compare, class Alloc>
bool operator!= ( const set<T,Compare,Alloc>& left,
				const set<T,Compare,Alloc>& right )
{
	return (!(left == right));
}

template <class T, class Compare, class Alloc>
bool operator<  ( const set<T,Compare,Alloc>& left,
				const set<T,Compare,Alloc>& right )
{
	return (ft::lexicographical_compare(left.begin(), left.end(), right.begin(), right.end()));
}

template <class T, class Compare, class Alloc>
bool operator<= ( const set<T,Compare,Alloc>& left,
				const set<T,Compare,Alloc>& right )
{
	return (!(right < left));
}

template <class T, class Compare, class Alloc>
bool operator>  ( const set<T,Compare,Alloc>& left,
				const set<T,Compare,Alloc>& right )
{
	return (right < left);
}

template <class T, class Compare, class Alloc>
bool operator>= ( const set<T,Compare,Alloc>& left,
				const set<T,Compare,Alloc>& right )
{
	return (!(left < right));
}

template <class T, class Compare, class Alloc>
void swap (set<T,Compare,Alloc>& x, set<T,Compare,Alloc>& y)
{
	return (x.swap(y));
}
};

#endif
