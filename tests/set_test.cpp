#include <iostream>
#include <string>
#include "test.hpp"

#ifdef STD
namespace ft = std;
# include <set>
#else
# include "../set.hpp"
#endif

template <typename Key>
void print_set(ft::set<Key>& set) {
	std::cout << "\t\tSet:\t\t\t{";
	typename ft::set<Key>::iterator beg = set.begin();
	typename ft::set<Key>::iterator end = set.end();
	typename ft::set<Key>::iterator it = beg;

	for (; it != end; ++it) {
		if (it != beg)
			std::cout << ", ";
		std::cout << *it;
	}
	std::cout << "}\n";
}

template <typename Key>
void print_param(ft::set<Key>& set) {
	std::cout << std::boolalpha;
	std::cout << "\t\tSet empty:\t\t" << set.empty() << std::endl;
	std::cout << "\t\tSet size:\t\t" << set.size() << std::endl;
	std::cout << "\t\tMax size:\t\t" << set.max_size() << std::endl;
	print_set(set);
}

template <typename Iterator>
void	printContent(Iterator first, Iterator last)
{
	Iterator	it = first;
	std::cout << "\t\tSet:\t\t\t{";
	for (; it != last; ++it)
	{
		if (it != first)
			std::cout << ", ";
		std::cout << *it;
	}
	std::cout << "}\n";
}

