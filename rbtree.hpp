#ifndef RBTREE_HPP
#define RBTREE_HPP

#include <iostream>
#include "util.hpp"
#include "iterator.hpp"
// #include "tree_iterator.hpp"
#include "vector_iterator.hpp"
#include <memory>
#include <exception>
#include <algorithm>
#include <iostream>
#include <cstddef>

namespace ft{



enum rb_tree_color{
    RED,
    BLACK
};

template < class T >
struct rb_tree_node{
	typedef T                           value_type;
	typedef T*                          value_ptr;
	typedef rb_tree_node<value_type>    node_type;
	typedef node_type*                  node_ptr;
	typedef const node_type*            const_node_ptr;

	rb_tree_color   m_color;
	node_ptr        m_parent;
	node_ptr        m_left;
	node_ptr        m_right;
	value_type      m_data;

	rb_tree_node() {}
	rb_tree_node(rb_tree_color color, node_ptr parent, node_ptr left, node_ptr right, value_type data)
	: m_color(color), m_parent(parent), m_left(left), m_right(right), m_data(data) {}
	~rb_tree_node() {}

};


template <typename T, typename Ref, typename Point>
class rb_tree_iterator{
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
	rb_tree_iterator(node_ptr node, node_ptr root, node_ptr NIL){
		m_node = node;
		m_root = root;
		m_nil = NIL;
	}

	rb_tree_iterator(const rb_tree_iterator<value_type, value_type&, value_type*>& node)
	: m_node(node.base()), m_root(node.get_root()), m_nil(node.get_nil()) {}


	reference operator*() const { return ((m_node->m_data)); }
	pointer operator->() const { return (&(operator*())); }

	rb_tree_iterator& operator++(){
		increment();
		return *this;
	}

	rb_tree_iterator operator++(int){
		rb_tree_iterator temp = *this;
		increment();
		return (temp);
	}

	rb_tree_iterator& operator--(){
		decrement();
		return *this;
	}

	rb_tree_iterator operator--(int){
		rb_tree_iterator temp = *this;
		decrement();
		return (temp);
	}

	node_ptr base() const { return (m_node); }
	node_ptr get_root() const { return (m_root); }
	node_ptr get_nil() const { return (m_nil); }

	private:
	void increment(){
		if (m_node == m_nil)
			m_node = minimum(m_root, m_nil);
		if (m_node->m_right != m_nil){
			m_node = m_node->m_right;
			while (m_node->m_left != m_nil)
				m_node = m_node->m_left;
		}
		else{
			node_ptr y = m_node->m_parent;
			while (m_node == y->m_right && y != m_nil){
				m_node = y;
				y = y->m_parent;
			}
			m_node = y;
		}
	}

	void decrement(){
		if (m_node == m_nil)
			m_node = maximum(m_root, m_nil);
		else{
			if (m_node->m_left != m_nil){
				m_node = m_node->m_left;
				while (m_node->m_right != m_nil)
					m_node = m_node->m_right;
			}
			else{
				node_ptr y = m_node->m_parent;
				while (m_node == y->m_left && y != m_nil){
					m_node = y;
					y = y->m_parent;
				}
				m_node = y;
			}
		}
	}

	node_ptr minimum(node_ptr node, node_ptr m_nil){
		node_ptr x = node;
		while (x->m_left != m_nil)
			x = x->m_left;
		return (x);
	}

