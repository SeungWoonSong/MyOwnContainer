#ifndef VECTOR_ITERATOR_SUSONG_HPP
#define VECTOR_ITERATOR_SUSONG_HPP

#include "iterator.hpp"

namespace ft
{
template <typename T>
class vector_iterator {
	public:
		typedef T value_type;
		typedef T& reference;
		typedef const T& const_reference;
		typedef T* pointer;
		typedef const T* const_pointer;
		typedef std::ptrdiff_t difference_type;
		typedef typename ft::iterator_traits<pointer>::iterator_category iterator_category;
		typedef pointer iterator_type;
		typedef vector_iterator<const T> const_iterator;

	private:
		pointer ptr;

	public:
		// Constructor
		vector_iterator(pointer p) : ptr(p) {}
		vector_iterator(const vector_iterator &p) : ptr(p.ptr) {}
		vector_iterator() : ptr(nullptr){}

		pointer base() const { return ptr;}
		operator const_iterator() const { return const_iterator(ptr); }

		// Dereference operator
		reference operator*() const { return *ptr; }

		// Arrow operator
		pointer operator->() const { return ptr; }

		// Prefix increment operator
		vector_iterator& operator++() { ++ptr; return *this; }

		// Postfix increment operator
		vector_iterator operator++(int) { vector_iterator tmp(*this); ++ptr; return tmp; }

		// Prefix decrement operator
		vector_iterator& operator--() { --ptr; return *this; }

		// Postfix decrement operator
		vector_iterator operator--(int) { vector_iterator tmp(*this); --ptr; return tmp; }

		// Random access operator
		reference operator[](difference_type n) const { return ptr[n]; }

		// Addition operator
		vector_iterator operator+(difference_type n) const { return vector_iterator(ptr + n); }

		//Addition-assignment operator
		vector_iterator operator+=(difference_type n) {ptr += n; return *this;}

		// Subtraction operator
		vector_iterator operator-(difference_type n) const { return vector_iterator(ptr - n); }

		//Subtraction-assignment operator
		vector_iterator operator-=(difference_type n) {ptr -= n;return *this;}

		// Difference operator
		difference_type operator-(const vector_iterator& other) const { return ptr - other.ptr; }

		// Less than operator
		bool operator<(const vector_iterator& other) const { return ptr < other.ptr; }

		// Less than or equal to operator
		bool operator<=(const vector_iterator& other) const { return ptr <= other.ptr; }

		// Greater than operator
		bool operator>(const vector_iterator& other) const { return ptr > other.ptr; }

		// Greater than or equal to operator
		bool operator>=(const vector_iterator& other) const { return ptr >= other.ptr; }

		// Equality operator
		bool operator==(const vector_iterator& other) const { return ptr == other.ptr; }

		// Inequality operator
		bool operator!=(const vector_iterator& other) const { return ptr != other.ptr; }
		// bool operator!=(const vector_iterator<const T>& other) const { return ptr != other.ptr; }


};

	template <typename T>
	bool operator==(const ft::vector_iterator<T> left,
				const ft::vector_iterator<T> right)
	{
		return (left.base() == right.base());
	}
	template <typename T1, typename T2>
	bool operator==(const ft::vector_iterator<T1> left,
				const ft::vector_iterator<T2> right)
	{
		return (left.base() == right.base());
	}

	template <typename T>
	bool operator!=(const ft::vector_iterator<T> left,
				const ft::vector_iterator<T> right)
	{
		return (left.ptr != right.ptr);
	}

	template <typename T1, typename T2>
	bool operator!=(const ft::vector_iterator<T1> left,
				const ft::vector_iterator<T2> right)
	{
		return (left.base() != right.base());
	}

	template <typename T>
	bool operator<(const ft::vector_iterator<T> left,
				const ft::vector_iterator<T> right)
	{
		return (left() < right());
	}

	template <typename T1, typename T2>
	bool operator<(const ft::vector_iterator<T1> left,
				const ft::vector_iterator<T2> right)
	{
		return (left.base() < right.base());
	}


	template <typename T>
	bool operator>(const ft::vector_iterator<T> left,
				const ft::vector_iterator<T> right)
	{
		return (left() > right());
	}

	template <typename T1, typename T2>
	bool operator>(const ft::vector_iterator<T1> left,
				const ft::vector_iterator<T2> right)
	{
		return (left.base() > right.base());
	}

	template <typename T>
	bool operator<=(const ft::vector_iterator<T> left,
				const ft::vector_iterator<T> right)
	{
		return (left() <= right());
	}

	template <typename T1, typename T2>
	bool operator<=(const ft::vector_iterator<T1> left,
				const ft::vector_iterator<T2> right)
	{
		return (left.base() <= right.base());
	}

	template <typename T>
	bool operator>=(const ft::vector_iterator<T> left,
				const ft::vector_iterator<T> right)
	{
		return (left() >= right());
	}

	template <typename T1, typename T2>
	bool operator>=(const ft::vector_iterator<T1> left,
				const ft::vector_iterator<T2> right)
	{
		return (left.base() >= right.base());
	}

	template <typename T>
	typename ft::vector_iterator<T>::difference_type
	operator+(const ft::vector_iterator<T> left,
				const ft::vector_iterator<T> right)
	{
		return (left.base() + right.base());
	}
	template <typename T1, typename T2>
	typename ft::vector_iterator<T1>::difference_type
	operator+(const ft::vector_iterator<T1> left,
				const ft::vector_iterator<T2> right)
	{
		return (left.base() + right.base());
	}

