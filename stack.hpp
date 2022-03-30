#pragma once

#include "vector.hpp"

namespace ft {
	template<class T, class Container = ft::vector<T> >
    class stack {
    protected:
		Container cont;
    public:
		typedef typename Container::value_type		value_type;
		typedef typename Container::reference		reference;
		typedef typename Container::const_reference	const_reference;
		typedef typename Container::size_type		size_type;
		typedef	Container							container_type;

		// Member functions //
        explicit stack(const container_type& c = container_type()) : cont(c) {}
        
        stack	&operator=(const stack& other) {
			if (this != &other) {
				while (size() > 0)
					pop();
				cont = other.cont;
			}
			return *this;
		}
        ~stack() {}

		template<typename T1, typename Container1>
		friend bool operator==(const stack<T1, Container1>&, const stack<T1, Container1>&);

		template<typename T1, typename Container1>
		friend bool operator<(const stack<T1, Container1>&, const stack<T1, Container1>&);

		// Element access //
		reference top() { return cont.back(); }
		const_reference& top() const { return cont.back(); }

		// Capacity //
		bool empty() const { return cont.empty(); }
		size_type size() const { return cont.size(); }

		// Modifiers //
		void push(const value_type& value) { cont.push_back(value); }
		void pop() { cont.pop_back(); }
    };
	// Non-member functions //
	template<class T, class Container>
	bool operator==(const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{ return lhs.cont == rhs.cont; }

	template<class T, class Container>
	bool operator!=(const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{ return !(lhs == rhs); }

	template<class T, class Container>
	bool operator<(const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{ return lhs.cont < rhs.cont; }

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

