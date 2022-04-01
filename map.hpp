#pragma once

#include "utils/pair.hpp"
#include "utils/map_utils.hpp"
#include "utils/Rb_tree.hpp"
#include "utils/equal_and_lexografical_compare.hpp"
#include <memory>

namespace ft {
	template< class Key, class T, class Compare = std::less<Key>, 
		class Allocator = std::allocator<ft::pair<const Key, T> > >
	class map {
	public:
		typedef Key						key_type;
		typedef T						mapped_type;
		typedef ft::pair<const Key, T>	value_type;
		typedef Compare					key_compare;
		typedef Allocator				allocator_type;
		
		// Member classes //
		class value_compare: public ft::binary_function<value_type, value_type, bool> {
      	protected:
			key_compare comp;

		public:
			value_compare(key_compare c) : comp(c) {}
			bool operator()(const value_type& x, const value_type& y) const
			{ return comp(x.first, y.first); }
		};
	private:
		typedef Rb_tree<key_type, value_type, ft::Select1st<value_type>,
		    key_compare, allocator_type> _tree_type;
		key_compare _comp;
		_tree_type tree;
	public:
		typedef typename allocator_type::pointer			pointer;
		typedef typename allocator_type::const_pointer	 	const_pointer;
		typedef typename allocator_type::reference		 	reference;
		typedef typename allocator_type::const_reference	const_reference;
		typedef typename _tree_type::iterator				iterator;
		typedef typename _tree_type::const_iterator			const_iterator;
		typedef typename _tree_type::size_type		 		size_type;
		typedef typename _tree_type::difference_type	 	difference_type;
		typedef typename _tree_type::reverse_iterator	 	reverse_iterator;
		typedef typename _tree_type::const_reverse_iterator	const_reverse_iterator;

		// Member functions //
		explicit map(const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type())
			: _comp(comp), tree(comp, alloc) {}

		map(const map& x) : _comp(x._comp), tree(x.tree) {}

		template<typename InputIterator>
		map(InputIterator first, InputIterator last, const key_compare& comp = key_compare(),
			const allocator_type& alloc = allocator_type()) : _comp(comp), tree(comp, alloc)
		{ tree.insert_range_unique(first, last); }

		map& operator=(const map& other) {
			if (this != &other) {
				_comp = other._comp;
				tree = other.tree;
			}
			return *this;
		}

		~map() {}

		// Element access //
		mapped_type& at( const key_type& key ) {
			iterator i = lower_bound(key);
			if (i == end() || _comp(key, (*i).first))
	 			throw std::out_of_range("map::at");
			return (*i).second;
		}

		const mapped_type& at(const key_type& key) const {
			const_iterator i = lower_bound(key);
			if (i == end() || _comp(key, (*i).first))
	 			throw std::out_of_range("map::at");
			return (*i).second;
		}

		mapped_type& operator[](const key_type& key) {
			iterator i = tree.lower_bound(key);
			if (i == tree.end() || _comp(key, (*i).first))
				i = insert(i, value_type(key, mapped_type()));
			return (*i).second;
		}

		// Iterators //
		iterator begin() { return tree.begin(); }
		const_iterator begin() const { return tree.begin(); }
		iterator end() { return tree.end(); }
		const_iterator end() const { return tree.end(); }
		reverse_iterator rbegin() { return tree.rbegin(); }
		const_reverse_iterator rbegin() const { return tree.rbegin(); }
		reverse_iterator rend() { return tree.rend(); }
		const_reverse_iterator rend() const { return tree.rend(); }

		// Capacity //
		bool empty() const { return tree.empty(); }
		size_type size() const { return tree.size(); }
		size_type max_size() const { return tree.max_size(); }

		// Modifiers //
		void clear() { return tree.clear(); }
		ft::pair<iterator, bool> insert(const value_type& x) { return tree.insert_unique(x); }
		iterator insert(iterator hint, const value_type& value) { return tree.insert_unique(hint, value); }
		template <class InputIt>
		void insert(InputIt first, InputIt last) { tree.insert_range_unique(first, last); }
		void erase( iterator pos ) { tree.erase(pos); }
		void erase( iterator first, iterator last ) { tree.erase(first, last); }
		size_type erase(const key_type& key) { return tree.erase(key); }
		void swap(map& other) { tree.swap(other.tree); }

		// Lookup //
		size_type count( const key_type& key ) const {
			if ( tree.find(key) == tree.end())
				return 0;
			return 1;
		}
		iterator find( const key_type& key ) { return tree.find(key); }
		const_iterator find( const key_type& key ) const { return tree.find(key); }
		ft::pair<iterator,iterator> equal_range(const key_type& key) { return tree.equal_range(key); }
		ft::pair<const_iterator,const_iterator> equal_range(const key_type& key) const { return tree.equal_range(key); }
		iterator lower_bound( const key_type& key ) { return tree.lower_bound(key); }
		const_iterator lower_bound( const key_type& key ) const { return tree.lower_bound(key); }
		iterator upper_bound( const key_type& key ) { return tree.upper_bound(key); }
		const_iterator upper_bound( const key_type& key ) const { return tree.upper_bound(key); }

		// Observers //
		key_compare key_comp() const { return _comp; }
		value_compare value_comp() const { return value_compare(_comp); }

		template <typename K1, typename T1, typename C1, typename A1>
		friend bool operator==(const map<K1, T1, C1, A1>& lhs, const map<K1, T1, C1, A1>& rhs);

		template <typename K1, typename T1, typename C1, typename A1>
		friend bool operator<(const map<K1, T1, C1, A1>& lhs, const map<K1, T1, C1, A1>& rhs);
	};
	// Non-member functions //
	template<class Key, class T, class Compare, class Alloc>
	bool operator==(const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs )
	{ return lhs.tree == rhs.tree; }

	template<class Key, class T, class Compare, class Alloc>
	bool operator!=(const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs )
	{ return !(lhs == rhs); }

	template<class Key, class T, class Compare, class Alloc>
	bool operator<(const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs)
	{ return lhs.tree < rhs.tree; }

	template<class Key, class T, class Compare, class Alloc>
	bool operator<=(const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs )
	{ return !(rhs < lhs); }

	template<class Key, class T, class Compare, class Alloc>
	bool operator>(const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs )
	{ return rhs < lhs; }

	template<class Key, class T, class Compare, class Alloc>
	bool operator>=(const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs )
	{ return !(lhs < rhs); }

	template< class Key, class T, class Compare, class Alloc >
	void swap(map<Key,T,Compare,Alloc>& lhs, map<Key,T,Compare,Alloc>& rhs)
	{ lhs.swap(rhs); }
}
