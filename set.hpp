#pragma once

#include <memory>
#include "Rb_tree.hpp"
#include "Rb_tree_iterator.hpp"
#include "iterator.hpp"
#include "pair.hpp"
#include "map_utils.hpp"

namespace ft {
	template<class Key, class Compare = std::less<Key>, class Alloc = std::allocator<Key> >
	class set {
	public:
		typedef Key     key_type;
		typedef Key     value_type;
		typedef Compare key_compare;
		typedef Compare value_compare;
		typedef Alloc   allocator_type;
	private:
		typedef Rb_tree<key_type, value_type, Identity<value_type>, key_compare, allocator_type> _tree_type;
		
		key_compare	_comp;
		_tree_type	_tree;
	public:
		typedef typename allocator_type::pointer			pointer;
		typedef typename allocator_type::const_pointer		const_pointer;
		typedef typename allocator_type::reference			reference;
		typedef typename allocator_type::const_reference	const_reference;
		typedef typename _tree_type::const_iterator			iterator;
		typedef typename _tree_type::const_iterator			const_iterator;
		typedef typename _tree_type::const_reverse_iterator	reverse_iterator;
		typedef typename _tree_type::const_reverse_iterator	const_reverse_iterator;
		typedef typename _tree_type::size_type				size_type; // check
		typedef typename _tree_type::difference_type		difference_type; // check

		// Member functions //
		explicit set(const key_compare& c = key_compare(), const allocator_type& alloc = allocator_type())
			: _comp(c), _tree(c, alloc) {}

		template<typename InputIt>
		set(InputIt first, InputIt last, const key_compare& c = key_compare(),
			const allocator_type& alloc = allocator_type()) : _comp(c), _tree(c, alloc)
		{ _tree.insert_range_unique(first, last); }

		set(const set& x) : _comp(x._comp), _tree(x._tree) {}

		set& operator=(const set& other) {
			if (this != &other) {
				_comp = other._comp;
				_tree = other._tree;
			}
			return (*this);
		}

		~set() {}

		// Iterators //
		iterator begin() { return _tree.begin(); }
		const_iterator begin() const { return _tree.begin(); }

		iterator end() { return _tree.end(); }
		const_iterator end() const { return _tree.end(); }

		reverse_iterator rbegin() { return _tree.rbegin(); }
		const_reverse_iterator rbegin() const { return _tree.rbegin(); }

		reverse_iterator rend() { return _tree.rend(); }
		const_reverse_iterator rend() const { return _tree.rend(); }

		// Capacity //
		bool empty() const { return _tree.empty(); }

		size_type size() const { return _tree.size(); }

		size_type max_size() const { return _tree.max_size(); }

		// Modifiers //
		void clear() { _tree.clear(); }

		ft::pair<iterator,bool> insert(const value_type& value) { return _tree.insert_unique(value); }
		iterator insert(iterator hint, const value_type& value) { return _tree.insert_unique(hint, value); }
		template< class InputIt >
		void insert(InputIt first, InputIt last) { _tree.insert_range_unique(first, last); }

		void erase(iterator pos) { _tree.erase(pos); }
		void erase(iterator first, iterator last) { _tree.erase(first, last); }
		size_type erase(const key_type& key) { return _tree.erase(key); }

		void swap(set& other) { _tree.swap(other._tree); }

		// Lookup //
		size_type count(const key_type& key) const { return _tree.find(key) == _tree.end() ? 0 : 1; }

		iterator find(const key_type& key) { return _tree.find(key); }
		const_iterator find(const key_type& key) const { return _tree.find(key); }

		ft::pair<iterator,iterator> equal_range(const key_type& key) { return _tree.equal_range(key); }
		ft::pair<const_iterator,const_iterator> equal_range(const key_type& key) const { return _tree.equal_range(key); }

		iterator lower_bound(const key_type& key) { return _tree.lower_bound(key); }
		const_iterator lower_bound(const key_type& key) const { return _tree.lower_bound(key); }

		iterator upper_bound( const key_type& key ) { return _tree.upper_bound(key); }
		const_iterator upper_bound( const key_type& key ) const { return _tree.upper_bound(key); }

		// Observers //
		key_compare key_comp() const { return _comp; }

		value_compare value_comp() const { return value_compare(_comp); }

		template<typename K1, typename C1, typename A1>
		friend bool operator==(const set<K1, C1, A1>&, const set<K1, C1, A1>&);

		template<typename K1, typename C1, typename A1>
		friend bool operator<(const set<K1, C1, A1>&, const set<K1, C1, A1>&);
	};
	// Non-member functions //
	template<class Key, class Compare, class Alloc> // check
	bool operator==(const set<Key,Compare,Alloc>& lhs, const set<Key,Compare,Alloc>& rhs)
	{ return lhs._tree == rhs._tree; }

	template<class Key, class Compare, class Alloc>
	bool operator!=(const set<Key,Compare,Alloc>& lhs, const set<Key,Compare,Alloc>& rhs)
	{ return !(lhs == rhs); }

	template<class Key, class Compare, class Alloc>
	bool operator<(const set<Key,Compare,Alloc>& lhs, const set<Key,Compare,Alloc>& rhs)
	{ return lhs._tree < rhs._tree; }

	template<class Key, class Compare, class Alloc>
	bool operator<=(const set<Key,Compare,Alloc>& lhs, const set<Key,Compare,Alloc>& rhs)
	{ return !(rhs < lhs); }

	template<class Key, class Compare, class Alloc>
	bool operator>(const set<Key,Compare,Alloc>& lhs, const set<Key,Compare,Alloc>& rhs)
	{ return rhs < lhs; }

	template< class Key, class Compare, class Alloc >
	bool operator>=(const set<Key,Compare,Alloc>& lhs, const set<Key,Compare,Alloc>& rhs)
	{ return !(lhs < rhs); }

	template<class Key, class Compare, class Alloc>
	void swap(set<Key,Compare,Alloc>& lhs, set<Key,Compare,Alloc>& rhs)
	{ lhs.swap(rhs); }
}
