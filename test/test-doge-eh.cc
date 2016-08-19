#include <cerrno>
#include <iomanip>
#include <iostream>

void foo()
{
	std::cout << "throw\n";
	throw 2;
}

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
