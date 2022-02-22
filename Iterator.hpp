#pragma once

#include <cstddef>
#include <iostream>
#include "Iterator_traits.hpp"

namespace ft {
	template<
		class Category,
		class T,
		class Distance = std::ptrdiff_t,
		class Pointer = T*,
		class Reference = T&>
	struct iterator
	{
		typedef Category	iterator_category;
		typedef T			value_type;
		typedef Distance	difference_type;
		typedef	Pointer		pointer;
		typedef	Reference	reference;
	};

	template <typename _Tp>
	struct bidirectional_iterator : ft::iterator<ft::bidirectional_iterator_tag, _Tp> {
		typedef typename ft::iterator<ft::bidirectional_iterator_tag, _Tp>::difference_type		difference_type;
		typedef typename ft::iterator<ft::bidirectional_iterator_tag, _Tp>::value_type			value_type;
		typedef typename ft::iterator<ft::bidirectional_iterator_tag, _Tp>::pointer				pointer;
		typedef typename ft::iterator<ft::bidirectional_iterator_tag, _Tp>::reference			reference;
		typedef typename ft::iterator<ft::bidirectional_iterator_tag, _Tp>::iterator_category	iterator_category;
	};


	// Reverse iterator //
	template<typename _Iterator>
    class reverse_iterator {
	protected:
		_Iterator _iter;
		typedef ft::iterator_traits<_Iterator>			_traits_type;
	public:
		typedef _Iterator								iterator_type;
		typedef typename _traits_type::difference_type	difference_type;
		typedef typename _traits_type::pointer			pointer;
		typedef typename _traits_type::reference		reference;

		reverse_iterator() : _iter() {}
		explicit reverse_iterator(iterator_type iter) : _iter(iter) {}
		reverse_iterator(const reverse_iterator& iter) : _iter(iter._iter) {}
		template<typename Iter>
		reverse_iterator(const reverse_iterator<Iter>& iter) : _iter(iter.base()) {}
		reverse_iterator&	operator=(const reverse_iterator& other) {
			if (this != &other)
				_iter = other._iter;
			return (*this);
		}
		virtual ~reverse_iterator() {}

		iterator_type base() const { return _iter; }

		reference			operator*() const { iterator_type tmp = _iter; return *--tmp; }
		pointer				operator->() const { return &(operator*()); }
		reverse_iterator&	operator++() { --_iter; return *this; }
		reverse_iterator	operator++(int) { reverse_iterator tmp = *this; --_iter; return tmp; }
		reverse_iterator&	operator--() { ++_iter; return *this; }
		reverse_iterator	operator--(int) { reverse_iterator tmp = *this; ++_iter; return tmp; }
		reverse_iterator	operator+(difference_type n) const { return reverse_iterator(_iter - n); }
		reverse_iterator&	operator+=(difference_type n) { _iter -= n; return *this; }
		reverse_iterator	operator-(difference_type n) const { return reverse_iterator(_iter + n); }
		reverse_iterator&	operator-=(difference_type n) { _iter += n; return *this; }
		reference operator[](difference_type n) const { return *(*this + n); }
	};

	template<typename _Iterator>
	bool operator==(const reverse_iterator<_Iterator>& lhs, const reverse_iterator<_Iterator>& rhs) { return lhs.base() == rhs.base(); }

	template<typename _Iterator>
	bool operator<(const reverse_iterator<_Iterator>& lhs, const reverse_iterator<_Iterator>& rhs) { return rhs.base() < lhs.base(); }

	template<typename _Iterator>
	bool operator!=(const reverse_iterator<_Iterator>& lhs, const reverse_iterator<_Iterator>& rhs) { return !(lhs == rhs); }

	template<typename _Iterator>
	bool operator>(const reverse_iterator<_Iterator>& lhs, const reverse_iterator<_Iterator>& rhs) { return rhs < lhs; }

	template<typename _Iterator>
	bool operator<=(const reverse_iterator<_Iterator>& lhs, const reverse_iterator<_Iterator>& rhs) { return !(rhs < lhs); }

