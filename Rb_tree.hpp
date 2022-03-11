#pragma once

#include <memory>
#include "pair.hpp"
#include "map_utils.hpp"
#include "Rb_tree_iterator.hpp"
#include "equal_and_lexografical_compare.hpp"

namespace ft {
    template<typename Key, typename Val, typename KeyOfValue,
	   typename Compare, typename Alloc = std::allocator<Val> >
    class Rb_tree {

		typedef typename Alloc::template rebind<Rb_tree_node<Val> >::other	node_allocator_type;

    protected:
		typedef Rb_tree_node<Val>*			node;
		typedef const Rb_tree_node<Val>*	const_node;
	
	public:
		typedef Key 						key_type;
		typedef Val 						value_type;
		typedef value_type* 				pointer;
		typedef const value_type* 			const_pointer;
		typedef value_type& 				reference;
		typedef const value_type& 			const_reference;
		typedef size_t 						size_type;
		typedef ptrdiff_t 					difference_type;
		typedef Alloc 						allocator_type;
		typedef ft::RBTree_iterator<value_type>			iterator;
		typedef ft::RBTree_const_iterator<value_type>	const_iterator;
		typedef ft::reverse_iterator<iterator>			reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>	const_reverse_iterator;

		// Member function //
		Rb_tree() {}
		Rb_tree(const Compare& comp, const allocator_type& alloc = allocator_type())
      		: _comp(comp), _alloc(alloc), _size(0) { _create_header(); }
		Rb_tree(const Rb_tree& cpy) : _comp(cpy._comp), _alloc(cpy._alloc), _size(cpy._size) {
			_create_header();
			if (cpy.header->parent != 0)
				header->parent = copy(cpy);
		}

		Rb_tree& operator=(const Rb_tree& other) {
			if (this != &other) {
				clear();
				_comp = other._comp;
				get_key = other.get_key;
				if (other.header->parent != 0)
					header->parent = copy(other);
			}
			return *this;
		}

		~Rb_tree() {
			erase(header->parent);
			node_alloc.deallocate(header, 1);
		}

		// Accessors //
		iterator				begin() { return iterator(header->left); }
		const_iterator			begin() const { return const_iterator(header->left); }
		iterator				end() { return iterator(header); }
		const_iterator			end() const { return const_iterator(header); }
		reverse_iterator		rbegin() { return reverse_iterator(end()); }
		const_reverse_iterator	rbegin() const { return const_reverse_iterator(end()); }
		reverse_iterator		rend() { return reverse_iterator(begin()); }
		const_reverse_iterator	rend() const { return const_reverse_iterator(begin()); }

		bool empty() const { return _size == 0; }
		size_type size() const { return _size; }
		size_type max_size() const { return node_alloc.max_size(); }
		void swap(Rb_tree& t) {
			ft::swap(header, t.header);
			ft::swap(_size, t._size);
		}

		// Insert/erase //
		ft::pair<iterator, bool> insert_unique(const value_type& val) {
			typedef ft::pair<iterator, bool> _Res;
      		ft::pair<node, node> res = _get_insert_unique_pos(get_key(val));

      		if (res.second) {
	  			return _Res(_insert(res.first, res.second, val), true);
			}
			return _Res(iterator(res.first), false);
    	}

		iterator insert_unique(const_iterator pos, const value_type& val) {
			ft::pair<node, node> res = _get_insert_hint_unique_pos(pos, get_key(val));

      		if (res.second)
				return _insert(res.first, res.second, val);
      		return iterator(res.first);
		}

		template<typename InputIterator>
		void insert_range_unique(InputIterator first, InputIterator last) {
			for (; first != last; ++first)
				insert_unique(end(), *first);
		}

	private:
		Compare								_comp;
		allocator_type						_alloc;
		node_allocator_type					node_alloc;
		node								header;
		size_type							_size;
		KeyOfValue							get_key;

		void put_node(node y) {
			_alloc.deallocate(y, 1);
		}

		void destroy_node(node y) {
			_alloc.destroy(&y->value);
		}

		void drop_node(node y) {
			destroy_node(y);
			put_node(y);
		}

		void _M_erase_aux(const_iterator position) {
			node y = rebalance_for_erase(position._node);
			drop_node(y);
			--size;
		}

		void _M_erase_aux(const_iterator first, const_iterator last) {
			if (first == begin() && last == end())
				clear();
      		else
				while (first != last)
	  				_M_erase_aux(first++);
		}

		void _create_header() {
			header = node_alloc.allocate(1);
			_reset_header();
			header->color = red;
		}

