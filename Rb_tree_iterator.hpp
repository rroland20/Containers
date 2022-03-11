#pragma once

#include "iterator.hpp"
#include "map_utils.hpp"

namespace ft {

	template <typename T>
	struct RBTree_iterator : public ft::bidirectional_iterator<T> {
		typedef ft::bidirectional_iterator<T>			bid_iter;

		typedef T  										value_type;
		typedef typename bid_iter::reference			reference;
		typedef typename bid_iter::pointer				pointer;

		typedef typename bid_iter::iterator_category	iterator_category;
		typedef typename bid_iter::difference_type		difference_type;

		typedef RBTree_iterator<T>						_Self;
		typedef Rb_tree_node<T>*						_Base_ptr;
		typedef Rb_tree_node<T>*						_Link_type;
		_Base_ptr _node;

		RBTree_iterator() : _node(0) {}
		explicit RBTree_iterator(_Base_ptr node) : _node(node) {}

		RBTree_iterator(const RBTree_iterator& copy) : _node(copy._node) {}
		RBTree_iterator	&operator=(const RBTree_iterator& other) {
			if (this != &other)
				_node = other._node;
			return *this;
		}

		~RBTree_iterator() {}

		reference operator*() const { return _node->value; }
		pointer operator->() const { return &(_node->value); }
		_Self& operator++() { _node = _Rb_tree_increment(); return *this; }
		_Self operator++(int) { _Self tmp = *this; _node = _Rb_tree_increment(); return tmp; }
		_Self& operator--() { _node = _Rb_tree_decrement(); return *this; }
		_Self operator--(int) { _Self tmp = *this; _node = _Rb_tree_decrement(); return tmp; }
		friend bool operator==(const _Self& x, const _Self& y) { return x._node == y._node; }
		friend bool operator!=(const _Self& x, const _Self& y) { return x._node != y._node; }

		private:
			_Base_ptr _Rb_tree_increment() {
				_Base_ptr x = _node;
				if (x->right != 0) {
					x = x->right;
					while (x->left != 0)
						x = x->left;
				}
				else {
					_Base_ptr y = x->parent;
					while (x == y->right)
					{
						x = y;
						y = y->parent;
					}
					if (x->right != y)
						x = y;
				}
				return x;
			}

			_Base_ptr _Rb_tree_decrement() {
				_Base_ptr x = _node;
				if (x->color == red && x->parent->parent == x)
					x = x->right;
				else if (x->left != 0) {
					_Base_ptr	y = x->left;
					while (y->right != 0)
						y = y->right;
					x = y;
				}
				else {
					_Base_ptr y = x->parent;
					while (x == y->left) {
						x = y;
						y = y->parent;
					}
					x = y;
				}
				return x;
			}
	};

	template <typename T>
	struct RBTree_const_iterator : public ft::bidirectional_iterator<const T> {
		typedef ft::bidirectional_iterator<T>			bid_iter;

		typedef T  										value_type;
		typedef typename bid_iter::reference			reference;
		typedef typename bid_iter::pointer				pointer;

		typedef RBTree_iterator<T>						iterator;

		typedef typename bid_iter::iterator_category	iterator_category;
		typedef typename bid_iter::difference_type		difference_type;

		typedef RBTree_const_iterator<T>				_Self;
		typedef const Rb_tree_node<T>*					_Base_ptr;
		typedef const Rb_tree_node<T>*					_Link_type;
		_Base_ptr _node;

		RBTree_const_iterator() : _node() {}
		explicit RBTree_const_iterator(_Base_ptr node) : _node(node) {}
		RBTree_const_iterator(const iterator& copy) : _node(copy._node) {}
		template <typename Iter>
		RBTree_const_iterator(const RBTree_iterator<Iter>& i) : _node(i._node) {}

		RBTree_const_iterator	&operator=(const RBTree_const_iterator& other) {
			if (this != &other)
				_node = other._node;
			return *this;
		}
		~RBTree_const_iterator() {}

		iterator _M_const_cast() const { return iterator(const_cast<_Base_ptr>(_node)); }
		reference operator*() const { return _node->value; }
		pointer operator->() const { return &(_node->value); }
		_Self&		operator++() { _node = _Rb_tree_increment(); return *this; }
		_Self		operator++(int) { _Self tmp = *this; _node = _Rb_tree_increment(); return tmp; }
		_Self&		operator--() { _node = _Rb_tree_decrement(); return *this; }
		_Self		operator--(int) { _Self tmp = *this; _node = _Rb_tree_decrement(); return tmp; }
		friend bool	operator==(const _Self&x, const _Self&y) { return x._node == y._node; }
		friend bool	operator!=(const _Self&x, const _Self&y) { return x._node != y._node; }

	private:
		_Base_ptr _Rb_tree_increment() {
			_Base_ptr x = _node;
			if (x->right != 0) {
				x = x->right;
				while (x->left != 0)
					x = x->left;
			}
			else {
				_Base_ptr y = x->parent;
				while (x == y->right) {
					x = y;
					y = y->parent;
				}
				if (x->right != y)
					x = y;
			}
			return x;
		}

		_Base_ptr _Rb_tree_decrement() {
			_Base_ptr x = _node;
			if (x->color == red && x->parent->parent == x)
				x = x->right;
			else if (x->left != 0) {
				_Base_ptr	y = x->left;
				while (y->right != 0)
					y = y->right;
				x = y;
			}
			else {
				_Base_ptr y = x->parent;
				while (x == y->left) {
					x = y;
					y = y->parent;
				}
				x = y;
			}
			return x;
		}
	};
}