	node_ptr maximum(node_ptr node, node_ptr m_nil){
		node_ptr x = node;
		while (x->m_right != m_nil)
			x = x->m_right;
		return (x);
	}

};

template<class Iterator1, class Iterator2>
bool operator==(const rb_tree_iterator<Iterator1, Iterator1&, Iterator1*>& x,
				const rb_tree_iterator<Iterator2, Iterator2&, Iterator2*>& y)
{return (x.base() == y.base());}

template<class Iterator1, class Iterator2>
bool operator==(const rb_tree_iterator<Iterator1, const Iterator1&, const Iterator1*>& x,
				const rb_tree_iterator<Iterator2, Iterator2&, Iterator2*>& y)
{return (x.base() == y.base());}

template<class Iterator1, class Iterator2>
bool operator==(const rb_tree_iterator<Iterator1, Iterator1&, Iterator1*>& x,
				const rb_tree_iterator<Iterator2, const Iterator2&, const Iterator2*>& y)
{return (x.base() == y.base());}

template<class Iterator1, class Iterator2>
bool operator==(const rb_tree_iterator<Iterator1, const Iterator1&, const Iterator1*>& x,
				const rb_tree_iterator<Iterator2, const Iterator2&, const Iterator2*>& y)
{return (x.base() == y.base());}

template<class Iterator1, class Iterator2>
bool operator!=(const rb_tree_iterator<Iterator1, Iterator1&, Iterator1*>& x,
				const rb_tree_iterator<Iterator2, Iterator2&, Iterator2*>& y)
{return (x.base() != y.base());}

template<class Iterator1, class Iterator2>
bool operator!=(const rb_tree_iterator<Iterator1, const Iterator1&, const Iterator1*>& x,
				const rb_tree_iterator<Iterator2, Iterator2&, Iterator2*>& y)
{return (x.base() != y.base());}

template<class Iterator1, class Iterator2>
bool operator!=(const rb_tree_iterator<Iterator1, Iterator1&, Iterator1*>& x,
				const rb_tree_iterator<Iterator2, const Iterator2&, const Iterator2*>& y)
{return (x.base() != y.base());}

template<class Iterator1, class Iterator2>
bool operator!=(const rb_tree_iterator<Iterator1, const Iterator1&, const Iterator1*>& x,
				const rb_tree_iterator<Iterator2, const Iterator2&, const Iterator2*>& y)
{return (x.base() != y.base());}

template <typename Key, typename T, typename KeyOfValue, typename Compare, typename Allocator>
class rb_tree
{
public:
typedef Key																key_type;
	typedef T															value_type;
	typedef Allocator													allocator_type;
	typedef Compare														key_compare;
	typedef ft::rb_tree_node<value_type>								node_type;
	typedef typename allocator_type::template rebind<node_type>::other	node_allocator_type;
	typedef typename node_type::node_ptr								node_ptr;
	typedef typename node_type::const_node_ptr							const_node_ptr;

	typedef ft::rb_tree_iterator<T, T&, T*>								iterator;
	typedef ft::rb_tree_iterator<T, const T&, const T*>					const_iterator;
	typedef ft::reverse_iterator<iterator>								reverse_iterator;
	typedef ft::reverse_iterator<const_iterator>						const_reverse_iterator;

protected:
	node_allocator_type													m_alloc;
	node_ptr															m_root;
	node_ptr															m_nil;
	key_compare															m_comp;
	size_t																m_size;

public:
	rb_tree() :  m_size(0){
		m_nil = alloc_node(BLACK, value_type());
		m_nil->m_left = m_nil;
		m_nil->m_right = m_nil;
		m_nil->m_parent = m_nil;
		m_root = m_nil;
	}

	rb_tree(const key_compare& comp, const allocator_type& alloc)
	: m_alloc(alloc), m_comp(comp), m_size(0){
		m_nil = alloc_node(BLACK, value_type());
		m_nil->m_left = m_nil;
		m_nil->m_right = m_nil;
		m_nil->m_parent = m_nil;
		m_root = m_nil;
	}

	template <typename InputIterator>
	rb_tree(InputIterator first, InputIterator last, const key_compare& comp , const allocator_type& alloc)
	: m_alloc(alloc), m_comp(comp), m_size(0){
		m_nil = alloc_node(BLACK, value_type());
		m_nil->m_left = m_nil;
		m_nil->m_right = m_nil;
		m_nil->m_parent = m_nil;
		m_root = m_nil;
		insert_node(first, last);
	}

