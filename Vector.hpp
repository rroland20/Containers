#pragma once

#include <iostream>
#include <memory>
#include <cstddef>
#include <sstream>
#include "Iterator.hpp"
#include "Is_integral.hpp"
#include "Iterator_traits.hpp"

namespace ft
{
	template<class _Tp, class _Alloc = std::allocator<_Tp> >
	class vector
	{
	public:
		typedef _Alloc									alloc_type;
		typedef _Tp										value_type;
		typedef typename alloc_type::pointer			pointer;
		typedef typename alloc_type::const_pointer		const_pointer;
		typedef typename alloc_type::reference			reference;
		typedef typename alloc_type::const_reference	const_reference;
		typedef ft::random_access_iterator<_Tp>			iterator;
		typedef ft::random_access_iterator<const _Tp>	const_iterator;
		typedef ft::reverse_iterator<iterator>			reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>	const_reverse_iterator;
		typedef size_t									size_type;
		typedef ptrdiff_t								difference_type;
	private:
		alloc_type		_alloc;
		pointer			_start;
		pointer			_finish;
		pointer			_end_of_storage;
	public:
		// Member functions //
		explicit vector(const alloc_type& alloc = alloc_type()) 
			: _alloc(alloc), _start(0), _finish(0), _end_of_storage(0) {}
		
		explicit vector(size_type n, const value_type& value = value_type(), const alloc_type& alloc = alloc_type()) \
			: _alloc(alloc), _start(0), _finish(0), _end_of_storage(0) {
			typedef typename ft::is_integral<size_type>::type	integral;
			_init(n, value, integral());
		}

		template< class InputIt >
		vector(InputIt first, InputIt last, const alloc_type& alloc = alloc_type())
			: _alloc(alloc), _start(0), _finish(0), _end_of_storage(0) {
			typedef typename ft::is_integral<InputIt>::type	integral;
			_init(first, last, integral());
		}

		virtual ~vector() {
			_data_destroy();
			_alloc.deallocate(_start, capacity());
			// std::cout << "asrt\n";
		}

		vector(const vector& copy)
			: _alloc(copy._alloc), _start(0), _finish(0), _end_of_storage(0) { *this = copy; }

		vector	&operator=(const vector& other) {
			if (this != &other) {
				_data_destroy();
				insert(begin(), other.begin(), other.end()); 
			}
			return *this;
		}

		void assign(size_type count, const value_type& value) {
			typedef typename ft::is_integral<size_type>::type	integral;
			_assign(count, value, integral());
		}

		template< class InputIt >
		void assign(InputIt first, InputIt last) {
			typedef typename ft::is_integral<InputIt>::type	integral;
			_assign(first, last, integral());
		}

		alloc_type get_allocator() const { return _alloc; }

	private:
		void	_new_alloc(size_type n) {
			_start = _alloc.allocate(n);
			_finish = _start;
			_end_of_storage = _start + n;
		}

		void _data_destroy() {
			for (; _finish != _start; --_finish)
				_alloc.destroy(_finish);
		}

		void _assign(size_type count, const value_type& value, ft::true_type) {
			if (count > max_size())
				throw std::bad_alloc();
			if (size())
				this->~vector();
			typedef typename ft::is_integral<size_type>::type	integral;
			_init(count, value, integral());
		}

		template< class InputIt >
		void _assign(InputIt first, InputIt last, ft::false_type) {
			size_type len = ft::iterLen(first, last);
			if (len > max_size())
				throw std::bad_alloc();
			if (size())
				this->~vector();
			typedef typename ft::is_integral<InputIt>::type	integral;
			_init(first, last, integral());
		}

		void _init(size_type n, const value_type& value, ft::true_type) {
			_new_alloc(n);
			for (size_type i = 0; i < n; ++i, ++_finish)
				_alloc.construct(_finish, value);
		}

		template< class InputIt >
		void _init(InputIt first, InputIt last, ft::false_type) {
			difference_type len = ft::iterLen(first, last);
			_new_alloc(len);
			for (; first != last; ++first, ++_finish)
				_alloc.construct(_finish, *first);
		}

