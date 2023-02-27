#ifndef VECTOR_SUSONG_HPP
#define VECTOR_SUSONG_HPP

#include <memory>
#include <iosfwd>
#include <exception>
#include "vector_iterator.hpp"
#include "util.hpp"
#include <algorithm>

namespace ft{

template <class T, class Alloc = std::allocator<T> >
class vector
{
	public:
		typedef T                                        value_type;
		typedef Alloc                                    allocator_type;
		typedef typename allocator_type::reference       reference;
		typedef typename allocator_type::const_reference const_reference;
		typedef typename allocator_type::pointer         pointer;
		typedef typename allocator_type::const_pointer   const_pointer;
		typedef ft::vector_iterator<value_type>          iterator;
		typedef ft::vector_iterator<const value_type>    const_iterator;
		typedef ft::reverse_iterator<iterator>          reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>    const_reverse_iterator;
		typedef typename allocator_type::difference_type difference_type;
		typedef typename allocator_type::size_type       size_type;

	private:
		pointer m_data;
		size_type m_size;
		size_type m_capacity;
		allocator_type m_allocator;

	public:
		explicit vector (const allocator_type& alloc = allocator_type())
		: m_data(nullptr), m_size(0), m_capacity(0), m_allocator(alloc){
		}

		explicit vector (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()){
			// std::cout << "1 consturctor called" << std::endl; // debug
			if(n < 0)
				throw std::out_of_range("Not Valid Size, Size sholud be plus");
			m_allocator = alloc;
			m_data = m_allocator.allocate(n);
			m_capacity = n;
			m_size = n;
			pointer _prev = m_data;
			while(n--){
				m_allocator.construct(_prev++, val);
			}
		}

		template <class InputIterator>
		vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type(), typename ft::enable_if<!ft::is_integral<InputIterator>::value, void>::type* = 0){
			difference_type n = std::distance(first, last);
			m_allocator = alloc;
			m_data = m_allocator.allocate(n);
			m_capacity = n;
			m_size = n;
			pointer _prev = m_data;
			while(n != 0){
				m_allocator.construct(_prev++, *first++);
				--n;
			}
		}

		vector (const vector& x) : m_data(nullptr), m_size(0), m_capacity(0), m_allocator(x.m_allocator){
				insert(begin(), x.begin(), x.end());
		}

		~vector(){
			for (size_type i = 0; i < m_size; i++) {
				m_allocator.destroy(m_data + i);
				}
			m_allocator.deallocate(m_data, m_capacity);
		};

		vector& operator= (const vector& x){
			if (this == &x)
				return *this;
			clear();
			m_allocator.deallocate(m_data, m_capacity);
			m_allocator = x.m_allocator;
			m_capacity = x.m_capacity;
			m_size = x.m_size;

			m_data = m_allocator.allocate(m_capacity);
			for(size_type i = 0; i < m_size; ++i){
				m_allocator.construct(m_data + i, x.m_data[i]);
			}
			return *this;
		}

		iterator begin(){
			return (iterator(m_data));
		}
		const_iterator begin() const{
			return (const_iterator(m_data));
		}

		iterator end(){
			return(iterator(m_data + m_size));
		}
		const_iterator end() const{
			return(const_iterator(m_data + m_size));
		}

		// do it later
		reverse_iterator rbegin(){
			return(reverse_iterator(end()));
		}
		const_reverse_iterator rbegin() const{
			return(const_reverse_iterator(end()));
		}

		reverse_iterator rend(){
			return(reverse_iterator(begin()));
		}
		const_reverse_iterator rend() const{
			return(const_reverse_iterator(begin()));
		}
		// someday..

		size_type size() const{
			return (m_size);
		}

		size_type max_size() const{
			return(static_cast<size_type>(m_allocator.max_size()));
		}

		void resize (size_type n, value_type val = value_type())
		{
			if (n < m_size){
				while(size() > n)
					pop_back();
			}
			else if (n > m_size)
			{
				if(m_capacity < n)
					reserve(n);
				size_type num_elements_to_add = n - size();
				insert(end(), num_elements_to_add, val);
			}
			m_size = n;
		}

		size_type capacity() const{
			return (m_capacity);
		}

		bool empty() const{
			return (m_size == 0 ? true : false);
		}

