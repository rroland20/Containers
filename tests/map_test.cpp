#include <iostream>
#include <string>
#include "test.hpp"

#ifdef STD
namespace ft = std;
# include <map>
#else
# include "../map.hpp"
#endif

template <typename Key, typename Val>
void print_map(ft::map<Key, Val>& map) {
	std::cout << "\t\tMap:\t\t\t\t{[";
	typename ft::map<Key, Val>::iterator beg = map.begin();
	typename ft::map<Key, Val>::iterator end = map.end();
	typename ft::map<Key, Val>::iterator it = beg;

	for (; it != end; ++it) {
		if (it != beg)
			std::cout << "] [";
		std::cout << (*it).first << ", " << (*it).second;
	}
	std::cout << "]}\n";
}

template <typename Key, typename Val>
void print_param(ft::map<Key, Val>& map) {
	std::cout << std::boolalpha;
	std::cout << "\t\tMap empty:\t" << map.empty() << std::endl;
	std::cout << "\t\tMap size:\t\t" << map.size() << std::endl;
	std::cout << "\t\tMax size:\t\t" << map.max_size() << std::endl;
	print_map(map);
}

template <typename Key, typename Val>
void print_param(const ft::map<Key, Val>& map) {
	std::cout << std::boolalpha;
	std::cout << "\t\tMap empty:\t" << map.empty() << std::endl;
	std::cout << "\t\tMap size:\t\t" << map.size() << std::endl;
	std::cout << "\t\tMax size:\t\t" << map.max_size() << std::endl;
	typename ft::map<Key, Val>::const_iterator	beg = map.begin();
	typename ft::map<Key, Val>::const_iterator	end = map.end();
	typename ft::map<Key, Val>::const_iterator	it = beg;
	std::cout << "\t\tMap:\t\t\t\t{[";
	for (; it != end; ++it) {
		if (it != beg)
			std::cout << "] [";
		std::cout << (*it).first << ", " << (*it).second;
	}
	std::cout << "]}\n";
}

template <typename Iterator>
void	printContent(Iterator first, Iterator last)
{
	Iterator	it = first;
	std::cout << "\t\tMap:\t\t\t\t{[";
	for (; it != last; ++it)
	{
		if (it != first)
			std::cout << "] [";
		std::cout << (*it).first << ", " << (*it).second;
	}
	std::cout << "]}\n";
}

typedef ft::pair<int, std::string> ispair;