	rb_tree(const rb_tree& tree) : m_size(0){
		if (this == &tree)
			return ;
		clear();
		dealloc_nil();
		*this = rb_tree(tree.begin(), tree.end(), tree.get_comp(), tree.get_allocator());
	}

	void swap(rb_tree& tree){
		std::swap(m_root, tree.m_root);
		std::swap(m_nil, tree.m_nil);
		std::swap(m_size, tree.m_size);
	}

	node_ptr make_node(const value_type& data){
		node_ptr new_node = alloc_node(RED, data);
		new_node->m_left = m_nil;
		new_node->m_right = m_nil;
		new_node->m_parent = m_nil;
		return (new_node);
	}

	node_ptr minimum(node_ptr node, node_ptr m_nil) const{
		node_ptr x = node;
		while (x->m_left != m_nil)
			x = x->m_left;
		return (x);
	}

	node_ptr maximum(node_ptr node, node_ptr m_nil) const{
		node_ptr x = node;
		while (x->m_right != m_nil)
			x = x->m_right;
		return (x);
	}

	node_ptr successor(node_ptr node) const{
		node_ptr x = node;
		node_ptr y = node->m_parent;
		if (node->m_right != m_nil)
			return (minimum(x->m_right, m_nil));
		while (y != m_nil && x == y->m_right){
			x = y;
			y = y->m_parent;
		}
		return (y);
	}

	node_ptr predecessor(node_ptr node) const{
		node_ptr x = node;
		node_ptr y = node->m_parent;
		if (node->m_left != m_nil)
			return (maximum(x->m_left, m_nil));
		while (y != m_nil && x == y->m_left){
			x = y;
			y = y->m_parent;
		}
		return (y);
	}

	bool is_empty() const{
		if (m_root == m_nil)
			return (true);
		return (false);
	}

	bool is_exist(const key_type& k) const{
		if (find_node(k) != m_nil)
			return (true);
		return (false);
	}

	template<class InputIterator>
	bool is_hint(InputIterator hint, const key_type& k){
		node_ptr hint_node = hint.base();
		node_ptr hint_next_node = (hint++).base();

		if (hint_node == m_nil){
			node_ptr max = maximum(m_root, m_nil);
			if (m_comp(KeyOfValue()(max->m_data), k))
				return (true);
			return (false);
		}
		else{
			if (m_comp(KeyOfValue()(hint_next_node->m_data), k)){
				if (m_comp(k, KeyOfValue()(hint_next_node->m_data)))
					return (true);
			}
			return (false);
		}
	}

	node_ptr get_root() const { return (m_root); }
	node_ptr get_nil() const { return (m_nil); }
	size_t get_size() const { return (m_size); }
	allocator_type get_allocator() const { return (m_alloc); }
	key_compare get_comp() const { return (m_comp); }


	size_t max_size() const{
		return std::min(node_allocator_type().max_size(),
		static_cast<size_t>(std::numeric_limits<std::size_t>::max()));
	}

	void transplant(node_ptr t, node_ptr c){
		if( t->m_parent == m_nil){
			m_root = c;
		}
		else if( t == t->m_parent->m_left){
			t->m_parent->m_left = c;
		}
		else{
			t->m_parent->m_right = c;
		}
		c->m_parent = t->m_parent;
	}

	template <class InputIterator>
	void insert_node(InputIterator first, InputIterator last){
		while (first != last){
			node_ptr node = make_node(*first);
			if (!is_exist(KeyOfValue()(node->m_data)))
				insert_node(node);
			first++;
		}
	}

	template <class InputIterator>
	iterator insert_node(InputIterator hint, const value_type& data){
		node_ptr node = make_node(data);
		if (is_empty())
			insert_node_empty(node);
		else
			insert_node_with_hint(hint, node);
		m_size++;
		return (iterator(node, m_root, m_nil));
	}

	iterator insert_node(node_ptr node){
		if (is_empty())
			insert_node_empty(node);
		else
			insert_node_not_empty(node);
		m_size++;
		return (iterator(node, m_root, m_nil));
	}