		node	create_node(const value_type& x)
		{
			node tmp = node_alloc.allocate(1);
			_alloc.construct(&(tmp->value), x);
			tmp->color = black;
			tmp->parent = 0;
			tmp->left = 0;
			tmp->right = 0;
			return tmp;
		}

		void _reset_header() {
			header->left = header;
			header->right = header;
			header->parent = 0;
		}

	public:
		void erase(iterator position) { if(position != end()) _M_erase_aux(position); }

		size_type erase(const key_type& key) {
			ft::pair<iterator, iterator> p = _equal_range(key);
			const size_type old_size = _size;

			erase_aux(p.first, p.second);
			return old_size - _size;
		}

		void erase(iterator first, iterator last) { _M_erase_aux(first, last); }

		void clear() {
			erase(header->parent);
			_reset_header();
			_size = 0;
		}

		// Set operations //
		iterator find(const key_type& key) {
			iterator j = _M_lower_bound(header->parent, header, key);
			return (j == end() || _comp(key, get_key(j._node->value))) ? end() : j;
		}

		const_iterator find(const key_type& key) const {
			iterator j = _M_lower_bound(header->parent, header, key);
			return (j == end() || _comp(key, get_key(j._node->value))) ? end() : j;
		}

 		iterator lower_bound(const key_type& key)
		{ return _M_lower_bound(header->parent, header, key); }

		const_iterator lower_bound(const key_type& key) const
		{ return _M_lower_bound(header->parent, header, key); }

		iterator upper_bound(const key_type& key)
		{ return _M_upper_bound(header->parent, header, key); }

		const_iterator upper_bound(const key_type& key) const
		{ return _M_upper_bound(header->parent, header, key); }

		pair<iterator, iterator> equal_range(const key_type& key)
		{ return _equal_range(key); }

		pair<const_iterator, const_iterator> equal_range(const key_type& key) const
		{ return _equal_range(key); }

		// Operators //
		friend bool operator==(const Rb_tree& x, const Rb_tree& y)
		{ return x.size() == y.size() && ft::equal(x.begin(), x.end(), y.begin()); }

		friend bool operator<(const Rb_tree& x, const Rb_tree& y)
		{ return ft::lexicographical_compare(x.begin(), x.end(), y.begin(), y.end()); }

		friend bool operator!=(const Rb_tree& x, const Rb_tree& y)
		{ return !(x == y); }

		friend bool operator>(const Rb_tree& x, const Rb_tree& y)
		{ return y < x; }

		friend bool operator<=(const Rb_tree& x, const Rb_tree& y)
		{ return !(y < x); }

		friend bool operator>=(const Rb_tree& x, const Rb_tree& y)
		{ return !(x < y); }

	private:
		iterator _M_lower_bound(node x, node y, const key_type& key) {
			while (x != 0)
				if (!_comp(get_key(x->value), key)) {
					y = x;
					x = x->left;
				}
				else
					x = x->right;
			return iterator(y);
		}

		const_iterator _M_lower_bound(const_node x, const_node y, const key_type& key) const {
			while (x != 0)
				if (!_comp(get_key(x->value), key)) {
					y = x;
					x = x->left;
				}
				else
					x = x->right;
			return const_iterator(y);
		}

		iterator _M_upper_bound(node x, node y, const key_type& key) {
			while (x != 0)
				if (_comp(key, get_key(x->value))) {
	  				y = x;
					x = x->left;
				}
				else
	  				x = x->right;
      		return iterator(y);
		}

		const_iterator _M_upper_bound(const_node x, const_node y, const key_type& key) const {
			while (x != 0)
				if (_comp(key, get_key(x->value))) {
	  				y = x;
					x = x->left;
				}
				else
	  				x = x->right;
      		return const_iterator(y);
		}

		ft::pair<iterator, iterator> _equal_range(const key_type& key) {
			node x = header->parent;
			node y = header;
			while (x != 0) {
				if (_comp(get_key(x->value), key))
					x = x->right;
				else if (_comp(key, get_key(x->value))) {
					y = x;
					x = x->left;
				}
				else {
					node xu(x);
					node yu(y);
					y = x;
					x = x->left;
					xu = xu->right;
					return ft::pair<iterator, iterator>(_M_lower_bound(x, y, key), _M_upper_bound(xu, yu, key));
				}
			}
			return ft::pair<iterator, iterator>(iterator(y), iterator(y));
    	}

