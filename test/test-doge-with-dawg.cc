#include <iostream>
#include <innocent-pear/dawg.h>

struct hello_t
{
	__attribute__((always_inline))
	hello_t()
	{
		std::cout << $ "\"'Twas brillig, and the slithy toves\n"
				" Did gyre and gymble in the wabe;\n";
	}
};

hello_t hello;

int main()
{
	std::cout << $	" All mimsy were the borogoves,\n"
			" And the mome raths outgrabe.\"\n";
	return 0;
}