	iterator insert_node(const value_type& data){
		node_ptr node = make_node(data);
		return (insert_node(node));
	}

	void delete_node(node_ptr node){
		node_ptr y = m_nil;
		node_ptr x = m_nil;
		rb_tree_color color = node->m_color;
		if (!is_exist(KeyOfValue()(node->m_data)))
			return ;
		if (node->m_left == m_nil){
			x = node->m_right;
			transplant(node, node->m_right);
		}
		else if (node->m_right == m_nil){
			x = node->m_left;
			transplant(node, node->m_left);
		}
		else{
			y = predecessor(node);

			color = y->m_color;
			x = y->m_left;

			transplant(y, y->m_left);
			y->m_left = node->m_left;
			y->m_left->m_parent = y;

			transplant(node, y);
			y->m_right = node->m_right;
			y->m_right->m_parent = y;
			y->m_color = node->m_color;
		}

		if (color == BLACK)
			delete_fixup(x);
		if (x == m_nil)
			x->m_parent = m_nil;
		m_alloc.deallocate(node, 1);
		m_alloc.destroy(node);
		m_size--;
	}

	void dealloc_nil(){
		m_alloc.deallocate(m_nil, 1);
		m_alloc.destroy(m_nil);
	}

	void clear(){
		inoder_dealloc_tree(m_root);
	}

	void inoder_dealloc_tree(node_ptr node){
		if (node != m_nil)
		{
			inoder_dealloc_tree(node->m_left);
			inoder_dealloc_tree(node->m_right);
			m_alloc.destroy(node);
			m_alloc.deallocate(node, 1);
		}
	}

	node_ptr find_node(const key_type & k) const{
		node_ptr x = m_root;
		while (x != m_nil)
		{
			if (k == KeyOfValue()(x->m_data))
				break ;
			if (m_comp(k, KeyOfValue()(x->m_data)))
				x = x->m_left;
			else
				x = x->m_right;
		}
		return (x);
	}

	iterator begin(){
		return (iterator(minimum(m_root, m_nil), m_root, m_nil));
	}

	const_iterator begin() const{
		return (const_iterator(minimum(m_root, m_nil), m_root, m_nil));
	}

	iterator end(){
		return (iterator(m_nil, m_root, m_nil));
	}

	const_iterator end() const{
		return (const_iterator(m_nil, m_root, m_nil));
	}

	reverse_iterator rbegin(){
		return (reverse_iterator(end()));
	}

	const_reverse_iterator rbegin() const{
		return (const_reverse_iterator(end()));
	}

	reverse_iterator rend(){
		return (reverse_iterator(begin()));
	}

	const_reverse_iterator rend() const{
		return (const_reverse_iterator(begin()));
	}

	iterator lower_bound(const key_type& k){
		if (is_exist(k))
			return (iterator(find_node(k), m_root, m_nil));

		node_ptr x = m_root;
		node_ptr y = m_nil;
		while (x != m_nil)
		{
			y = x;
			if (m_comp(k, KeyOfValue()(x->m_data)))
				x = x->m_left;
			else
				x = x->m_right;
		}
		if (m_comp(KeyOfValue()(y->m_data), k))
			y = successor(y);
		return (iterator(y, m_root, m_nil));
	}

	const_iterator lower_bound(const key_type& k) const{
		if (is_exist(k))
			return (const_iterator(find_node(k), m_root, m_nil));

		node_ptr x = m_root;
		node_ptr y = m_nil;
		while (x != m_nil)
		{
			y = x;
			if (m_comp(k, KeyOfValue()(x->m_data)))
				x = x->m_left;
			else
				x = x->m_right;
		}
		if (m_comp(KeyOfValue()(y->m_data), k))
			y = successor(y);
		return (const_iterator(y, m_root, m_nil));
	}

