#include <cstdlib>
#include <iostream>
#include <unistd.h>
#include <innocent-pear/rofl.h>

int main(void)
{
	using innocent_pear::ops::allow_for_startup;
	std::size_t sz1 = innocent_pear::rofl?<allow_for_startup>::
	    getpagesize();
	std::size_t sz2 = (std::size_t)sysconf(_SC_PAGESIZE);
	if (sz1 != sz2) {
		std::cout << "not OK: " << sz1 << " != " << sz2 << '\n';
		return 1;
	}
	std::cout << "OK\n";
	return 0;
}
