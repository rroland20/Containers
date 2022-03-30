#include <iostream>
#include <string>
#include <iomanip>
#include "test.hpp"

#ifdef STD
namespace ft = std;
# include <vector>
#else
# include "../vector.hpp"
#endif

template <typename T>
void print_vector(ft::vector<T> &vec) {
	std::cout << "\tVector:\t\t\t";
	for(size_t i = 0; i != vec.size(); ++i)
		std::cout << vec[i] << " ";
	std::cout << std::endl;
}

template <typename T>
void print_param(ft::vector<T> &vec) {
	std::cout << std::boolalpha;
	std::cout << "\tVector empty:\t" << vec.empty() << std::endl;
	std::cout << "\tVector size:\t" << vec.size() << std::endl;
	std::cout << "\tCapacity:\t\t" << vec.capacity() << std::endl;
	std::cout << "\tMax size:\t\t" << vec.max_size() << std::endl;
	print_vector(vec);
}

void vector_test() {
	std::cout << "\n<<<< VECTOR >>>>\n\n";
	{
		std::cout << "Constuctor:\n";
		ft::vector<int> v1;
		ft::vector<int> v2(10);

		std::cout << "  Default:\n";
		print_param(v1);
		std::cout << "  Fill:\n";
		print_param(v2);
	}
    std::cout << "--------" << std::endl;
    {
		std::cout << "Constuctor iterator:\n";
        ft::vector<int> v(3, 5);
        ft::vector<std::string> v1(5, "aboba");
        ft::vector<int> ve(v.begin(), v.end());
        ft::vector<std::string> ve2(v1.begin(), v1.end());
		std::cout << "  Int:\n";
        print_param(ve);
		std::cout << "  String:\n";
        print_param(ve2);
    }
    std::cout << "--------" << std::endl;
    {
		std::cout << "Size and capacity:\n";
        int sz = 100;
        ft::vector<int> v;
 
        size_t cap = v.capacity();
        std::cout << "Initial size: " << v.size() << ", capacity: " << cap << '\n';
        std::cout << "\nDemonstrate the capacity's growth policy."
                 "\nSize:  Capacity:\n" << std::left;
        while (sz-- > 0) {
            v.push_back(sz);
            if (cap != v.capacity()) {
                std::cout << std::setw( 7) << v.size()
                        << std::setw(11) << v.capacity() << '\n';
                cap = v.capacity();
            }
        }
        std::cout << "\nFinal size: " << v.size() << ", capacity: " << v.capacity() << '\n';
		print_vector(v);
    }
    std::cout << "--------" << std::endl;
	{
		std::cout << "Front and back:\n";
		ft::vector<int> vec;
		vec.push_back(1);
		vec.push_back(2);
		vec.push_back(3);

		print_param(vec);
		std::cout << "\tFront:\t" << vec.front() << std::endl;
		std::cout << "\tBack:\t" << vec.back() << std::endl;
	}
    std::cout << "--------" << std::endl;
	{
		std::cout << "Data:\n";
		ft::vector<int> vec;
		vec.push_back(1);
		vec.push_back(2);
		vec.push_back(3);

		print_param(vec);
		std::cout << "\tData:\t\t\t";
		for (size_t i = 0; i != vec.size(); ++i)
			std::cout << vec.data()[i] << " ";
		std::cout << std::endl;
	}
    std::cout << "--------" << std::endl;
	{
		std::cout << "At:\n";
		ft::vector<int> v;

		v.push_back(1);
		v.push_back(2);
		v.push_back(3);
		print_param(v);
		try {
			std::cout << "\tvec.at(2) - " << v.at(2) << std::endl;	
			std::cout << "\tvec.at(5) - " << v.at(5) << std::endl;	
		}
		catch(const std::exception& e) {
			std::cout << e.what() << '\n';
		}
		
	}
    std::cout << "--------" << std::endl;
	{
		std::cout << "Operator[]:\n";
		ft::vector<char> v;
		v.push_back('a');
		v.push_back('b');
		v.push_back('c');

		print_param(v);
		std::cout << "\tvec[1] - " << v[1] << std::endl;
	}
    std::cout << "--------" << std::endl;
	{
		std::cout << "Reserve:\n";
		ft::vector<int> v;
		v.push_back(33);
		v.push_back(45);
		std::cout << "  Before reserve(capacity): " << v.capacity() << std::endl;
		v.reserve(5);
		std::cout << "  After reserve:\n";
		print_param(v);
		std::cout << "\tvec[3] - " << v[3] << std::endl;
		try {
			std::cout << "\tTry reserve > max size: ";
			v.reserve(2305843009213693957);
		}
		catch(const std::exception& e) {
			std::cout << e.what() << '\n';
		}
	}
	std::cout << "--------" << std::endl;
	{
		std::cout << "Assign:\n";
		ft::vector<char> characters(2, 's');
		std::cout << "  Before assign:\n";
		print_param(characters);
	
		characters.assign(5, 'a');
		std::cout << "  After assign(5, 'a'):\n";
		print_param(characters);
	
		const std::string extra(6, 'b');
		characters.assign(extra.begin(), extra.end());
		std::cout << "  After iterator assign(6, 'b'):\n";
		print_param(characters);
	}
	std::cout << "--------" << std::endl;
	{
		std::cout << "Clear:\n";
		ft::vector<int> container;
		container.push_back(1);
		container.push_back(2);
		container.push_back(3);
	
		std::cout << "  Before clear:\n";
		print_param(container);

		container.clear();
	
		std::cout << "  After clear:\n";
		print_param(container);
	}
	std::cout << "--------" << std::endl;
	{
		std::cout << "Push and pop:\n";
		ft::vector<char> vec;
		std::cout << "  Before push_back:\n";
		print_param(vec);
		vec.push_back('a');
		vec.push_back('b');
		vec.push_back('c');
		std::cout << "  After push_back:\n";
		print_param(vec);

		vec.pop_back();
		vec.pop_back();
		std::cout << "  After pop_back:\n";
		print_param(vec);

	}
	std::cout << "--------" << std::endl;
	{
		std::cout << "Resize:\n";
		ft::vector<int> c;
		c.push_back(1);
		c.push_back(2);
		c.push_back(3);
		std::cout << "  The vector holds:\n";
		print_param(c);

		c.resize(5);
		std::cout << "  After resize up to 5:\n";
		print_param(c);
		
		c.resize(2);
		std::cout << "  After resize down to 2:\n";
		print_param(c);
		
		c.resize(6, 4);
		std::cout << "  After resize up to 6 (initializer = 4):\n";
		print_param(c);
	}
	std::cout << "--------" << std::endl;
	{
		std::cout << "Insert:\n";
		ft::vector<int> vec(3, 100);
		std::cout << "  Create vec(3, 100)\n";
		print_param(vec);
	
		ft::vector<int>::iterator it2 = vec.begin();
		it2 = vec.insert(it2, 200);
		std::cout << "\n  vec.insert(iter, 200):\n";
		print_param(vec);
	
		vec.insert(it2, 4, 300);
		std::cout << "\n  vec.insert(it2, 4, 300):\n";
		print_param(vec);

		it2 = vec.begin();
	
		ft::vector<int> vec2(2, 400);
		vec.insert(it2, vec2.begin(), vec2.end());
		std::cout << "\n  vec.insert(it2, vec2.begin(), vec2.end()):\n";
		print_param(vec);
	}
	std::cout << "--------" << std::endl;
	{
		std::cout << "Iterator:\n";
		ft::vector<int> vec;
		vec.push_back(1);
		vec.push_back(4);
		vec.push_back(7);

		print_param(vec);
		std::cout << "\tvec.begin():\t" << *(vec.begin()) << std::endl;
		std::cout << "\tvec.end() - 1:\t" << *(vec.end() - 1) << std::endl;
		std::cout << "\tvec.end():\t\t" << *(vec.end()) << std::endl;
	}
	std::cout << "--------" << std::endl;
	{
		std::cout << "Reverse iterator:\n";
		ft::vector<int> vec;
		vec.push_back(1);
		vec.push_back(4);
		vec.push_back(7);

		print_param(vec);
		std::cout << "\tvec.rbegin():\t" << *(vec.rbegin()) << std::endl;
		std::cout << "\tvec.rend() - 1:\t" << *(vec.rend() - 1) << std::endl;
		std::cout << "\tvec.rend():\t\t" << *(vec.rend()) << std::endl;
	}
	std::cout << "--------" << std::endl;
	{
		std::cout << "Erase:\n";
		ft::vector<int> c;
		c.push_back(1);
		c.push_back(2);
		c.push_back(3);
		c.push_back(4);
		c.push_back(5);
		c.push_back(6);
		c.push_back(7);
		c.push_back(8);
		std::cout << "  Create vector:\n";
		print_param(c);
	
		c.erase(c.begin());
		std::cout << "  erase(c.begin()):\n";
		print_param(c);
	
		c.erase(c.begin()+2, c.begin()+5);
		std::cout << "  erase(c.begin()+2, c.begin()+5):\n";
		print_param(c);
	}
	std::cout << "--------" << std::endl;
	{
		std::cout << "Swap:\n";
		ft::vector<int> v1(2, 5);
		ft::vector<int> v2(4, 8);
		std::cout << "  Before swap:\n";
		print_vector(v1);
		print_vector(v2);
		
		v1.swap(v2);
		std::cout << "  After swap:\n";
		print_vector(v1);
		print_vector(v2);
	}
	std::cout << "--------" << std::endl;
	{
		std::cout << "Operators:\n";
		ft::vector<int> v1(2, 5);
		ft::vector<int> v2(4, 8);
		print_vector(v1);
		print_vector(v2);
		std::cout << "\tvec1 == vec2:\t" << (v1 == v2) << std::endl;
		std::cout << "\tvec1 != vec2:\t" << (v1 != v2) << std::endl;
		std::cout << "\tvec1 < vec2:\t" << (v1 < v2) << std::endl;
		std::cout << "\tvec1 <= vec2:\t" << (v1 <= v2) << std::endl;
		std::cout << "\tvec1 > vec2:\t" << (v1 > v2) << std::endl;
		std::cout << "\tvec1 >= vec2:\t" << (v1 >= v2) << std::endl;
	}
}