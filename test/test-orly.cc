#include <iomanip>
#include <iostream>
#include <innocent-pear/orly.h>

int main(void)
{
	using innocent_pear::ops::allow_all;
	typedef innocent_pear::orly?<uint32_t, true, true, allow_all> f0_t;
	typedef innocent_pear::orly?<uint32_t, true, true, allow_all> f1_t;
	typedef innocent_pear::orly?<uint32_t, true, true, allow_all> f2_t;
	typedef innocent_pear::orly?<uint32_t, true, true, allow_all> f3_t;
	typedef innocent_pear::orly?<uint32_t, true, true, allow_all> f4_t;
	typedef f0_t::inv::unbad g0_t;
	typedef f1_t::inv::unbad g1_t;
	typedef f2_t::inv::unbad g2_t;
	typedef f3_t::inv::unbad g3_t;
	typedef f4_t::inv::unbad g4_t;
	f0_t f0;  f1_t f1;  f2_t f2;  f3_t f3;  f4_t f4;
	g0_t g0;  g1_t g1;  g2_t g2;  g3_t g3;  g4_t g4;
	uint32_t z0 = f0(0x67452301u), z1 = f1(0xefcdab89u),
		 z2 = f2(0x98badcfeu), z3 = f3(0x10325476u),
		 z4 = f4(0xc3d2e1f0u);
	std::cout << std::hex
		  << g0(z0) << ' '
		  << g1(z1) << ' '
		  << g2(z2) << ' '
		  << g3(z3) << ' '
		  << g4(z4) << '\n';
	return 0;
}