	public:
		// Element access //
		reference at(size_type pos) {
			if (pos >= size()) {
				std::ostringstream msg;
				msg << "vector::_M_range_check: _n (which is " << pos << ") >= this->size() (which is " << size() << ")";
				throw std::out_of_range(msg.str());
			}
			return (*this)[pos];
		}

		const_reference at(size_type pos) const {
			if (pos >= size()) {
				std::ostringstream msg;
				msg << "vector::_M_range_check: _n (which is " << pos << ") >= this->size() (which is " << size() << ")";
				throw std::out_of_range(msg.str());
			}
			return (*this)[pos];
		}

		reference operator[](size_type pos) { return *(_start + pos); }
		const_reference operator[](size_type pos) const { return *(_start + pos); }

		reference front() { return *_start; }
		const_reference front() const { return *_start; }

		reference back() { return *(_finish - 1); }
		const_reference back() const { return *(_finish - 1); }

		value_type* data() { return _start; }
		const value_type* data() const { return _start; }
		
		// Iterators //
		iterator begin() { return _start; }
		const_iterator begin() const { return _start; }

		iterator end() {return _finish; }
		const_iterator end() const { return _finish; }

		reverse_iterator rbegin() { return reverse_iterator(end()); }
		const_reverse_iterator rbegin() const { return reverse_iterator(end()); }

		reverse_iterator rend() { return reverse_iterator(begin()); }
		const_reverse_iterator rend() const { return reverse_iterator(begin()); }

		// Capacity //
		bool empty() const {
			if (_finish == _start)
				return true;
			return false;
		}

		size_type size() const { return _finish - _start; }
		size_type max_size() const { return _alloc.max_size(); }

		void reserve(size_type new_cap) {
			if (new_cap > max_size())
				throw std::length_error("vector::reserve");
			if (new_cap > capacity()) {
				size_type old_size = size();
				size_type old_cap = capacity();
				pointer old_start = _start;
				pointer old_finish = _finish;
				_new_alloc(new_cap);
				for (; old_start != old_finish ; ++old_start, ++_finish) {
					_alloc.construct(_finish, *old_start);
					_alloc.destroy(old_start);
				}
				old_start -= old_size;
				_alloc.deallocate(old_start, old_cap);
			}
		}

		size_type capacity() const { return _end_of_storage - _start; }

		// Modifiers //
		void clear() { _data_destroy(); }

		iterator insert(iterator pos, const value_type& value) {
			size_type position = &(*pos) - _start;
			insert(pos, 1, value);
			return _start + position;
		}

		void insert(iterator pos, size_type count, const value_type& value) {
			typedef typename ft::is_integral<size_type>::type	integral;
			_insert(pos, count, value, integral());
		}

		template< class InputIt >
		void insert(iterator pos, InputIt first, InputIt last) {
			typedef typename ft::is_integral<InputIt>::type	integral;
			_insert(pos, first, last, integral());
		}

		iterator erase(iterator pos) { return erase(pos, pos + 1); }

		iterator erase(iterator first, iterator last) {
			size_type len = ft::iterLen(first, last);
			size_type begin_er = ft::iterLen(_start, &(*first));
			if (!len)
				return last;
			if (last == end()) {
				size_type s = end() - first;
				_finish -= s;
				return end();
			}
			else {
				pointer beg_er = &(*first);
				pointer end_er = &(*last);
				for (; end_er != _finish; ++end_er, ++beg_er)
					_alloc.construct(beg_er, *end_er);
				pointer new_end = beg_er;
				for (; beg_er != _finish; ++beg_er)
					_alloc.destroy(beg_er);
				_finish = new_end;
				return iterator(_start + begin_er);
			}
		}

		void push_back(const value_type& value) {
			if (size() == capacity()) {
				size_type new_cap;
				if (capacity() != 0)
					new_cap = capacity() * 2;
				else
					new_cap = 1;
				reserve(new_cap);
			}
			_alloc.construct(_finish, value);
			++_finish;
		}

