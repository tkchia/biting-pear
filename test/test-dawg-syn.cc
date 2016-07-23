#include <iostream>
#include <locale>
#include <innocent-pear/dawg.h>

#define BLARGH		std::cout << $"Hello, world!\n" \
				  << $"Hello, world!\n" \
				  << $"Hello, world!\n" \
				  << $"Hello, world!\n" \
				  << $"Hello, world!\n" \
				  << $"Hello, world!\n"

int main()
{
	std::locale::global(std::locale(""));
	BLARGH;
	BLARGH;
	BLARGH;
	BLARGH;
	BLARGH;
	BLARGH;
	return 0;
}