		void reserve (size_type n){
			if (n > max_size()){
				throw (std::length_error("reserve() error : cannot reserve more than max"));
			}
			else if(n > m_capacity){
				pointer prev_data = m_data;
				size_type prev_size = m_size;
				size_type prev_capacity = m_capacity;

				m_data = m_allocator.allocate(n);
				m_size = 0;
				m_capacity = n;
				while(prev_size != 0){
					m_allocator.construct(m_data + m_size, *(prev_data + m_size));
					m_allocator.destroy(prev_data + m_size);
					++m_size;
					--prev_size;
				}
				if(prev_capacity != 0)
					m_allocator.deallocate(prev_data, prev_capacity);
			}
			return ;
		}

		reference operator[] (size_type n){
			return (*(m_data + n));
		}
		const_reference operator[] (size_type n) const{
			return (*(m_data + n));
		}

		reference at (size_type n){
			if(m_size - 1< n)
				throw std::out_of_range("Index out of range.");
			return (*(m_data + n));
		}
		const_reference at (size_type n) const{
			if(m_size - 1 < n)
				throw std::out_of_range("Index out of range.");
			return (*(m_data + n));
		}

		reference front(){
			if(m_size == 0)
				throw std::out_of_range("ft::vector::front() can not be called in empty vector");
			return (*(m_data));
		}
		const_reference front() const{
			if(m_size == 0)
				throw std::out_of_range("ft::vector::front() can not be called in empty vector");
			return (*(m_data));
		}

		reference back(){
			if(m_size == 0)
				throw std::out_of_range("ft::vector::back() can not be called in empty vector");
			return (*(m_data + m_size - 1));
		}
		const_reference back() const{
			if(m_size == 0)
				throw std::out_of_range("ft::vector::back() can not be called in empty vector");
			return (*(m_data + m_size - 1));
		}

		template <class InputIterator>
		void assign (InputIterator first, InputIterator last, typename ft::enable_if<!ft::is_integral<InputIterator>::value, void>::type* = 0){
			size_type n = std::distance(first, last);
			// std::cout << "#### distance " << n << " ###"<< std::endl;
			clear();
			if(n > m_capacity){
				pointer new_data = m_allocator.allocate(n);
				pointer _prev = new_data;
				m_size = n;
				while(n--){
					m_allocator.construct(_prev++, *first++);
				}
				m_allocator.deallocate(m_data, m_capacity);
				m_capacity = m_size;
				m_data = new_data;
			}
			else{
				pointer _prev = m_data;
				m_size = n;
				while(n != 0){
					m_allocator.construct(_prev++, *first++);
					--n;
				}
			}
			return ;
		}

		void assign (size_type n, const value_type& val){
			clear();
			if(n == 0)
				return ;
			if(m_capacity > n){
				m_size = n;
				pointer _prev = m_data;
				while(n){
					m_allocator.construct(_prev++, val);
					--n;
				}
			}
			else{
				m_allocator.deallocate(m_data, m_capacity);
				m_data = m_allocator.allocate(n);
				pointer _start = m_data;
				m_size = n;
				m_capacity = n;
				while(n){
					m_allocator.construct(_start++, val);
					--n;
				}
			}
			return ;
		}

		void push_back (const value_type& val){
			if(m_size == m_capacity)
				reserve(m_capacity == 0 ? 1 : m_capacity * 2);
			m_allocator.construct(m_data + m_size, val);
			m_size += 1;
			return ;
		}

		void pop_back(){
			m_allocator.destroy(m_data + m_size - 1);
			m_size -= 1;
			return ;
		}

		iterator insert (iterator position, const value_type& val){
			size_type index = position - m_data;
			// std::cout << "index is " << index << std::endl;
			if(m_size == m_capacity){
				reserve(m_capacity == 0 ? 2 : m_capacity * 2);
			}
			if (position != end()) {
				pointer _prev = m_data + m_size;
				size_type move_need = m_size - index;
				while(move_need != 0){
					m_allocator.construct(_prev, *(_prev - 1));
					--move_need;
					--_prev;
				}
				*(m_data + index) = val;
				++m_size;
			}
			else{
				*(m_data + index) = val;
				++m_size;
			}
			return iterator(m_data + index);
		}

