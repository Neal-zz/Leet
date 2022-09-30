#include <iostream>
#include <vector>
#include <string>

#include "dynamic_program.h"

int main() {

	std::cout << coinsDP(1113) << std::endl;

	std::vector<unsigned> seq({ 10,9,2,5,3,7,101,18 });
	std::cout << lis(seq) << std::endl;

	std::string s1 = "rad", s2 = "apple";
	std::cout << minDisDP(s1, s2) << std::endl;

	
	return 0;
}