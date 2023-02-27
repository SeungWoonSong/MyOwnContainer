/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susong <susong@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 11:59:08 by susong            #+#    #+#             */
/*   Updated: 2023/02/24 10:51:28 by susong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_HPP_SUSONG
#define STACK_HPP_SUSONG

#include <vector>
#include "vector.hpp"
namespace ft{

// Should have to change later
template <class T, class Container = ft::vector<T> >
class stack
{
public:
    typedef Container                                container_type;
    typedef typename container_type::value_type      value_type;
    typedef typename container_type::size_type       size_type;

protected:
    container_type c;

public:
    explicit stack (const container_type& ctnr = container_type()) : c(ctnr) {}
    ~stack(){};

    bool empty() const{
		return (c.empty());
	}
    size_type size() const{
		return (c.size());
	}
	value_type& top(){
		return (c.back());
	}
	const value_type& top() const{
		return (c.back());
	}
	void push (const value_type& val){
		c.push_back(val);
		return ;
	}
    void pop(){
		return(c.pop_back());
	}

	container_type get_container() const{
		return (c);
	}
};

template <class T, class Container>
bool operator== (const stack<T,Container>& lhs, const stack<T,Container>& rhs){
	return (lhs.get_container() == rhs.get_container());
}

template <class T, class Container>
bool operator!= (const stack<T,Container>& lhs, const stack<T,Container>& rhs){
	return (lhs.get_container() != rhs.get_container());
}

template <class T, class Container>
bool operator<  (const stack<T,Container>& lhs, const stack<T,Container>& rhs){
	return (lhs.get_container() < rhs.get_container());
}

template <class T, class Container>
bool operator<= (const stack<T,Container>& lhs, const stack<T,Container>& rhs){
	return (lhs.get_container() <= rhs.get_container());
}

template <class T, class Container>
bool operator>  (const stack<T,Container>& lhs, const stack<T,Container>& rhs){
	return (lhs.get_container() > rhs.get_container());
}

template <class T, class Container>
bool operator>= (const stack<T,Container>& lhs, const stack<T,Container>& rhs){
	return (lhs.get_container() >= rhs.get_container());
}

}
#endif
