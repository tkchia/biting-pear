#include <cstring>
#include <iostream>
#include <locale>
#include <innocent-pear/dawg.h>

int main()
{
	std::locale::global(std::locale(""));
	std::cout << $"Hello, world!\n"
		  << $"Hello, world!\n"
		  << $"Hello, world!\n"
		  << $$"Hello, world!\n"
		  << $$"Hello, world!\n"
		  << $$"Hello, world!\n";
	char foo[sizeof("Hello, world!\n")];
	memset(foo, 0, sizeof foo);
	$$"Hello, world!\n" >> foo;
	std::cout << foo;
	memset(foo, 0, sizeof foo);
	$$"Hello, world!\n" >> foo;
	std::cout << foo;
	memset(foo, 0, sizeof foo);
	$$"Hello, world!\n" >> foo;
	std::cout << foo;
	memset(foo, 0, sizeof foo);
	return 0;
}