		ft::pair<const_iterator, const_iterator>	_equal_range(const key_type& key) const {
			node x = header->parent;
			node y = header;
			while (x != 0) {
				if (_comp(get_key(x->value), key))
					x = x->right;
				else if (_comp(key, get_key(x->value))) {
					y = x;
					x = x->left;
				}
				else {
					node xu(x);
					node yu(y);
					y = x;
					x = x->left;
					xu = xu->right;
					return ft::pair<const_iterator, const_iterator>(_M_lower_bound(x, y, key), _M_upper_bound(xu, yu, key));
				}
			}
			return ft::pair<const_iterator, const_iterator>(const_iterator(y), const_iterator(y));
		}

		node minimum(node x) {
			while(x->left)
				x = x->left;
			return x;
		}

		node maximum(node x) {
			while(x->right)
				x = x->right();
			return x;
		}

		void RBtree_rotate_left(node x, node& root) {
			node y = x->right;
			x->right = y->left;
			if (y->left != 0)
				y->left->parent = x;
			y->parent = x->parent;
			
			if (x == root)
				root = y;
			else if (x == x->parent->left)
				x->parent->left = y;
			else
				x->parent->right = y;
			y->left = x;
			x->parent = y;
		}

		void RBtree_rotate_right(node x, node& root) {
			node y = x->left;
			x->left = y->right;
			if(y->right != 0)
				y->right->parent=x;
			y->parent = x->parent;

			if(x == root)
				root = y;
			else if(x == x->parent->right)
				x->parent->right = y;
			else
				x->parent->left = y;
			y->right = x;
			x->parent = y;
		}
		
		node rebalance_for_erase(node z) {
			node& root = header->parent;
			node& leftmost = header->left;
			node& rightmost = header->right;
			node y = z;
			node x = 0;
			node x_parent = 0;

			if (y->left == 0)
		      	x = y->right;
	     	else if (y->right == 0)
			    x = y->left;
			else {
		       	y = y->right;
		   		while (y->left != 0)
				   	y = y->left;
			   	x = y->right;
			}
			if (y != z) {
				z->left->parent = y;
				y->left = z->left;
				if (y != z->right) {
					x_parent = y->parent;
					if (x) x->parent = y->parent;
						y->parent->left = x;
					y->right = z->right;
					z->right->parent = y;
				}
				else
					x_parent = y;
				if (root == z)
					root = y;
				else if (z->parent->left == z)
					z->parent->left = y;
				else
					z->parent->right = y;
				y->parent = z->parent;
				ft::swap(y->color, z->color);
				y = z;
			}
			else {
				x_parent = y->parent;
				if (x)
					x->parent = y->parent;
				if (root == z)
					root = x;
				else if (z->parent->left == z)
					z->parent->left = x;
				else
					z->parent->right = x;
				if (leftmost == z) {
					if (z->right == 0)
						leftmost = z->parent;
					else
						leftmost = minimum(x);
				}
				if (rightmost == z) {
					if (z->left == 0)
						rightmost = z->parent;
					else
						rightmost = maximum(x);
				}
			}
			if (y->color != red) {
				while (x != root && (x == 0 || x->color == black)) {
					if (x == x_parent->left) {
						node	w = x_parent->right;
						if (w->color == red) {
							w->color = black;
							x_parent->color = red;
							RBtree_rotate_left(x_parent, root);
							w = x_parent->right;
						}
						if ((w->left == 0 || w->left->color == black) && \
								(w->right == 0 || w->right->color == black)) {
							w->color = red;
							x = x_parent;
							x_parent = x_parent->parent;
						}
						else {
							if (w->right == 0 || w->right->color == black) {
								w->left->color = black;
								w->color = red;
								RBtree_rotate_right(w, root);
								w = x_parent->right;
							}
							w->color = x_parent->color;
							x_parent->color = black;
							if (w->right)
								w->right->color = black;
							RBtree_rotate_left(x_parent, root);
							break;
						}
					}
					else {
						node	w = x_parent->left;
						if (w->color == red) {
							w->color = black;
							x_parent->color = red;
							RBtree_rotate_right(x_parent, root);
							w = x_parent->left;
						}
						if ((w->right == 0 || w->right->color == black) && \
							(w->left == 0 || w->left->color == black)) {
							w->color = red;
							x = x_parent;
							x_parent = x_parent->parent;
						}
						else {
							if (w->left == 0 || w->left->color == black) {
								w->right->color = black;
								w->color = red;
								RBtree_rotate_left(w, root);
								w = x_parent->left;
							}
							w->color = x_parent->color;
							x_parent->color = black;
							if (w->left)
								w->left->color = black;
							RBtree_rotate_right(x_parent, root);
							break;
						}
					}
				}
				if (x)
					x->color = black;
			}
			return y;
		}

