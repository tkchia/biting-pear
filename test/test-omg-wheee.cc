#include <iomanip>
#include <iostream>
#define innocent_pear_DEBUG_WHEEE
#include <innocent-pear/omg.h>

int main(void)
{
	using innocent_pear::ops::allow_for_startup;
	std::cout << "1\n";
	innocent_pear::omg?<unsigned, allow_for_startup>().wheee();
	std::cout << "2\n";
	innocent_pear::omg?<unsigned, allow_for_startup>().wheee();
	std::cout << "3\n";
	innocent_pear::omg?<unsigned, allow_for_startup>().wheee();
	std::cout << "done\n";
	return 0;
}
