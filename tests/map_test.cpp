#include "map.hpp"
#include <map>
#include <iostream>
#include <string>

template <typename Key, typename Val>
void	printAttr(ft::map<Key, Val>& map)
{
	std::cout << "      Empty\t:  " << ((map.empty()) ? "true\n" : "false\n");
	std::cout << "      Size\t:  " << map.size() << "\n";
	std::cout << "      Max size\t:  " << map.max_size() << "\n";
	std::cout << "      Content\t:  [(";
	typename ft::map<Key, Val>::const_iterator	beg = map.begin();
	typename ft::map<Key, Val>::const_iterator	it = beg;
	typename ft::map<Key, Val>::iterator	end = map.end();
	for (; it != end; ++it)
	{
		if (it != beg)
			std::cout << "), (";
		std::cout << (*it).first << " ; " << (*it).second;
	}
	std::cout << ")]\n";
}

template <typename Key, typename Val>
void	printAttr(const ft::map<Key, Val>& map)
{
	std::cout << "      Empty\t:  " << ((map.empty()) ? "true\n" : "false\n");
	std::cout << "      Size\t:  " << map.size() << "\n";
	std::cout << "      Max size\t:  " << map.max_size() << "\n";
	std::cout << "      Content\t:  [(";
	typename ft::map<Key, Val>::const_iterator	beg = map.begin();
	typename ft::map<Key, Val>::const_iterator	it = beg;
	typename ft::map<Key, Val>::const_iterator	end = map.end();
	for (; it != end; ++it)
	{
		if (it != beg)
			std::cout << "), (";
		std::cout << (*it).first << " ; " << (*it).second;
	}
	std::cout << ")]\n";
}
typedef ft::pair<int, std::string> ispair;
void map_test() {
    std::cout << "  Constructors:\n";

	{
		std::cout << "    Defaul constructor:\n";
		ft::map<int, std::string>	map;
		printAttr(map);
	}

	std::cout << "\n";

	{
		std::cout << "    Fill constructor:\n";
		int			iarr[] = { 1, 2, 3, 6, 5, 4, 4 };
		std::string	sarr[] = { "One", "Two", "Three", "Six", "Five", "Four", "asdasda" };
		ispair		parr[7];
		for (size_t i = 0; i < 7; i++)
			parr[i] = ft::make_pair(iarr[i], sarr[i]);
		ft::map<int, std::string>	map(parr, parr + 7);
		printAttr(map);
	}

}