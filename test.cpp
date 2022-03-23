#include <iostream>
#include <cctype>
#include <time.h>
#include "tests/test.hpp"

void time(clock_t start) {
	clock_t end = clock();
	double	avg = (((double)end - start) / ((double) CLOCKS_PER_SEC));
	std::cout << "\nAverage time to complete the test: " << avg << " second(s)\n";
}

void toLow(char *str) {
	for (int i = 0; str[i]; ++i)
		str[i] = tolower(str[i]);
}

int main(int ac, char **av) {
	if (ac > 2)
		return (std::cerr << "Usage: ./containers_ft/std [container_name(optional)]." << std::endl && 1);
	clock_t start;
	if (ac == 1) {
		start = clock();
		vector_test();
		stack_test();
		map_test();
		set_test();
		time(start);
	}
	else {
		toLow(av[1]);
		std::string container(av[1]);
		if (container == "vector") {
			start = clock();
			vector_test();
			time(start);
		}
		else if (container == "stack") {
			start = clock();
			stack_test();
			time(start);
		}
		else if (container == "map") {
			start = clock();
			map_test();
			time(start);
		}
		else if (container == "set") {
			start = clock();
			set_test();
			time(start);
		}
		else
			return (std::cerr << "Usage container names: vector, stack, map or set." << std::endl && 1);
	}
	return 0;
}