		void pop_back() {
			_alloc.destroy(_finish);
			--_finish;
		}

		void resize(size_type count, value_type value = value_type()) {
			if (count > max_size())
				throw std::length_error("vector::resize ");
			if (count > size())
				insert(end(), count - size(), value);
			else if (count < size()) {
				for (; size() > count;) {
					--_finish;
					_alloc.destroy(_finish);
				}
			}
		}

		void swap( vector& other ) {
			if (this == &other)
				return ;
			alloc_type	tmp_alloc = other._alloc;
			pointer		tmp_start = other._start;
			pointer		tmp_finish = other._finish;
			pointer		tmp_end_of_s = other._end_of_storage;
			other._alloc = _alloc;
			other._start = _start;
			other._finish = _finish;
			other._end_of_storage = _end_of_storage;
			_alloc = tmp_alloc;
			_start = tmp_start;
			_finish = tmp_finish;
			_end_of_storage = tmp_end_of_s;
		}

	private:
		void _insert(iterator pos, size_type count, const value_type& value, ft::true_type) {
			if (!count)
				return ;
			if (size() + count <= capacity()) {
				iterator it = _finish + count - 1;
				for (; it != pos + count - 1; --it)
					_alloc.construct(&(*it), *(it - count));
				for (size_type i = 0; i < count; ++i, --it)
					_alloc.construct(&(*it), value);
				_finish += count;
				std::cout << "size() + count <= capacity(): " << *_start << " - " << *_finish << " - " << *_end_of_storage << std::endl;
			}
			else {
				size_type new_cap = capacity() * 2;
				if (new_cap < size() + count)
					new_cap = size() + count;
				if (new_cap > max_size())
					throw std::length_error("vector::insert ");
				size_type pos_idx = &(*pos) - _start;
				size_type old_size = size();
				size_type old_cap = capacity();
				pointer old_start = _start;
				_new_alloc(new_cap);
				for (size_type i = 0; i < old_size + count; ++i, ++_finish) {
					if (i >= pos_idx && i < pos_idx + count)
						_alloc.construct(_finish, value);
					else {
						_alloc.construct(_finish, *old_start);
						_alloc.destroy(old_start);
						++old_start;
					}
				}
				std::cout << "size() + count > capacity(): " << *_start << " - " << *_finish << " - " << *_end_of_storage << std::endl;
				old_start -= old_size;
				_alloc.deallocate(old_start, old_cap);
			}
		}

		template <class InputIt>
		void _insert(iterator pos, InputIt first, InputIt last, ft::false_type) {
			size_type count = ft::iterLen(first, last);
			if (!count)
				return ;
			if (size() + count <= capacity()) {
				iterator it = _finish + count - 1;
				for (; it != pos + count - 1; --it)
					_alloc.construct(&(*it), *(it - count));
				for (size_type i = 0; i < count; ++i, --it) {
					--last;
					_alloc.construct(&(*it), *last);
				}
				_finish += count;
			}
			else {
				size_type new_cap = capacity() * 2;
				if (new_cap < size() + count)
					new_cap = size() + count;
				if (new_cap > max_size())
					throw std::length_error("vector::insert ");
				size_type pos_idx = &(*pos) - _start;
				size_type old_size = size();
				size_type old_cap = capacity();
				pointer old_start = _start;
				_new_alloc(new_cap);
				for (size_type i = 0; i < old_size + count; ++i, ++_finish) {
					if (i >= pos_idx && i < pos_idx + count) {
						_alloc.construct(_finish, *first);
						++first;
					}
					else {
						_alloc.construct(_finish, *old_start);
						_alloc.destroy(old_start);
						++old_start;
					}
				}
				old_start -= old_size;
				_alloc.deallocate(old_start, old_cap);
			}
		}
	};
	// Non-member functions //
	// template <class T, class Alloc>
	// bool operator==(const std::vector<T,Alloc>& lhs, const std::vector<T,Alloc>& rhs)
	// { return lhs == rhs; }
}
