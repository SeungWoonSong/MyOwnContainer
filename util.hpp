#ifndef UTIL_HPP
#define UTIL_HPP

#include <functional>

namespace ft{
	//enable if
	template<bool B, class T = void>
	struct enable_if {};

	template<class T>
	struct enable_if<true, T> { typedef T type; };

	//is_integral
	template< typename T >
	struct is_integral{
		static const bool value = false;
	};

	template <>
	struct is_integral<int> {
		static const bool value = true;
	};

	template <>
	struct is_integral<short> {
		static const bool value = true;
	};

	template <>
	struct is_integral<long> {
		static const bool value = true;
	};

	template <>
	struct is_integral<char> {
		static const bool value = true;
	};

	template <>
	struct is_integral<unsigned long long> {
		static const bool value = true;
	};

	template <>
	struct is_integral<const int> {
		static const bool value = true;
	};

	template <>
	struct is_integral<const short> {
		static const bool value = true;
	};

	template <>
	struct is_integral<const long> {
		static const bool value = true;
	};

	template <>
	struct is_integral<const char> {
		static const bool value = true;
	};


	template <>
	struct is_integral<const unsigned long long> {
		static const bool value = true;
	};

	template <typename T>
	bool operator==(const ft::is_integral<T>&, const std::is_integral<T>&) {
		return true;
	}


	// equal
	template< class InputIt1, class InputIt2 >
	bool equal( InputIt1 first1, InputIt1 last1, InputIt2 first2 ){
		for (; first1 != last1; ++first1, ++first2)
			if (!(*first1 == *first2))
				return false;
		return true;
	}

	template< class InputIt1, class InputIt2, class BinaryPredicate >
	bool equal( InputIt1 first1, InputIt1 last1, InputIt2 first2, BinaryPredicate p){
		for (; first1 != last1; ++first1, ++first2)
			if (!p(*first1, *first2))
				return false;

		return true;
	}

	//LEXICOGRAPHICAL_COMPARE_HPP
	template< typename InputIt1, typename InputIt2 >
	bool lexicographical_compare( InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2 ){
		while (first1 != last1 && first2 != last2) {
			if (*first1 < *first2) {
				return true;
			} else if (*first2 < *first1) {
				return false;
			}
			++first1;
			++first2;
		}
		return (first1 == last1 && first2 != last2);
	}

	template< class InputIt1, class InputIt2, class Compare >
	bool lexicographical_compare( InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2, Compare comp ){
		for (; (first1 != last1) && (first2 != last2); ++first1, (void) ++first2)
		{
			if (comp(*first1, *first2))
				return true;
			if (comp(*first2, *first1))
				return false;
		}

		return (first1 == last1) && (first2 != last2);
	}

	template <class T> struct less : std::binary_function <T,T,bool> {
		bool operator() (const T& x, const T& y) const {return x < y;}
	};

	template <class Pair>
	struct key_pair
	{
		typename Pair::first_type &operator()(Pair & pair) const { return (pair.first); }
		typename Pair::first_type &operator()(const Pair & pair) const { return (pair.first); }
	};

	template <class Value>
	struct key_value
	{
		Value &operator()(Value & val) const { return (val); }
		Value &operator()(const Value & val) const { return (val); }
	};


    template <class Pair>
    struct key_with_pair
    {
        typename Pair::first_type &operator()(Pair & pair) const { return (pair.first); }
        typename Pair::first_type &operator()(const Pair & pair) const { return (pair.first); }
    };

    template <class Value>
    struct key_with_value
    {
        Value &operator()(Value & val) const { return (val); }
        Value &operator()(const Value & val) const { return (val); }
    };
}


#endif
