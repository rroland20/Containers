#include <iostream>
#include "test.hpp"

#ifdef STD
namespace ft = std;
# include <stack>
#else
# include "../stack.hpp"
#endif

void reportStackSize(const ft::stack<int>& s)
{
    std::cout << s.size() << " elements on stack\n";
}
 
void reportStackTop(const ft::stack<int>& s)
{
    // Leaves element on stack
    std::cout << "Top element: " << s.top() << '\n';
}

void stack_test() {
    {
		ft::stack<int> s;
		s.push(2);
		s.push(6);
		s.push(51);

		reportStackSize(s);
		reportStackTop(s);

		reportStackSize(s);
		s.pop();

		reportStackSize(s);
		reportStackTop(s);
    }
	std::cout << "--------" << std::endl;
	{
		std::cout << std::boolalpha;
	
		ft::stack<int> container;
	
		std::cout << "Initially, container.empty(): " << container.empty() << '\n';
	
		container.push(42);
		std::cout << "After adding elements, container.empty(): " << container.empty() << '\n';
	}
	std::cout << "--------" << std::endl;
	{
		ft::stack<int> container;
 
    	std::cout << "Initially, container.size(): " << container.size() << '\n';
	
		for (int i = 0; i < 7; ++i)
			container.push(i);
	
		std::cout << "After adding elements, container.size(): " << container.size() << '\n';
	}
}