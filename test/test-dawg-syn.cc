#include <iostream>
#include <locale>
#include <innocent-pear/dawg.h>

int main()
{
	std::locale::global(std::locale(""));
	std::cout << $"Hello, world!\n"
		  << $"Hello, world!\n"
		  << $"Hello, world!\n"
		  << $"Hello, world!\n"
		  << $"Hello, world!\n"
		  << $"Hello, world!\n";
	return 0;
}
