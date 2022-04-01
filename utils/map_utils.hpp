#pragma once

namespace ft {
	template<typename Arg1, typename Arg2, typename Result>
	struct binary_function {
		typedef Arg1 	first_argument_type;
		typedef Arg2 	second_argument_type;
		typedef Result 	result_type;
	};

	template<typename Pair>
    struct Select1st {
      typename Pair::first_type& operator()(Pair& x) const
      { return x.first; }

      const typename Pair::first_type& operator()(const Pair& x) const
      { return x.first; }
	};

	enum Rb_tree_color { red, black, };

	template<typename Val>
    struct Rb_tree_node {
		typedef Rb_tree_node* 		Base_ptr;

		bool			color;
		Base_ptr		parent;
		Base_ptr		left;
		Base_ptr		right;
		Val				value;
	};

	template<typename T>
	void swap(T& x, T& y) {
		T z = x;
		x = y;
		y = z;
	}

	// Only set //
	template<typename T>
    struct Identity {
		T& operator()(T& x) const { return x; }

		const T& operator()(const T& x) const { return x; }
	};
}