	template<typename _Iterator>
	bool operator>=(const reverse_iterator<_Iterator>& lhs, const reverse_iterator<_Iterator>& rhs) { return !(lhs < rhs); }

	template<typename _IteratorL, typename _IteratorR>
	bool operator==(const reverse_iterator<_IteratorL>& lhs, const reverse_iterator<_IteratorR>& rhs) { return lhs.base() == rhs.base(); }

	template<typename _IteratorL, typename _IteratorR>
	bool operator<(const reverse_iterator<_IteratorL>& lhs, const reverse_iterator<_IteratorR>& rhs) { return rhs.base() < lhs.base(); }
	
	template<typename _IteratorL, typename _IteratorR>
	bool operator!=(const reverse_iterator<_IteratorL>& lhs, const reverse_iterator<_IteratorR>& rhs) { return !(lhs == rhs); }

	template<typename _IteratorL, typename _IteratorR>
	bool operator>(const reverse_iterator<_IteratorL>& lhs, const reverse_iterator<_IteratorR>& rhs) { return rhs < lhs; }

	template<typename _IteratorL, typename _IteratorR>
	bool operator<=(const reverse_iterator<_IteratorL>& lhs, const reverse_iterator<_IteratorR>& rhs) { return !(rhs < lhs); }

	template<typename _IteratorL, typename _IteratorR>
	bool operator>=(const reverse_iterator<_IteratorL>& lhs, const reverse_iterator<_IteratorR>& rhs) { return !(lhs < rhs); }

	template<typename _Iterator>
	typename reverse_iterator<_Iterator>::difference_type operator-(const reverse_iterator<_Iterator>& lhs,
	    const reverse_iterator<_Iterator>& rhs) { return rhs.base() - lhs.base(); }

	template<typename _IteratorL, typename _IteratorR>
	typename reverse_iterator<_IteratorL>::difference_type operator-(const reverse_iterator<_IteratorL>& lhs,
	    const reverse_iterator<_IteratorR>& rhs) { return rhs.base() - lhs.base(); }

	template<typename _Iterator>
	reverse_iterator<_Iterator> operator+(typename reverse_iterator<_Iterator>::difference_type n,
	    const reverse_iterator<_Iterator>& lhs) { return reverse_iterator<_Iterator>(lhs.base() - n); }

	// end Reverse iterator //

	// Random_Iterator //
	template<typename _Tp>
    class random_access_iterator : ft::iterator<ft::random_access_iterator_tag, _Tp> {
	private:
		_Tp* _ptr;
		typedef ft::iterator<ft::random_access_iterator_tag, _Tp>	_traits_type;
	public:
		typedef typename _traits_type::iterator_category			iterator_category;
		typedef typename _traits_type::value_type					value_type;
		typedef typename _traits_type::difference_type				difference_type;
		typedef _Tp*												pointer;
		typedef _Tp&												reference;

		random_access_iterator() : _ptr() {}
		random_access_iterator(const random_access_iterator& copy) : _ptr(copy._ptr) {}
		random_access_iterator(pointer ptr) : _ptr(ptr) {}
		template <typename Iter>
		random_access_iterator(const random_access_iterator<Iter>& ptr) : _ptr(ptr.base()) {}

		random_access_iterator &operator=(const random_access_iterator &other) {
			if (this != &other)
				_ptr = other._ptr;
			return *this;
		}
		virtual ~random_access_iterator() {}

		pointer base() const { return _ptr; }

		reference				operator*() const { return *_ptr; }
		pointer					operator->() { return _ptr; }
		random_access_iterator&	operator++() { ++_ptr; return *this; }
		random_access_iterator	operator++(int) { random_access_iterator tmp = *this; ++_ptr; return tmp; }
		random_access_iterator&	operator--() { --_ptr; return *this; }
		random_access_iterator	operator--(int) { random_access_iterator tmp = *this; --_ptr; return tmp; }
		random_access_iterator	operator+(difference_type n) const { return random_access_iterator(_ptr + n); }
		random_access_iterator&	operator+=(difference_type n) { _ptr += n; return *this; }
		random_access_iterator	operator-(difference_type n) const { return random_access_iterator(_ptr - n); }
		random_access_iterator&	operator-=(difference_type n) { _ptr -= n; return *this; }
		reference				operator[](difference_type n) { return *(*this + n); }
	};