void	set_test() {
	std::cout << "\n<<<< SET >>>>\n\n";

	int	arr[] = { 1, 2, 3, 4, 5, 6 };
	{
		std::cout << "Constructors:\n";
		std::cout << "  Defaul constructor:\n";
		ft::set<int> set;
		print_param(set);

		std::cout << "  Fill constructor:\n";
		ft::set<int> set1(arr, arr + 6);
		print_param(set1);

		std::cout << "  Copy constructor:\n";
		ft::set<int> set2(arr, arr + 6);
		ft::set<int> set3(set2);
		std::cout << "\tset1:\n";
		print_param(set2);
		std::cout << "\n\tset2(set1):\n";
		print_param(set3);
	}
	std::cout << "--------" << std::endl;
	{
		std::cout << "Operator = :\n";
		ft::set<int> set1(arr, arr + 6);
		ft::set<int> set2;
		set2 = set1;
		std::cout << "\tset1:\n";
		print_param(set1);
		std::cout << "\n\tset2 = set1:\n";
		print_param(set2);
	}
	std::cout << "--------" << std::endl;
	{
		std::cout << "Iterators:\n";
		std::cout << "\tValues from Begin to End:\n";
		ft::set<int> set(arr, arr + 6);
		printContent(set.begin(), set.end());

		std::cout << "\tValues from const Begin to const End:\n";
		const ft::set<int> set1(arr, arr + 6);
		printContent(set1.begin(), set1.end());

		std::cout << "\tValues from RBegin to REnd:\n";
		ft::set<int> set2(arr, arr + 6);
		printContent(set2.rbegin(), set2.rend());

		std::cout << "\tValues from const RBegin to const REnd:\n";
		const ft::set<int> set3(arr, arr + 6);
		printContent(set3.rbegin(), set3.rend());
	}
	std::cout << "--------" << std::endl;
	{
		std::cout << "Insert single element:\n";
		int arr[] = { 1, 3, 4, 5, 6 };
		ft::set<int> set(arr, arr + 5);
		print_param(set);
		set.insert(2);
		std::cout << "\n\tset.insert(2):\n";
		print_param(set);
	}
	std::cout << "--------" << std::endl;
	{
		std::cout << "Insert with hint:\n";
		int arr[] = { 1, 3, 4, 5, 6 };
		ft::set<int> set(arr, arr + 5);
		print_param(set);
		set.insert(set.begin(), 2);
		std::cout << "\n\tset.insert(set.begin(), 2):\n";
		print_param(set);
	}
	std::cout << "--------" << std::endl;
	{
		std::cout << "Insert range:\n";
		int arr[] = { 1, 2, 3, 5, 6 };
		int arr2[] = { 4, 7, 8 };
		ft::set<int> set(arr, arr + 5);
		print_param(set);
		set.insert(arr2, arr2 + 3);
		std::cout << "\n\tset.insert(arr2, arr2 + 3):\n";
		print_param(set);
	}
	std::cout << "--------" << std::endl;
	{
		std::cout << "Erase single element:\n";
		ft::set<int> set(arr, arr + 6);
		print_param(set);
		ft::set<int>::iterator it = set.begin();
		++it;
		++it;
		++it;
		set.erase(it);
		std::cout << "\n\tset.erase(it(it + 3)):\n";
		print_param(set);
	}
	std::cout << "--------" << std::endl;
	{
		std::cout << "Erase key:\n";
		ft::set<int> set(arr, arr + 6);
		print_param(set);
		set.erase(4);
		std::cout << "\n\tset.erase(4):\n";
		print_param(set);
	}
	std::cout << "--------" << std::endl;
	{
		std::cout << "Erase range:\n";
		ft::set<int> set(arr, arr + 6);
		print_param(set);
		ft::set<int>::iterator it = set.begin();
		ft::set<int>::iterator it2 = set.begin();
		++it;
		++it2;
		++it2;
		++it2;
		set.erase(it, it2);
		std::cout << "\n\tset.erase(it, it2):\n";
		print_param(set);
	}
	std::cout << "--------" << std::endl;
	{
		std::cout << "Swap:\n";
		int arr[] = { 2, 3, 6, 7 };
		int arr2[] = { 1, 4, 5, 8 };
		ft::set<int> set(arr, arr + 4);
		ft::set<int> set2(arr2, arr2 + 4);
		std::cout << "\tset1:\n";
		print_param(set);
		std::cout << "\tset2:\n";
		print_param(set2);
		set.swap(set2);

		std::cout << "\n  set1.swap(set2):\n";
		std::cout << "\tset1:\n";
		print_param(set);
		std::cout << "\tset2:\n";
		print_param(set2);
	}
	std::cout << "--------" << std::endl;
	{
		std::cout << "Clear:\n";
		ft::set<int> set(arr, arr + 6);
		print_param(set);

		set.clear();
		std::cout << "\n\tset.clear():\n";
		print_param(set);
	}
	std::cout << "--------" << std::endl;
	{
		std::cout << "Key Comp (true):\n";
		ft::set<int> set;
		std::cout << "\tcmp(1, 2):\t\t" << set.key_comp()(1, 2) << std::endl;

		std::cout << "\nKey Comp (false):\n";
		std::cout << "\tcmp(2, 1):\t\t" << set.key_comp()(2, 1) << std::endl;
	}
	std::cout << "--------" << std::endl;
	{
		std::cout << "Value Comp (true):\n";
		ft::set<int> set;
		std::cout << "\tcmp(1, 2):\t\t" << set.value_comp()(1, 2) << std::endl;

		std::cout << "\nValue Comp (false):\n";
		std::cout << "\tcmp(2, 1):\t\t" << set.value_comp()(2, 1) << std::endl;
	}
	std::cout << "--------" << std::endl;
	{
		std::cout << "Find:\n";
		ft::set<int> set(arr, arr + 6);
		print_param(set);
		ft::set<int>::iterator it = set.find(2);
		std::cout << "\n\tset.find(2):\n";
		printContent(it, ++it);

		ft::set<int>::iterator it1 = set.find(9);
		std::cout << "\n\tset.find(9):\n";
		if (it1 != set.end())
			printContent(it1, ++it1);
	}
	std::cout << "--------" << std::endl;
	{
		std::cout << "Count:\n";
		ft::set<int> set(arr, arr + 6);
		print_param(set);

		std::cout << "\n\t\tcount(2):\t\t" << set.count(2) << std::endl;

		std::cout << "\n\t\tcount(9):\t\t" << set.count(9) << std::endl;
	}
	std::cout << "--------" << std::endl;
	{
		std::cout << "Lower bound:\n";
		ft::set<int> set(arr, arr + 6);
		print_param(set);
		ft::set<int>::iterator it = set.lower_bound(3);
		std::cout << "\n\tset.lower_bound(3):\n";
		printContent(it, ++it);

		ft::set<int>::iterator it2 = set.lower_bound(8);
		std::cout << "\n\tset.lower_bound(8):\n";
		if (it2 != set.end())
			printContent(it2, ++it2);
	}
	std::cout << "--------" << std::endl;
	{
		std::cout << "Upper bound:\n";
		ft::set<int> set(arr, arr + 6);
		print_param(set);
		ft::set<int>::iterator it = set.upper_bound(3);
		std::cout << "\n\tset.upper_bound(3):\n";
		printContent(it, ++it);

		ft::set<int>::iterator it2 = set.upper_bound(9);
		std::cout << "\n\tset.upper_bound(9):\n";
		if (it2 != set.end())
			printContent(it2, ++it2);
	}
	std::cout << "--------" << std::endl;
	{
		std::cout << "Equal range:\n";
		ft::set<int> set(arr, arr + 6);
		print_param(set);
		typedef ft::set<int>::iterator iter;
		ft::pair<iter, iter> it = set.equal_range(3);
		std::cout << "\n\tset.equal_range(3):\n";
		printContent(it.first, it.second);

		typedef ft::set<int>::iterator iter1;
		ft::pair<iter1, iter1> it1 = set.equal_range(9);
		std::cout << "\n\tset.equal_range(9):\n";
		printContent(it1.first, it1.second);
	}
	std::cout << "--------" << std::endl;
	{
		std::cout << "Operator == (true):\n";
		ft::set<int> set(arr, arr + 6);
		std::cout << "\t set == set:\t\t" << (set == set) << std::endl;

		std::cout << "Operator == (false):\n";
		int arr2[] = { 4, 7, 8 };
		ft::set<int> set2(arr2, arr2 + 3);
		std::cout << "\tset1 == set2:\t" << (set == set2) << std::endl;
	}
	std::cout << "--------" << std::endl;
	{
		std::cout << "Operator != (false):\n";
		ft::set<int> set(arr, arr + 6);
		std::cout << "\t set != set:\t\t" << (set != set) << std::endl;

		std::cout << "Operator != (true):\n";
		int arr2[] = { 4, 7, 8 };
		ft::set<int> set2(arr2, arr2 + 3);
		std::cout << "\tset1 != set2:\t" << (set != set2) << std::endl;
	}
	std::cout << "--------" << std::endl;
	{
		std::cout << "Operator < (false):\n";
		ft::set<int> set(arr, arr + 6);
		std::cout << "\t set < set:\t\t" << (set < set) << std::endl;

		std::cout << "Operator < (true):\n";
		int arr2[] = { 4, 7, 8 };
		ft::set<int> set2(arr2, arr2 + 3);
		std::cout << "\tset1 < set2:\t" << (set < set2) << std::endl;
	}
	std::cout << "--------" << std::endl;
	{
		std::cout << "Operator <= (false):\n";
		int arr2[] = { 4, 7, 8 };
		ft::set<int> set(arr, arr + 5);
		ft::set<int> set2(arr2, arr2 + 3);
		std::cout << "\tset2 <= set1:\t" << (set2 <= set) << std::endl;

		std::cout << "Operator <= (true):\n";
		std::cout << "\tset1 <= set2:\t" << (set <= set2) << std::endl;
	}
	std::cout << "--------" << std::endl;
	{
		std::cout << "Operator > (true):\n";
		int			arr2[] = { 4, 7, 8 };
		ft::set<int>	set(arr, arr + 5);
		ft::set<int>	set2(arr2, arr2 + 3);
		std::cout << "\tset2 > set1:\t" << (set2 > set) << std::endl;

		std::cout << "Operator > (false):\n";
		std::cout << "\tset1 > set2:\t" << (set > set2) << std::endl;
	}
	std::cout << "--------" << std::endl;
	{
		std::cout << "Operator >= (true):\n";
		int			arr2[] = { 4, 7, 8 };
		ft::set<int>	set(arr, arr + 5);
		ft::set<int>	set2(arr2, arr2 + 3);
		std::cout << "\tset2 >= set1:\t" << (set2 >= set) << std::endl;

		std::cout << "Operator >= (false):\n";
		std::cout << "\tset1 >= set2:\t" << (set >= set2) << std::endl;
	}
	std::cout << "--------" << std::endl;
	{
		std::cout << "Swap:\n";
		int			arr2[] = { 4, 7, 8 };
		ft::set<int>	set(arr, arr + 6);
		ft::set<int>	set2(arr2, arr2 + 3);
		std::cout << "\tset1:\n";
		printContent(set.begin(), set.end());
		std::cout << "\tset2:\n";
		printContent(set2.begin(), set2.end());
		ft::swap(set, set2);
		std::cout << "\n  ft::swap(set1, set2):\n";
		std::cout << "\tset1:\n";
		printContent(set.begin(), set.end());
		std::cout << "\tset2:\n";
		printContent(set2.begin(), set2.end());
	}
}