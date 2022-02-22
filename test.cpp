#include <iostream>
#include "Vector.hpp"
#include <vector>
#include <iterator>
#include <iomanip>
#include <algorithm>

template <typename T>
void print_vector(ft::vector<T> &vec) {
	for(size_t i = 0; i != vec.size(); ++i)
		std::cout << vec[i] << " ";
	std::cout << std::endl;
}

template <typename T>
void print_vector(std::vector<T> &vec) {
	for(size_t i = 0; i != vec.size(); ++i)
		std::cout << vec[i] << " ";
	std::cout << std::endl;
}

int main() {
	{
		std::vector<int> v;
		ft::vector<int> v1;

		std::cout << v.max_size() << " " << v.empty() << std::endl;
		std::cout << v1.max_size() << " " << v1.empty() << std::endl;
	}
    std::cout << "--------" << std::endl;
	{
		ft::vector<int> myvec(2);
		std::vector<int> vec(2);
		std::cout << vec.at(1) << " " << vec.size() << " " << vec.capacity() << std::endl;
		std::cout << myvec.at(1) << " " << myvec.size() << " " << myvec.capacity()<< std::endl;

	}
    std::cout << "--------" << std::endl;
    {
        std::vector<int> vec(3, 5);
        ft::vector<int> v(3, 5);
        std::vector<int> vecs(vec.begin(), vec.end());
        ft::vector<int> ve(v.begin(), v.end()); // fix vec to v
        std::cout << vecs[1] << " " << vecs.size() << " " << vecs.capacity()  << std::endl;
        std::cout << ve[1] << " " << ve.size() << " " << ve.capacity() << std::endl;
    }
    std::cout << "--------" << std::endl;
    {
        int sz = 100;
        ft::vector<int> v;
 
        size_t cap = v.capacity();
        std::cout << "Initial size: " << v.size() << ", capacity: " << cap << '\n';
        std::cout << "\nDemonstrate the capacity's growth policy."
                 "\nSize:  Capacity:  Ratio:\n" << std::left;
        while (sz-- > 0) {
            v.push_back(sz);
            if (cap != v.capacity()) {
                std::cout << std::setw( 7) << v.size()
                        << std::setw(11) << v.capacity()
                        << std::setw(10) << v.capacity() / static_cast<float>(cap) << '\n';
                cap = v.capacity();
            }
        }
        std::cout << "\nFinal size: " << v.size() << ", capacity: " << v.capacity() << '\n';
    }
    std::cout << "--------" << std::endl;
	{
		ft::vector<int> vec;
		vec.push_back(1);
		vec.push_back(2);
		vec.push_back(3);
		std::cout << vec.front() << " " << vec.back() << std::endl;
	}
    std::cout << "--------" << std::endl;
	{
		std::vector<int> vec;
		ft::vector<int> v;
		vec.push_back(33);
		vec.push_back(45);
		v.push_back(33);
		v.push_back(45);
		vec.reserve(5);
		v.reserve(5);
		std::cout << v[3] << std::endl;
		std::cout << vec.capacity() << " " << v.capacity() << std::endl;
	}
	std::cout << "--------" << std::endl;
	{
		ft::vector<char> characters;
		characters.push_back('s');
		characters.push_back('s');
		// characters.push_back('s');
		// characters.push_back('s');
		// characters.push_back('s');
		// characters.push_back('s');
		// characters.push_back('s');
	
		characters.assign(5, 'a');
		print_vector(characters);
	
		const std::string extra(6, 'b');
		characters.assign(extra.begin(), extra.end());
		print_vector(characters);

	}
	std::cout << "--------" << std::endl;
	{
		ft::vector<int> container;
		container.push_back(1);
		container.push_back(2);
		container.push_back(3);
	
		std::cout << "Before clear:";
		std::cout << "\nSize=" << container.size() << ", Capacity=" << container.capacity() << '\n';
	
		std::cout << "Clear\n";
		container.clear();
	
		std::cout << "After clear:";
		std::cout << "\nSize=" << container.size() << ", Capacity=" << container.capacity() << '\n';
	}
	std::cout << "--------" << std::endl;
	{
		ft::vector<char> vec;
		vec.push_back('a');
		vec.push_back('b');
		vec.push_back('c');

		std::cout << "Before pop_back:\n";
		print_vector(vec);

		vec.pop_back();
		vec.pop_back();
		std::cout << "After pop_back:\n";
		print_vector(vec);

	}
	std::cout << "--------" << std::endl;
	{
		std::vector<int> vec(5, 7);

		vec.resize(8, 5);
		print_vector(vec);
	}
	std::cout << "--------" << std::endl;
	{
		ft::vector<int> vec1(2, 100);
		ft::vector<int> vec2(4, 500);
	}
	std::cout << "--------" << std::endl;
	{
		std::vector<int> c1(3, 100);
		ft::vector<int> vec(3, 100);
		std::cout << "std::vector - ";
		print_vector(c1);
		std::cout << "ft::vector - ";
		print_vector(vec);
		std::cout << "-\n";
	
		std::vector<int>::iterator it = c1.begin(); //1
		ft::vector<int>::iterator it2 = vec.begin();
		it = c1.insert(it, 200);
		it2 = vec.insert(it2, 200);
		std::cout << "std::vector - ";
		print_vector(c1);
		std::cout << "ft::vector  - ";
		print_vector(vec);
		std::cout << "-\n";
	
		// std::cout << c1.capacity() << " - " << vec.capacity() << " " << vec.size() << std::endl;
		c1.insert(it, 2, 300); //2
		vec.insert(it2, 2, 300);
		std::cout << "std::vector - ";
		print_vector(c1);
		std::cout << "ft::vector  - ";
		print_vector(vec);
		std::cout << "-\n";

		// it = c1.begin();
		// it2 = vec.begin();
	
		// std::vector<int> c2(2, 400); //3
		// ft::vector<int> vec2(2, 400);
		// c1.insert(it, c2.begin(), c2.end());
		// vec.insert(it2, vec2.begin(), vec2.end());
		// std::cout << "std::vector - ";
		// print_vector(c1);
		// std::cout << "ft::vector  - ";
		// print_vector(vec);
		// std::cout << "-\n";
	}
	// std::cout << "--------" << std::endl;
	// {
	// 	ft::vector<int> vec;
	// 	vec.push_back(1);
	// 	vec.push_back(4);
	// 	vec.push_back(7);

	// 	std::cout << *(vec.rbegin()) << std::endl;
	// }
}