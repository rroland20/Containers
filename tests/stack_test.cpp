#include <iostream>
#include "test.hpp"

#ifdef STD
namespace ft = std;
# include <stack>
#else
# include "../stack.hpp"
#endif

template <typename T>
void print_top(const ft::stack<T> &s) {
	std::cout << "\tStack top:\t\t" << s.top() << std::endl;
}

template <typename T>
void print_stack(ft::stack<T> s) {
	std::cout << "\tStack:\t\t\t";
	for (; !s.empty();) {
		std::cout << s.top() << " ";
		if (!s.empty())
			s.pop();
	}
	std::cout << std::endl;
}

template <typename T>
void print_param(ft::stack<T> s) {
	std::cout << std::boolalpha;
	std::cout << "\tStack empty:\t" << s.empty() << std::endl;
	std::cout << "\tStack size:\t\t" << s.size() << std::endl;
	print_stack(s);
}

void stack_test() {
	std::cout << "\n<<<< STACK >>>>\n\n";
	{
		std::cout << "Constructor:\n";
		std::cout << "  Default constructor:\n";
		ft::stack<char> s;
		print_param(s);

		std::cout << "  Fill stack:\n";
		s.push('a');
		s.push('b');
		s.push('c');
		print_top(s);
		print_param(s);
	}
	std::cout << "--------" << std::endl;
    {
		std::cout << "Push:\n";
		ft::stack<int> s;
		std::cout << "  Before push:\n";
		print_param(s);
		
		s.push(2);
		s.push(6);
		s.push(51);
		std::cout << "  After push:\n";
		print_top(s);
		print_param(s);

    }
	std::cout << "--------" << std::endl;
	{
		std::cout << "Pop:\n";
		ft::stack<int> s;
		s.push(10);
		s.push(4);
		s.push(8);
		std::cout << "  Before pop:\n";
		print_top(s);
		print_param(s);

		s.pop();
		s.pop();
		std::cout << "  After pop:\n";
		print_top(s);
		print_param(s);
	}
	std::cout << "--------" << std::endl;
	{
		std::cout << "Operators:\n";
	
		ft::stack<int> s;
		ft::stack<int> s1;

		s.push(1);
		s.push(2);
		s.push(3);
		s.push(4);
		s1.push(10);
		s1.push(13);
		s1.push(15);
		std::cout << "  Stack s1:\n";
		print_stack(s);
		std::cout << "  Stack s2:\n";
		print_stack(s1);

		std::cout << "\n\ts1 == s2:\t\t" << (s == s1) << std::endl;
		std::cout << "\ts1 != s2:\t\t" << (s != s1) << std::endl;
		std::cout << "\ts1 < s2:\t\t" << (s < s1) << std::endl;
		std::cout << "\ts1 <= s2:\t\t" << (s <= s1) << std::endl;
		std::cout << "\ts1 > s2:\t\t" << (s > s1) << std::endl;
		std::cout << "\ts1 >= s2:\t\t" << (s >= s1) << std::endl;
	}
}