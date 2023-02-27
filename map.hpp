/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susong <susong@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 11:24:46 by susong            #+#    #+#             */
/*   Updated: 2023/02/27 16:28:09 by susong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
#define MAP_HPP

#include "util.hpp"
#include "rbtree.hpp"
#include "pair.hpp"
#include "vector_iterator.hpp"
#include <limits>

namespace ft{


template < class Key, class T, class Compare = ft::less<Key>, class Allocator = std::allocator<pair<const Key, T> > >
class map{

public:
	typedef Key																key_type;
	typedef T																mapped_type;
	typedef pair<const key_type, mapped_type>								value_type;
	typedef Compare															key_compare;

	typedef Allocator														allocator_type;
	typedef typename Allocator::reference									reference;
	typedef typename Allocator::const_reference								const_reference;
	typedef typename Allocator::pointer										pointer;
	typedef typename Allocator::const_pointer								const_pointer;

	typedef ft::rb_tree<key_type, value_type, key_pair<value_type>, key_compare, allocator_type> tree_type;

	typedef typename tree_type::node_type									node_type;
	typedef typename tree_type::iterator									iterator;
	typedef typename tree_type::const_iterator								const_iterator;
	typedef ft::reverse_iterator<iterator>									reverse_iterator;
	typedef ft::reverse_iterator<const_iterator>							const_reverse_iterator;

	typedef typename allocator_type::difference_type						difference_type;
	typedef typename allocator_type::size_type								size_type;

	class value_compare
	{
		friend class map;
		protected:
		Compare comp;
		value_compare (Compare c) : comp(c) {}

		public:
		typedef bool result_type;
		typedef value_type first_argument_type;
		typedef value_type second_argument_type;
		bool operator() (const value_type& x, const value_type& y) const
		{
			return comp(x.first, y.first);
		}
	};

protected:
	tree_type m_tree;

public:

	explicit map (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type())
	: m_tree(tree_type(comp, alloc)){}

	template <class InputIterator>
	map (InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type())
	: m_tree(tree_type(first, last, comp, alloc)){}

	map (const map& obj){
		if(this != &obj){
			m_tree.clear();
			m_tree.dealloc_nil();
			m_tree = tree_type(obj.begin(), obj.end(), obj.key_comp(), obj.get_allocator());
		}
	}

	~map(){
		m_tree.clear();
		m_tree.dealloc_nil();
	}

	map& operator= (const map& obj){{
		if(this != &obj){
			m_tree.clear();
			m_tree.dealloc_nil();
			m_tree = tree_type(obj.begin(), obj.end(), obj.key_comp(), obj.get_allocator());
		}
		return (*this);
	}}

	iterator begin(){
		return (m_tree.begin());
	}
	const_iterator begin() const{
		return (m_tree.begin());
	}

	const_iterator cbegin() const{
		return (m_tree.begin());
	}

	iterator end(){
		return (m_tree.end());
	}

	const_iterator end() const{
		return (m_tree.end());
	}

	const_iterator cend() const{
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

	const_reverse_iterator crbegin() const{
		return (m_tree.rbegin());
	}

	const_reverse_iterator crend() const{
		return (m_tree.rend());
	}

	bool empty() const{
		return (m_tree.is_empty());
	}

	size_type size() const{
		return (m_tree.get_size());
	}
	size_type max_size() const{

		return(m_tree.max_size());
		// return (std::numeric_limits<std::size_t>::max() / (sizeof(node_type)));
		// return(std::numeric_limits<node_type>::max());
		// return(sizeof(node_type));
		// return(sizeof(mapped_type) + 1);
		// return (m_tree.get_allocator().max_size());
		// return (m_tree.get_allocator().max_size() / (sizeof(mapped_type) + 1));
	}

	mapped_type& operator[] (const key_type& k){
		iterator iter = find(k);
		if ((*iter).first != k)
			iter = insert(iter, value_type(k, mapped_type()));
		return ((*iter).second);
	}

	mapped_type& at (const key_type& k){
		iterator it = find(k);
		// std::cout << k << "    " << (*it).first << std::endl;
		if(it == m_tree.end())
			throw std::out_of_range("Index out of range.");
		return((*it).second);
	}

	const mapped_type& at (const key_type& k) const{
		iterator it = m_tree.find(k);
		if(it == m_tree.end())
			throw std::out_of_range("Index out of range.");
		return((*it).second);
	}


	pair<iterator,bool> insert (const value_type& val){
		if (count(val.first))
			return (ft::make_pair(find(val.first), false));
		return (ft::make_pair(m_tree.insert_node(val), true));
	}

	iterator insert (iterator position, const value_type& val){
		iterator iter;

		if (count(val.first))
			return (find(val.first));
		if (m_tree.is_hint(position, val.first))
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
		key_type k = position.base()->m_data.first;
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
			k = (*first).first;
			first++;
			m_tree.delete_node(m_tree.find_node(k));
		}
	}

	void swap (map& x){
		m_tree.swap(x.m_tree);
	}
	void clear(){
		erase(begin(), end());
	}

	key_compare key_comp() const{
		return (m_tree.get_comp());
	}
	value_compare value_comp() const{
		return (value_compare(m_tree.get_comp()));
	}

	iterator find (const key_type& k){
		return (iterator(m_tree.find_node(k), m_tree.get_root(), m_tree.get_nil()));
	}
	const_iterator find (const key_type& k) const{
		return (const_iterator(m_tree.find_node(k), m_tree.get_root(), m_tree.get_nil()));
	}

	size_type count (const key_type& k) const{
		return(m_tree.is_exist(k));
	}

	iterator lower_bound (const key_type& k){
		return(m_tree.lower_bound(k));
	}
	const_iterator lower_bound (const key_type& k) const{
		return(m_tree.lower_bound(k));
	}

	iterator upper_bound (const key_type& k){
		return(m_tree.upper_bound(k));
	}
	const_iterator upper_bound (const key_type& k) const{
		return(m_tree.upper_bound(k));
	}

	pair<const_iterator,const_iterator> equal_range (const key_type& k) const{
		return (make_pair(lower_bound(k), upper_bound(k)));
	}

	pair<iterator,iterator> equal_range (const key_type& k){
		return (make_pair(lower_bound(k), upper_bound(k)));
	}

	allocator_type get_allocator() const{
		return (m_tree.get_allocator());
	}

};

template <class Key, class T, class Compare, class Alloc>
bool operator== ( const map<Key,T,Compare,Alloc>& left,
                const map<Key,T,Compare,Alloc>& right )
{
    if (left.size() == right.size())
        return (ft::equal(left.begin(), left.end(), right.begin()));
    return (false);

}

template <class Key, class T, class Compare, class Alloc>
bool operator!= ( const map<Key,T,Compare,Alloc>& left, const map<Key,T,Compare,Alloc>& right ){
    return (!(left == right));
}

template <class Key, class T, class Compare, class Alloc>
bool operator<  ( const map<Key,T,Compare,Alloc>& left, const map<Key,T,Compare,Alloc>& right ){
    return (ft::lexicographical_compare(left.begin(), left.end(), right.begin(), right.end()));
}

template <class Key, class T, class Compare, class Alloc>
bool operator<= ( const map<Key,T,Compare,Alloc>& left, const map<Key,T,Compare,Alloc>& right ){
    return (!(right < left));
}

template <class Key, class T, class Compare, class Alloc>
bool operator>  ( const map<Key,T,Compare,Alloc>& left, const map<Key,T,Compare,Alloc>& right ){
    return (right < left);
}

template <class Key, class T, class Compare, class Alloc>
bool operator>= ( const map<Key,T,Compare,Alloc>& left, const map<Key,T,Compare,Alloc>& right ){
    return (!(left < right));
}

template <class Key, class T, class Compare, class Alloc>
void swap (map<Key,T,Compare,Alloc>& x, map<Key,T,Compare,Alloc>& y){
    return (x.swap(y));
}


};

#endif
