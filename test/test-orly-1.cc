#include <iomanip>
#include <iostream>
#include <innocent-pear/orly.h>

int main(void)
{
	using innocent_pear::ops::allow_for_startup;
	typedef innocent_pear::orly?<uint32_t, true, true,
	    allow_for_startup> f0_t;
	typedef innocent_pear::orly?<uint32_t, false, true,
	    allow_for_startup> f1_t;
	typedef f0_t::inv::unbad g0_t;
	typedef f1_t::inv::unbad g1_t;
	f0_t f0;  f1_t f1;
	g0_t g0;  g1_t g1;
	uint32_t z0 = f0(0x67452301u), z1 = f1(0xefcdab89u);
	std::cout << std::hex
		  << g0(z0) << ' '
		  << g1(z1) << '\n';
	return 0;
}