void map_test() {
	std::cout << "\n<<<< MAP >>>>\n\n";

	int			iarr[] = { 1, 2, 3, 4, 5, 6, 7 };
	std::string	sarr[] = { "One", "Two", "Three", "Four", "Five", "Six", "Seven" };
	ispair		parr[7];
	for (size_t i = 0; i < 7; i++)
		parr[i] = ft::make_pair(iarr[i], sarr[i]);
	
	{
    	std::cout << "Constructors:\n";
		std::cout << "  Default constructor:\n";
		ft::map<int, std::string>	map;
		print_param(map);

		std::cout << "  Fill constructor:\n";
		ft::map<int, std::string>	m(parr, parr + 7);
		print_param(m);
	}
	std::cout << "--------" << std::endl;
	{
		std::cout << "Copy constructor:\n";
		ft::map<int, std::string>	map(parr, parr + 7);
		ft::map<int, std::string>	map2(map);
		std::cout << "  map1:\n";
		print_param(map);
		std::cout << "\n  map2:\n";
		print_param(map2);
	}
	std::cout << "--------" << std::endl;
	{
		std::cout << "Operator=:\n";
		ft::map<int, std::string>	map(parr, parr + 7);
		ft::map<int, std::string>	map2;
		map2 = map;
		std::cout << "  map1:\n";
		print_param(map);
		std::cout << "\n  map2:\n";
		print_param(map2);
	}
	std::cout << "--------" << std::endl;
	{
		std::cout << "Iterators:\n";
		std::cout << "  Values from Begin to End:\n";
		ft::map<int, std::string>	map(parr, parr + 7);
		printContent(map.begin(), map.end());

		std::cout << "  Values from const Begin to const End:\n";
		const ft::map<int, std::string>	m(parr, parr + 7);
		printContent(m.begin(), m.end());

		std::cout << "  Values from RBegin to REnd:\n";
		ft::map<int, std::string>	m2(parr, parr + 7);
		printContent(m2.rbegin(), m2.rend());

		std::cout << "  Values from const RBegin to const REnd:\n";
		const ft::map<int, std::string>	m3(parr, parr + 7);
		printContent(m3.rbegin(), m3.rend());
	}
	std::cout << "--------" << std::endl;
	{
		std::cout << "Element access:\n";
		std::cout << "  Operator[]:\n";
		ft::map<int, std::string>	map(parr, parr + 7);
		print_param(map);
		std::cout << "\n  map[4] = :)\n";
		map[4] = ":)";
		std::cout << "\n";
		print_param(map);

		std::cout << "\n  map[8] = :):\n";
		map[8] = ":)";
		print_param(map);
	}
	std::cout << "--------" << std::endl;
	{
		std::cout << "At:\n";
		ft::map<int, std::string>	map(parr, parr + 7);
		print_param(map);
		std::cout << "\n  map.at(3) = :)\n";
		map.at(3) = ":)";
		print_param(map);

		try {
			std::cout << "\n  map.at(8) = :)\n";
			map.at(8) = ":)";
		}
		catch(const std::exception& e) {
			std::cout << "  Exception:\t" << e.what() << '\n';
		}
		print_param(map);
	}
	std::cout << "--------" << std::endl;
	{
		std::cout << "Const At:\n";
		const ft::map<int, std::string>	map(parr, parr + 7);
		print_param(map);
		map.at(6);
		std::cout << "\n  map.at(6):\n";
		print_param(map);

		try {
			std::cout << "\n  map.at(9):\n";
			map.at(9);
		}
		catch(const std::exception& e) {
			std::cout << "  Excetion:\t" << e.what() << '\n';
		}
		print_param(map);
	}
	std::cout << "--------" << std::endl;
	{
		std::cout << "Insert single element:\n";
		ft::map<int, std::string>	map(parr, parr + 7);
		print_param(map);
		map.insert(ft::make_pair(8, "Eight"));
		std::cout << "\n  map.insert(8, Eight):\n";
		print_param(map);

		std::cout << "\nInsert with hint:\n";
		int			iarr[] = { 1, 2, 3, 5, 6 };
		std::string	sarr[] = { "One", "Two", "Three", "Five", "Six" };
		ispair		parr[5];
		for (size_t i = 0; i < 5; i++)
			parr[i] = ft::make_pair(iarr[i], sarr[i]);
		ft::map<int, std::string>	m(parr, parr + 5);
		print_param(m);
		m.insert(m.begin(), ft::make_pair(4, "Four"));
		std::cout << "\n  map.insert(map.begin(), (4, Four)):\n";
		print_param(m);

		std::cout << "\nInsert range:\n";
		int			iarr2[] = { 4, 7, 8 };
		std::string	sarr2[] = { "Four", "Seven", "Eight" };
		ispair		parr2[3];
		for (size_t i = 0; i < 3; i++)
			parr2[i] = ft::make_pair(iarr2[i], sarr2[i]);
		ft::map<int, std::string>	m2(parr, parr + 5);
		print_param(m2);
		m2.insert(parr2, parr2 + 3);
		std::cout << "\n  map.insert(parr, parr + 3):\n";
		print_param(m2);
	}
	std::cout << "--------" << std::endl;
	{
		std::cout << "Erase single element:\n";
		ft::map<int, std::string>	map(parr, parr + 7);
		print_param(map);
		ft::map<int, std::string>::iterator	it = map.begin();
		++it;
		++it;
		++it;
		map.erase(it);
		std::cout << "\n  map.erase(it(begin + 3)):\n";
		print_param(map);

		std::cout << "\nErase key:\n";
		map.erase(6);
		std::cout << "  map.erase(6):\n";
		print_param(map);

		std::cout << "\nErase range:\n";
		ft::map<int, std::string>::iterator	it2 = map.begin();
		ft::map<int, std::string>::iterator	it3 = map.begin();
		++it3;
		++it3;
		++it3;
		map.erase(it2, it3);
		std::cout << "  map.erase(it, it2(begin + 3)):\n";
		print_param(map);
	}
	std::cout << "--------" << std::endl;
	{
		std::cout << "Swap:\n";
		int			iarr2[] = { 3, 1, 5 };
		std::string	sarr2[] = { "Tree", "One", "Five" };
		ispair		parr2[3];
		for (size_t i = 0; i < 3; i++)
			parr2[i] = ft::make_pair(iarr2[i], sarr2[i]);
		ft::map<int, std::string>	map(parr, parr + 7);
		ft::map<int, std::string>	map2(parr2, parr2 + 3);
		std::cout << "  map1:\n";
		print_map(map);
		std::cout << "  map2:\n";
		print_map(map2);

		map.swap(map2);
		std::cout << "\n map1.swap(map2):\n  map1:\n";
		print_map(map);
		std::cout << "  map2:\n";
		print_map(map2);
	}
	std::cout << "--------" << std::endl;
	{
		std::cout << "Clear:\n";
		ft::map<int, std::string>	map(parr, parr + 7);
		print_param(map);
		map.clear();
		std::cout << "\n  map.clear():\n";
		print_param(map);
	}	
	std::cout << "--------" << std::endl;
	{
		std::cout << "Key Comp (true):\n";
		ft::map<int, std::string>	map;
		std::cout << "\t\tcmp(1, 2)\t:  " << map.key_comp()(1, 2) << std::endl;

		std::cout << "Key Comp (false):\n";
		std::cout << "\t\tcmp(2, 1)\t:  " << map.key_comp()(2, 1) << std::endl;
	}
	std::cout << "--------" << std::endl;
	{
		std::cout << "Value Comp (true):\n";
		ft::map<int, std::string>	map;
		ispair a = ft::make_pair(1, "One");
		ispair b = ft::make_pair(2, "Two");
		std::cout << "\t\tcmp(1, 2)\t:  " << map.value_comp()(a, b) << std::endl;

		std::cout << "Value Comp (false):\n";
		std::cout << "\t\tcmp(2, 1)\t:  " << map.value_comp()(b, a) << std::endl;
	}
	std::cout << "--------" << std::endl;
	{
		std::cout << "Find:\n";
		ft::map<int, std::string>	map(parr, parr + 7);
		print_param(map);
		ft::map<int, std::string>::iterator	it = map.find(4);
		std::cout << "\n  map.find(4):\n";
		printContent(it, ++it);

		ft::map<int, std::string>::iterator	it2 = map.find(8);
		if (it2 != map.end())
		{
			std::cout << "\n map.find(8):\n";
			printContent(it2, ++it2);
		}
	}
	std::cout << "--------" << std::endl;
	{
		std::cout << "Count:\n";
		ft::map<int, std::string>	map(parr, parr + 7);
		print_param(map);
		std::cout << "\n\t\tcount(4):\t" << map.count(4) << "\n";

		std::cout << "\n\t\tcount(8):\t" << map.count(8) << "\n";
	}
	std::cout << "--------" << std::endl;
	{
		std::cout << "Lower bound:\n";
		ft::map<int, std::string>	map(parr, parr + 7);
		print_param(map);
		ft::map<int, std::string>::iterator	it = map.lower_bound(4);
		std::cout << "\n  map.lower_bound(4):\n";
		printContent(it, ++it);

		ft::map<int, std::string>::iterator	it2 = map.lower_bound(8);
		if (it2 != map.end())
		{
			std::cout << "\n  map.lower_bound(8):\n";
			printContent(it2, ++it2);
		}
	}
	std::cout << "--------" << std::endl;
	{
		std::cout << "Upper bound:\n";
		ft::map<int, std::string>	map(parr, parr + 7);
		print_param(map);
		ft::map<int, std::string>::iterator	it = map.upper_bound(4);
		std::cout << "\n  map.upper_bound(4):\n";
		printContent(it, ++it);

		ft::map<int, std::string>::iterator	it2 = map.upper_bound(8);
		if (it2 != map.end())
		{
			std::cout << "\n  map.upper_bound(8):\n";
			printContent(it2, ++it2);
		}
	}
	std::cout << "--------" << std::endl;
	{
		std::cout << "Equal range:\n";
		ft::map<int, std::string>	map(parr, parr + 7);
		print_param(map);
		typedef ft::map<int, std::string>::iterator iter;
		ft::pair<iter, iter>	it = map.equal_range(4);
		std::cout << "\n  map.equal_range(4):\n";
		printContent(it.first, it.second);

		ft::pair<iter, iter>	it2 = map.equal_range(8);
		std::cout << "\n  map.equal_range(8):\n";
		printContent(it2.first, it2.second);
	}
	std::cout << "--------" << std::endl;
	{
		std::cout << "Operator == :\n";
		ft::map<int, std::string>	map(parr, parr + 7);
		std::cout << "  map == map:\t" << (map == map) << std::endl;

		int			iarr2[] = { 4, 7, 8 };
		std::string	sarr2[] = { "Four", "Seven", "Eight" };
		ispair		parr2[3];
		for (size_t i = 0; i < 3; i++)
			parr2[i] = ft::make_pair(iarr2[i], sarr2[i]);
		ft::map<int, std::string>	map2(parr2, parr2 + 3);
		std::cout << "  map1 == map2:\t" << (map == map2) << std::endl;
	}
	std::cout << "--------" << std::endl;
	{
		std::cout << "Operator != :\n";
		ft::map<int, std::string>	map(parr, parr + 7);
		std::cout << "  map != map:\t" << (map != map) << std::endl;

		int			iarr2[] = { 4, 7, 8 };
		std::string	sarr2[] = { "Four", "Seven", "Eight" };
		ispair		parr2[3];
		for (size_t i = 0; i < 3; i++)
			parr2[i] = ft::make_pair(iarr2[i], sarr2[i]);
		ft::map<int, std::string>	map2(parr2, parr2 + 3);
		std::cout << "  map1 != map2:\t" << (map != map2) << std::endl;
	}
	std::cout << "--------" << std::endl;
	{
		std::cout << "Operator < :\n";
		ft::map<int, std::string>	map(parr, parr + 7);
		std::cout << "  map < map:\t" << (map < map) << std::endl;

		int			iarr2[] = { 4, 7, 8 };
		std::string	sarr2[] = { "Four", "Seven", "Eight" };
		ispair		parr2[3];
		for (size_t i = 0; i < 3; i++)
			parr2[i] = ft::make_pair(iarr2[i], sarr2[i]);
		ft::map<int, std::string>	map2(parr2, parr2 + 3);
		std::cout << "  map1 < map2:\t" << (map < map2) << std::endl;
	}
	std::cout << "--------" << std::endl;
	{
		std::cout << "Operator <= :\n";
		int			iarr2[] = { 4, 7, 8 };
		std::string	sarr2[] = { "Four", "Seven", "Eight" };
		ispair		parr2[3];
		for (size_t i = 0; i < 3; i++)
			parr2[i] = ft::make_pair(iarr2[i], sarr2[i]);
		ft::map<int, std::string>	map(parr, parr + 7);
		ft::map<int, std::string>	map2(parr2, parr2 + 3);

		std::cout << "  map2 <= map1:\t" << (map2 <= map) << std::endl;
		std::cout << "  map1 <= map2:\t" << (map <= map2) << std::endl;
	}
	std::cout << "--------" << std::endl;
	{
		std::cout << "Operator > :\n";
		int			iarr2[] = { 4, 7, 8 };
		std::string	sarr2[] = { "Four", "Seven", "Eight" };
		ispair		parr2[3];
		for (size_t i = 0; i < 3; i++)
			parr2[i] = ft::make_pair(iarr2[i], sarr2[i]);
		ft::map<int, std::string>	map(parr, parr + 7);
		ft::map<int, std::string>	map2(parr2, parr2 + 3);

		std::cout << "  map2 > map1:\t" << (map2 > map) << std::endl;
		std::cout << "  map1 > map2:\t" << (map > map2) << std::endl;
	}
	std::cout << "--------" << std::endl;
	{
		std::cout << "Operator >= :\n";
		int			iarr2[] = { 4, 7, 8 };
		std::string	sarr2[] = { "Four", "Seven", "Eight" };
		ispair		parr2[3];
		for (size_t i = 0; i < 3; i++)
			parr2[i] = ft::make_pair(iarr2[i], sarr2[i]);
		ft::map<int, std::string>	map(parr, parr + 7);
		ft::map<int, std::string>	map2(parr2, parr2 + 3);

		std::cout << "  map2 >= map1:\t" << (map2 >= map) << std::endl;
		std::cout << "  map1 >= map2:\t" << (map >= map2) << std::endl;
	}
	std::cout << "--------" << std::endl;
	{
		std::cout << "Swap(non-member function):\n";
		int			iarr2[] = { 4, 7, 8 };
		std::string	sarr2[] = { "Four", "Seven", "Eight" };
		ispair		parr2[3];
		for (size_t i = 0; i < 3; i++)
			parr2[i] = ft::make_pair(iarr2[i], sarr2[i]);
		ft::map<int, std::string>	map(parr, parr + 7);
		ft::map<int, std::string>	map2(parr2, parr2 + 3);
		std::cout << "  map1:\n";
		printContent(map.begin(), map.end());
		std::cout << "  map2:\n";
		printContent(map2.begin(), map2.end());

		ft::swap(map, map2);
		std::cout << "\n swap(map1, map2):\n  map1:\n";
		printContent(map.begin(), map.end());
		std::cout << "  map2:\n";
		printContent(map2.begin(), map2.end());
	}
}