		void insert (iterator position, size_type n, const value_type& val){
			if(n == 0)
				return ;
			if (position < begin() || position > end()) {
				throw std::out_of_range("vector insert position out of range");
			}
			if(n > max_size())
				throw (std::length_error("vector insert over max_size"));
			size_type index = &(*position) - m_data;
			size_type move_need = m_size - index;
			if(m_capacity - m_size > n){
				pointer _prev = m_data + m_size + n - 1;
				while(move_need != 0){
					m_allocator.construct(_prev, *(_prev - n));
					--_prev;
					--move_need;
				}
				pointer _prev2 = m_data + index;
				while(n != 0){
					m_allocator.construct(_prev2, val);
					--n;
					++m_size;
					++_prev2;
				}
			}
			else{
				reserve(m_capacity == 0 ? n : m_capacity * 2);
				while(n >= m_capacity)
					reserve(m_capacity == 0 ? n : m_capacity * 2);
				pointer _prev = m_data + m_size + n - 1;
				while(move_need != 0){
					m_allocator.construct(_prev, *(_prev - n));
					--_prev;
					--move_need;
				}
				pointer _prev2 = m_data + index;
				while(n != 0){
					m_allocator.construct(_prev2, val);
					--n;
					++m_size;
					++_prev2;
				}
				// insert(position, val);
			}
		}

		template <class InputIterator>
		void insert (iterator position, InputIterator first, InputIterator last, typename ft::enable_if<!ft::is_integral<InputIterator>::value, void>::type* = 0){
			difference_type n = std::distance(first, last);
			if(n == 0)
				return ;
			size_type index = position - begin();
			size_type new_size = m_size + n;
			if(new_size > m_capacity)
				reserve(new_size);
			for(size_type i = m_size; i > index; --i){
				m_allocator.construct(m_data + i + n - 1, m_data[i - 1]);
				m_allocator.destroy(m_data + i - 1);
			}
			pointer _prev = m_data + index;
			while(n--){
				m_allocator.construct(_prev++, *first++);
			}
			m_size = new_size;
		}

		iterator erase (iterator position){
			if (position == end()) {
				return position;
			}
			const size_type index = position - begin();
			m_allocator.destroy(m_data + index);
			std::memmove(m_data + index, m_data + index + 1, (m_size - index - 1) * sizeof(value_type));
			--m_size;
			return begin() + index;
		}

		iterator erase (iterator first, iterator last){
			size_type n = last - first;
			for (iterator it = first; it != last; ++it) {
				m_allocator.destroy(&(*it));
			}
			std::memmove(&(*first), &(*last), (end() - last) * sizeof(value_type));
			m_size -= n;
			return first;
		}

		void swap(vector& other) {
			std::swap(m_data, other.m_data);
			std::swap(m_size, other.m_size);
			std::swap(m_capacity, other.m_capacity);
		}


		void clear(){
			if(m_size == 0)
				return ;
			pointer _prev = m_data;
			while(m_size != 0){
				m_allocator.destroy(_prev++);
				--m_size;
			}
			return ;
		}
};
		template <class T, class Alloc>
		bool operator== (const ft::vector<T, Alloc>& left, const ft::vector<T, Alloc>& right)
		{
			if (left.size() != right.size())
				return (false);
			typename ft::vector<T>::const_iterator first1 = left.begin();
			typename ft::vector<T>::const_iterator first2 = right.begin();
			while (first1 != left.end())
			{
				if (first2 == right.end() || *first1 != *first2)
					return (false);
				++first1;
				++first2;
			}
			return (true);
		}

		template <class T, class Alloc>
		bool operator!= (const vector<T, Alloc>& left, const vector<T, Alloc>& right)
		{
			return (!(left == right));
		}

		template <class T, class Alloc>
		bool operator<  (const vector<T, Alloc>& left, const vector<T, Alloc>& right)
		{
			return (ft::lexicographical_compare(left.begin(), left.end(), right.begin(), right.end()));
		}

		template <class T, class Alloc>
		bool operator<= (const vector<T, Alloc>& left, const vector<T, Alloc>& right)
		{
			return (!(right < left));
		}

		template <class T, class Alloc>
		bool operator> (const vector<T, Alloc>& left, const vector<T, Alloc>& right)
		{
			return (right < left);
		}

		template <class T, class Alloc>
		bool operator>= (const vector<T, Alloc>& left, const vector<T, Alloc>& right)
		{
			return (!(left < right));
		}
}
#endif
