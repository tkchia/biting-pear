#include <iomanip>
#include <iostream>
#include <innocent-pear/orly.h>

int main(void)
{
	using innocent_pear::ops::allow_for_startup;
	typedef innocent_pear::orly?<uint32_t, true, true,
	    allow_for_startup, 3u> f2_t;
	typedef innocent_pear::orly?<uint32_t, false, false,
	    allow_for_startup> f3_t;
	typedef innocent_pear::orly?<uint32_t, true, false,
	    allow_for_startup, 1u> f4_t;
	typedef f2_t::inv::unbad g2_t;
	typedef f3_t::inv::unbad g3_t;
	typedef f4_t::inv::unbad g4_t;
	f2_t f2;  f3_t f3;  f4_t f4;
	g2_t g2;  g3_t g3;  g4_t g4;
	uint32_t z2 = f2(0x98badcfeu), z3 = f3(0x10325476u),
		 z4 = f4(0xc3d2e1f0u);
	std::cout << std::hex
		  << g2(z2) << ' '
		  << g3(z3) << ' '
		  << g4(z4) << '\n';
	return 0;
}
