#include <iomanip>
#include <iostream>

extern void foo();

int main()
{
	try {
		std::cout << "try\n";
		foo();
	} catch (int i) {
		std::cout << "catch\n";
		return 0;
	} catch (unsigned i) {
		std::cout << "wrong catch...\n";
		return 1;
	}
	std::cout << "oops\n";
	return 2;
}
