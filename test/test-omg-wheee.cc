#include <iomanip>
#include <iostream>
#define innocent_pear_DEBUG_WHEEE
#include <innocent-pear/omg.h>

#define BLARGH(func, levels) \
	__attribute__((noinline)) \
	static void func(void) \
	{ \
		using innocent_pear::ops::allow_for_startup; \
		innocent_pear::omg?<unsigned, allow_for_startup, (levels)>:: \
		    wheee(); \
	}

BLARGH(f1, 1u)
BLARGH(f2, 1u)
BLARGH(f3, 1u)
BLARGH(f4, 1u)
BLARGH(f5, 1u)
BLARGH(f6, 2u)
BLARGH(f7, 2u)
BLARGH(f8, 2u)
BLARGH(f9, 2u)
BLARGH(f10, 3u)
BLARGH(f11, 3u)
BLARGH(f12, 3u)

int main(void)
{
	std::cout << "1\n";
	f1();
	std::cout << "2\n";
	f2();
	std::cout << "3\n";
	f3();
	std::cout << "4\n";
	f4();
	std::cout << "5\n";
	f5();
	std::cout << "6\n";
	f6();
	std::cout << "7\n";
	f7();
	std::cout << "8\n";
	f8();
	std::cout << "9\n";
	f9();
	std::cout << "10\n";
	f10();
	std::cout << "11\n";
	f11();
	std::cout << "12\n";
	f12();
	std::cout << "done\n";
	return 0;
}