	template <typename _Tp>
	bool operator==(const ft::random_access_iterator<_Tp>& lhs, const ft::random_access_iterator<_Tp>& rhs)
	{ return (lhs.base() == rhs.base()); }
	template <typename L, typename R>
	bool operator==(const ft::random_access_iterator<L>& lhs, const ft::random_access_iterator<R>& rhs)
	{ return (lhs.base() == rhs.base()); }

	template <typename _Tp>
	bool operator!=(const ft::random_access_iterator<_Tp>& lhs, const ft::random_access_iterator<_Tp>& rhs)
	{ return (lhs.base() != rhs.base()); }
	template <typename L, typename R>
	bool operator!=(const ft::random_access_iterator<L>& lhs, const ft::random_access_iterator<R>& rhs)
	{ return (lhs.base() != rhs.base()); }

	template <typename _Tp>
	bool operator<(const ft::random_access_iterator<_Tp>& lhs, const ft::random_access_iterator<_Tp>& rhs)
	{ return (lhs.base() < rhs.base()); }
	template <typename L, typename R>
	bool operator<(const ft::random_access_iterator<L>& lhs, const ft::random_access_iterator<R>& rhs)
	{ return (lhs.base() < rhs.base()); }

	template <typename _Tp>
	bool operator>(const ft::random_access_iterator<_Tp>& lhs, const ft::random_access_iterator<_Tp>& rhs)
	{ return (lhs.base() > rhs.base()); }
	template <typename L, typename R>
	bool operator>(const ft::random_access_iterator<L>& lhs, const ft::random_access_iterator<R>& rhs)
	{ return (lhs.base() > rhs.base()); }

	template <typename _Tp>
	bool operator<=(const ft::random_access_iterator<_Tp>& lhs, const ft::random_access_iterator<_Tp>& rhs)
	{ return (lhs.base() <= rhs.base()); }
	template <typename L, typename R>
	bool operator<=(const ft::random_access_iterator<L>& lhs, const ft::random_access_iterator<R>& rhs)
	{ return (lhs.base() <= rhs.base()); }

	template <typename _Tp>
	bool operator>=(const ft::random_access_iterator<_Tp>& lhs, const ft::random_access_iterator<_Tp>& rhs)
	{ return (lhs.base() >= rhs.base()); }
	template <typename L, typename R>
	bool operator>=(const ft::random_access_iterator<L>& lhs, const ft::random_access_iterator<R>& rhs)
	{ return (lhs.base() >= rhs.base()); }

	template <typename _Tp>
	typename ft::random_access_iterator<_Tp>::difference_type	operator-(const ft::random_access_iterator<_Tp>& lhs,
		const ft::random_access_iterator<_Tp>& rhs)
	{ return (lhs.base() - rhs.base()); }
	template <typename L, typename R>
	typename ft::random_access_iterator<L>::difference_type	operator-(const ft::random_access_iterator<L>& lhs,
		const ft::random_access_iterator<R>& rhs)
	{ return (lhs.base() - rhs.base()); }

	template <typename _Tp>
	ft::random_access_iterator<_Tp>	operator+(typename ft::random_access_iterator<_Tp>::difference_type n,
		const ft::random_access_iterator<_Tp>& it)
	{ return ft::random_access_iterator<_Tp>(it.base() + n); }
	// End Random_Iterator //

	template <typename InputIt>
	typename ft::iterator_traits<InputIt>::difference_type iterLen(InputIt first, InputIt last) {
		typename ft::iterator_traits<InputIt>::difference_type len = 0;
		for (; first != last; ++first)
			++len;
		return len;
	}

}