	template <typename T>
	typename ft::vector_iterator<T>::difference_type
	operator-(const ft::vector_iterator<T> left,
				const ft::vector_iterator<T> right)
	{
		return (left.base() - right.base());
	}

	template <typename T1, typename T2>
	typename ft::vector_iterator<T1>::difference_type
	operator-(const ft::vector_iterator<T1> left,
				const ft::vector_iterator<T2> right)
	{
		return (left.base() - right.base());
	}
    template<typename T>
    ft::vector_iterator<T> operator+(
        typename ft::vector_iterator<T>::difference_type n,
        typename ft::vector_iterator<T>& obj)
        {
            return (&(*obj) + n);
		}


template <class Iterator>
class reverse_iterator
{
	public:

		typedef Iterator													iterator_type;
		typedef typename ft::iterator_traits<Iterator>::iterator_category	iterator_category;
		typedef typename ft::iterator_traits<Iterator>::value_type			value_type;
		typedef typename ft::iterator_traits<Iterator>::difference_type		difference_type;
		typedef typename ft::iterator_traits<Iterator>::pointer				pointer;
		typedef typename ft::iterator_traits<Iterator>::reference			reference;

		reverse_iterator()
		: ptr()
		{}

		explicit reverse_iterator (iterator_type it)
		: ptr(it)
		{}

		template <class Iter>
		reverse_iterator (const reverse_iterator<Iter>& rev_it)
		: ptr(rev_it.base())
		{}

		virtual ~reverse_iterator() {}

		iterator_type base() const
		{ return (ptr); }

		reference operator*() const
		{
			iterator_type tmp = ptr;
			return (*(--tmp));
		}

		reverse_iterator operator+ (difference_type n) const { return (reverse_iterator(ptr - n)); }

		reverse_iterator& operator++()
		{
			--ptr;
			return (*this);
		}

		reverse_iterator operator++(int)
		{
			reverse_iterator tmp = *this;
			++(*this);
			return (tmp);
		}

		reverse_iterator& operator+= (difference_type n)
		{
			ptr -= n;
			return (*this);
		}

		reverse_iterator operator- (difference_type n) const { return (reverse_iterator(ptr + n)); }

		reverse_iterator& operator--()
		{
			++ptr;
			return (*this);
		}

		reverse_iterator operator--(int)
		{
			reverse_iterator tmp = *this;
			--(*this);
			return (tmp);
		}

		reverse_iterator& operator-= (difference_type n)
		{
			ptr += n;
			return (*this);
		}

		pointer operator->() const { return &(operator*()); }

		reference operator[] (difference_type n) const { return (this->base()[-n - 1]); }

	private:
		iterator_type     ptr;
};

template <class Iterator>
bool operator== (const reverse_iterator<Iterator>& left, const reverse_iterator<Iterator>& right)
{ return (left.base() == right.base()); }

template <class Iterator1, class Iterator2>
bool operator== (const reverse_iterator<Iterator1>& left, const reverse_iterator<Iterator2>& right)
{ return (left.base() == right.base()); }

template <class Iterator>
bool operator!= (const reverse_iterator<Iterator>& left, const reverse_iterator<Iterator>& right)
{ return (left.base() != right.base()); }

template <class Iterator1, class Iterator2>
bool operator!= (const reverse_iterator<Iterator1>& left,
const reverse_iterator<Iterator2>& right) { return (left.base() != right.base()); }

template <class Iterator>
bool operator<  (const reverse_iterator<Iterator>& left,
const reverse_iterator<Iterator>& right) { return (left.base() > right.base()); }

template <class Iterator1, class Iterator2>
bool operator< (const reverse_iterator<Iterator1>& left,
const reverse_iterator<Iterator2>& right) { return (left.base() > right.base()); }

template <class Iterator>
bool operator<= (const reverse_iterator<Iterator>& left,
const reverse_iterator<Iterator>& right) { return (left.base() >= right.base()); }

template <class Iterator1, class Iterator2>
bool operator<= (const reverse_iterator<Iterator1>& left,
const reverse_iterator<Iterator2>& right) { return (left.base() >= right.base()); }


template <class Iterator>
bool operator> (const reverse_iterator<Iterator>& left,
const reverse_iterator<Iterator>& right) { return (left.base() < right.base()); }

template <class Iterator1, class Iterator2>
bool operator> (const reverse_iterator<Iterator1>& left,
const reverse_iterator<Iterator2>& right) { return (left.base() < right.base()); }

template <class Iterator>
bool operator>= (const reverse_iterator<Iterator>& left,
const reverse_iterator<Iterator>& right) { return (left.base() <= right.base()); }

template <class Iterator1, class Iterator2>
bool operator>= (const reverse_iterator<Iterator1>& left,
const reverse_iterator<Iterator2>& right) { return (left.base() <= right.base()); }

template <class Iterator>
	reverse_iterator<Iterator> operator+ (
		typename reverse_iterator<Iterator>::difference_type n,
		const reverse_iterator<Iterator>& rev_it) { return (rev_it + n); }

template <class Iterator>
	typename reverse_iterator<Iterator>::difference_type operator- (
		const reverse_iterator<Iterator>& left,
		const reverse_iterator<Iterator>& right) { return (left.base() - right.base()); }

template <class Iterator1, class Iterator2>
	typename reverse_iterator<Iterator1>::difference_type operator- (const reverse_iterator<Iterator1>& left,
					const reverse_iterator<Iterator2>& right) { return (right.base() - left.base()); }


} // namespace ft


#endif
