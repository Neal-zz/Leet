#include <iostream>
#include <vector>
#include <string>

#include "dynamic_program.h"

int main() {

	std::cout << coinsDP(1113) << std::endl;

	std::vector<unsigned> seq({ 10,9,2,5,3,7,101,18 });
	std::cout << lis(seq) << std::endl;

	std::cout << minDisDP("rad", "apple") << std::endl;

	std::cout << brokenEgg(2, 1040) << std::endl;
	std::cout << brokenEggDP(2, 1040) << std::endl;

	std::cout << lpsDP("abxabybx") << std::endl;

	std::cout << psDP({ 3,9,1,2 }) << std::endl;

	return 0;
}