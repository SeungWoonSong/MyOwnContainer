#ifndef PAIR_HPP
#define PAIR_HPP

namespace ft{
	template<typename T1, typename T2>
	struct pair
	{
			typedef T1			first_type;
			typedef T2			second_type;
			first_type			first;
			second_type			second;

			// Constructor
			pair() : first(), second() {}
			template<class U, class V>
			pair (const pair<U,V>& obj) : first(obj.first), second(obj.second) {}
			pair (const T1& a, const T2& b) : first(a), second(b) {}

			pair& operator=(const pair& obj){
				if(this != &obj){
					this->first = obj.first;
					this->second = obj.second;
				}
				return(*this);
			}
	};

	template< class T1, class T2 >
	pair<T1, T2> make_pair(T1 first, T2 second){
		return(pair<T1, T2>(first, second));
	}

	template< class T1, class T2, class U1, class U2 >
	bool operator==( const pair<T1, T2>& left, const pair<U1, U2>& right ){
		if(left.first == right.first && left.second == right.second)
			return true;
		return false;
	}

	template< class T1, class T2, class U1, class U2 >
	bool operator!=( const pair<T1, T2>& left, const pair<U1, U2>& right ){
		return (!(left == right));
	}

	template< class T1, class T2, class U1, class U2 >
	bool operator<( const pair<T1, T2>& left, const pair<U1, U2>& right ){
		if(left.first < right.first)
			return(true);
		else if(right.first < left.first)
			return(false);
		else if(left.second < right.second)
			return(true);
		else
			return(false);
	}

	template< class T1, class T2, class U1, class U2 >
	bool operator<=( const pair<T1, T2>& left, const pair<U1, U2>& right ){
		return(!(right < left));
	}

	template< class T1, class T2, class U1, class U2 >
	bool operator>( const pair<T1, T2>& left, const pair<U1, U2>& right ){
		return(right < left);
	}

	template< class T1, class T2, class U1, class U2 >
	bool operator>=( const pair<T1, T2>& left, const pair<U1, U2>& right ){
		return(!(left < right));
	}
}
#endif