	iterator upper_bound (const key_type& k){
		node_ptr x = m_root;
		node_ptr y = m_nil;
		while (x != m_nil)
		{
			y = x;
			if (m_comp(k, KeyOfValue()(x->m_data)))
				x = x->m_left;
			else
				x = x->m_right;
		}
		if (is_exist(k) || m_comp(KeyOfValue()(y->m_data), k))
			y = successor(y);
		return (iterator(y, m_root, m_nil));
	}

	const_iterator upper_bound (const key_type& k) const{
		node_ptr x = m_root;
		node_ptr y = m_nil;
		while (x != m_nil)
		{
			y = x;
			if (m_comp(k, KeyOfValue()(x->m_data)))
				x = x->m_left;
			else
				x = x->m_right;
		}
		if (is_exist(k) || m_comp(KeyOfValue()(y->m_data), k))
			y = successor(y);
		return (const_iterator(y, m_root, m_nil));
	}

protected:
	node_ptr alloc_node(rb_tree_color color, value_type data){
		node_type node(color, NULL, NULL, NULL, data);
		node_ptr new_node = m_alloc.allocate(1);
		m_alloc.construct(new_node, node);
		return (new_node);
	}

	void left_rotate(node_ptr node){
		node_ptr y = node->m_right;
		node->m_right = y->m_left;
		if (y->m_left != m_nil)
		y->m_left->m_parent = node;
		y->m_parent = node->m_parent;
		if (node->m_parent == m_nil)
			m_root = y;
		else if (node == node->m_parent->m_left)
			node->m_parent->m_left = y;
		else
			node->m_parent->m_right = y;
		y->m_left = node;
		node->m_parent = y;
	}

	void right_rotate(node_ptr node){
		node_ptr y = node->m_left;
		node->m_left = y->m_right;
		if (y->m_right != m_nil)
			y->m_right->m_parent = node;
		y->m_parent = node->m_parent;
		if (node->m_parent == m_nil)
			m_root = y;
		else if (node == node->m_parent->m_right)
			node->m_parent->m_right = y;
		else
			node->m_parent->m_left = y;
		y->m_right = node;
		node->m_parent = y;
	}

	void insert_fixup_left(node_ptr* node){
		node_ptr uncle = m_nil;

		uncle = (*node)->m_parent->m_parent->m_right;
		// case 1: Color of Uncle is RED
		if (uncle->m_color == RED)
		{
			(*node)->m_parent->m_color = BLACK;
			uncle->m_color = BLACK;
			(*node)->m_parent->m_parent->m_color = RED;
			(*node) = (*node)->m_parent->m_parent;
		}
		// case 2: Right child ir RED
		else if ((*node) == (*node)->m_parent->m_right)
		{
			(*node) = (*node)->m_parent;
			left_rotate((*node));
		}
		// case 3: if node is left child
		else
		{
			(*node)->m_parent->m_color = BLACK;
			(*node)->m_parent->m_parent->m_color = RED;
			right_rotate((*node)->m_parent->m_parent);
		}
	}

	void insert_fixup_right(node_ptr* node){
		node_ptr uncle = m_nil;

		uncle = (*node)->m_parent->m_parent->m_left;
		if (uncle->m_color == RED)
		{
			(*node)->m_parent->m_color = BLACK;
			uncle->m_color = BLACK;
			(*node)->m_parent->m_parent->m_color = RED;
			(*node) = (*node)->m_parent->m_parent;
		}
		else if ((*node) == (*node)->m_parent->m_left)
		{
			(*node) = (*node)->m_parent;
			right_rotate((*node));
		}
		else
		{
			(*node)->m_parent->m_color = BLACK;
			(*node)->m_parent->m_parent->m_color = RED;
			left_rotate((*node)->m_parent->m_parent);
		}
	}

	void insert_fixup(node_ptr node){
		while (node->m_parent->m_color == RED)
		{
			if (node->m_parent == node->m_parent->m_parent->m_left)
				insert_fixup_left(&node);
			else
				insert_fixup_right(&node);
		}
		m_root->m_color = BLACK;
	}

	void insert_node_empty(node_ptr node){
		m_root = node;
		m_root->m_color = BLACK;
		m_root->m_parent = m_nil;
	}