		node clone_node(node x) {
			node tmp = create_node(x->value);

			tmp->color = x->color;
			return tmp;
		}

		node copy(node x, node p) {
			node top = clone_node(x);

			top->parent = p;
			if (x->right)
				top->right = copy(x->right, top);
			p = top;
			x = x->left;
			while (x != 0) {
				node y = clone_node(x);
				p->left = y;
				y->parent = p;
				if (x->right)
					y->right = copy(x->right, y);
				p = y;
				x = x->left;
			}
			return top;
		}

		void erase(node x) {
			while (x != 0) {
				erase(x->right);
				node y = x->left;
				drop_node(x);
				x = y;
			}
		}

		node copy(const Rb_tree& x) {
			node root = copy(x.header->parent, header);
			header->left = minimum(root);
			header->right = maximum(root);
			_size = x._size;
			return root;
		}

		void _insert_and_rebalance(const bool insert_left, node x, node p) {
			node& root = header->parent;

			x->parent = p;
			x->left = 0;
			x->right = 0;
			x->color = red;

			if (insert_left) {
				p->left = x;
				if (p == header) {
					header->parent = x;
					header->right = x;
				}
				else if (p == header->left)
					header->left = x;
		    }
			else {
				p->right = x;
				if (p == header->right)
					header->right = x;
			}
			while (x != root && x->parent->color == red) {
				node const xpp = x->parent->parent;

				if (x->parent == xpp->left) {
					node const y = xpp->right;
					if (y && y->color == red) {
						x->parent->color = black;
						y->color = black;
						xpp->color = red;
						x = xpp;
					}
					else {
						if (x == x->parent->right) {
							x = x->parent;
							RBtree_rotate_left(x, root);
						}
						x->parent->color = black;
						xpp->color = red;
						RBtree_rotate_right(xpp, root);
					}
				}
				else {
					node const y = xpp->left;
					if (y && y->color == red) {
						x->parent->color = black;
						y->color = black;
						xpp->color = red;
						x = xpp;
					}
					else {
						if (x == x->parent->left) {
							x = x->parent;
							RBtree_rotate_right(x, root);
						}
						x->parent->color = black;
						xpp->color = red;
						RBtree_rotate_left(xpp, root);
					}
				}
			}
			root->color = black;
		}

		iterator _insert(node x, node p, const value_type& value) {
			bool insert_left = (x != 0 || p == header || _comp(get_key(value), get_key(p->value)));

			node z = create_node(value);

			_insert_and_rebalance(insert_left, z, p);
			++_size;
			return iterator(z);
		}

		pair<node, node> _get_insert_unique_pos(const key_type& key) {
			typedef pair<node, node> _Res;
			node x = header->parent;
			node y = header;
			bool comp = true;

			while (x != 0) {
				y = x;
				comp = _comp(key, get_key(x->value));
				x = comp ? x->left : x->right;
			}
			iterator j = iterator(y);
			if (comp) {
				if (j == begin())
					return _Res(x, y);
				else
					--j;
			}
			if (_comp(get_key(j._node->value), key))
				return _Res(x, y);
			return _Res(j._node, 0);
		}

		node leftmost() { return header->left; }

		node rightmost() { return header->right; }

		pair<node, node> _get_insert_hint_unique_pos(const_iterator pos, const key_type& key) {
      		typedef pair<node, node> _Res;

			if (pos._node == header) {
				node r = rightmost();
				if (size() > 0 && _comp(get_key(r), key))
					return _Res(0, r);
				else
					return _get_insert_unique_pos(key);
			}
			else if (_comp(key, get_key(pos._node->value)))
			{
				iterator before = pos;
				node l = leftmost();
				if (pos._node == l)
					return _Res(l, l);
				else if (_comp(get_key((--before)._node->value), key)) {
					if (before._node->right == 0)
						return _Res(0, before._node);
					else
						return _Res(pos._node, pos._node);
				}
				else
					return _get_insert_unique_pos(key);
			}
			else if (_comp(get_key(pos._node), key))
			{
				iterator after = pos;
				node r = rightmost();
				if (pos._node == r)
					return _Res(0, r);
				else if (_comp(key, get_key((++after)._node->value))) {
					if (pos._node->right == 0)
						return _Res(0, pos._node);
					else
						return _Res(after._node, after._node);
					}
				else
					return _get_insert_unique_pos(key);
			}
			else
				return _Res(pos._node, 0);
		}
	};
}