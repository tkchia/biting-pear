#include <iostream>

struct hello_t
{
	__attribute__((always_inline))
	hello_t()
	{
		std::cout << "Hello world!\n";
	}
};

hello_t hello;

int main()
{
	std::cout << "And hello world again!\n";
	return 0;
}