	template<class InputIterator>
	void insert_node_with_hint(InputIterator hint, node_ptr node){
		node_ptr y = hint.base();

		if (y == m_nil)
			y = maximum(m_root, m_nil);

		// 트리에 노드 연결
		node->m_parent = y;
		if (m_comp(KeyOfValue()(node->m_data), KeyOfValue()(y->m_data)))
			y->m_left = node;
		else
			y->m_right = node;

		// fixup 실행
		insert_fixup(node);
	}

	void insert_node_not_empty(node_ptr node){
		node_ptr y = m_nil;
		node_ptr x = m_root;
		while (x != m_nil)
		{
			y = x;
			if (m_comp(KeyOfValue()(node->m_data), KeyOfValue()(x->m_data)))
				x = x->m_left;
			else
				x = x->m_right;
		}
		// LINKING
		node->m_parent = y;
		if (m_comp(KeyOfValue()(node->m_data), KeyOfValue()(y->m_data)))
			y->m_left = node;
		else
			y->m_right = node;
		insert_fixup(node);
	}

	void delete_fixup_left(node_ptr* node){
		node_ptr brother = (*node)->m_parent->m_right;
		//case 1: Brother is RED
		if (brother->m_color == RED){
			brother->m_color = BLACK;
			(*node)->m_parent->m_color = RED;
			left_rotate((*node)->m_parent);
			brother = (*node)->m_parent->m_right;
		}
		//case 2: Bro's two child is BLACK
		if (brother->m_left->m_color == BLACK && brother->m_right->m_color == BLACK){
			brother->m_color = RED;
			(*node) = (*node)->m_parent;
		}
		// Case 3 : Bro's left child is RED
		else if (brother->m_right->m_color == BLACK){
			brother->m_left->m_color = BLACK;
			brother->m_color = RED;
			right_rotate(brother);
			brother = (*node)->m_parent->m_right;
		}
		// Case 4 : Bro's right child is RED
		else{
			brother->m_color = (*node)->m_parent->m_color;
			(*node)->m_parent->m_color = BLACK;
			brother->m_right->m_color = BLACK;
			left_rotate((*node)->m_parent);
			(*node) = m_root;
		}
	}

	void delete_fixup_right(node_ptr* node){
		node_ptr brother = (*node)->m_parent->m_left;
		if (brother->m_color == RED){
			brother->m_color = BLACK;
			(*node)->m_parent->m_color = RED;
			right_rotate((*node)->m_parent);
			brother = (*node)->m_parent->m_left;
		}
		if (brother->m_left->m_color == BLACK && brother->m_right->m_color == BLACK){
			brother->m_color = RED;
			(*node) = (*node)->m_parent;
		}
		else if (brother->m_left->m_color == BLACK){
			brother->m_right->m_color = BLACK;
			brother->m_color = RED;
			left_rotate(brother);
			brother = (*node)->m_parent->m_left;
		}
		if (brother->m_left->m_color == RED){
			brother->m_color = (*node)->m_parent->m_color;
			(*node)->m_parent->m_color = BLACK;
			brother->m_left->m_color = BLACK;
			right_rotate((*node)->m_parent);
			(*node) = m_root;
		}
	}

	void delete_fixup(node_ptr node){
		while (node != m_root && node->m_color == BLACK){
			if (node == node->m_parent->m_left)
				delete_fixup_left(&node);
			else
				delete_fixup_right(&node);
		}
		node->m_color = BLACK;
	}

	void delete_right(){
		node_ptr tail = maximum(m_root, m_nil);

		tail->m_parent->m_right = tail->m_left;
		m_alloc.destroy(tail);
		m_alloc.deallocate(tail, 1);
		m_size--;
	}
	void delete_left(){
		node_ptr tail = minimum(m_root, m_nil);

		tail->m_parent->m_left = tail->m_right;
		m_alloc.destroy(tail);
		m_alloc.deallocate(tail, 1);
		m_size--;
	}
};
};


#endif
