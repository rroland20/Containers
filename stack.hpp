#pragma once

#include "vector.hpp"

namespace ft {
	template<class T, class Container = ft::vector<T> >
    class stack {
    protected:
		Container c;
    public:
		typedef typename Container::value_type		value_type;
		typedef typename Container::reference		reference;
		typedef typename Container::const_reference	const_reference;
		typedef typename Container::size_type		size_type;
		typedef	Container							container_type;

		// Member functions //
        explicit stack(const container_type& c = container_type()) : c(c) {}
        
        stack	&operator=(const stack& other) {
			if (this != &other) {
				while (size() > 0)
					pop();
				c = other.c;
			}
			return *this;
		}
        ~stack() {}

		template<typename T1, typename Container1>
		friend bool operator==(const stack<T1, Container1>&, const stack<T1, Container1>&);

		template<typename T1, typename Container1>
		friend bool operator<(const stack<T1, Container1>&, const stack<T1, Container1>&);

		// Element access //
		reference top() { return c.back(); }
		const_reference& top() const { return c.back(); }

		// Capacity //
		bool empty() const { return c.empty(); }
		size_type size() const { return c.size(); }

		// Modifiers //
		void push(const value_type& value) { c.push_back(value); }
		void pop() { c.pop_back(); }
    };
	// Non-member functions //
	template<class T, class Container>
	bool operator==(const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{ return lhs.c == rhs.c; }

	template<class T, class Container>
	bool operator!=(const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{ return !(lhs == rhs); }

	template<class T, class Container>
	bool operator<(const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{ return lhs.c < rhs.c; }

	template<class T, class Container>
	bool operator<=(const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{ return !(rhs < lhs); }

	template<class T, class Container>
	bool operator>(const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{ return (rhs < lhs); }

	template<class T, class Container>
	bool operator>=(const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{ return !(lhs < rhs); }
}
