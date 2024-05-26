#include <iostream>


int main()
{
	int condition = 0;

	while (condition != 4) {
		std::cout << "YOU want to login as:\t\t\t\t\t\t" << std::endl << std::endl;
		std::cout << "1-ADMIN" << std::endl;
		std::cout << "2-STAFF" << std::endl;
		std::cout << "3-CUSTOMER" << std::endl;
		std::cin >> condition;

		if (condition == 1) {
		
		}
		if (condition == 2) {

		}
		if (condition == 3) {

		}
		if (condition == 4) {

		}
	}


	std::cin.get();
	return 0;
}