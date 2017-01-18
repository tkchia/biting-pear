#include <cstdio>
#include <innocent-pear/orly.h>

int main(int argc, char **argv)
{
	using innocent_pear::ops::allow_for_startup;
	using innocent_pear::impl::uint_least32_t;
	typedef innocent_pear::orly?<uint_least32_t, true, true,
	    allow_for_startup> f0_t;
	typedef innocent_pear::orly?<uint_least32_t, false, true,
	    allow_for_startup> f1_t;
	typedef f0_t::inv::unbad g0_t;
	typedef f1_t::inv::unbad g1_t;
	f0_t f0;  f1_t f1;
	g0_t g0;  g1_t g1;
	innocent_pear::kthxbai?<innocent_pear_decltype(&std::printf),
	    allow_for_startup, 1u> pf(std::printf);
	uint_least32_t c0, z0, w0;
	if (argc < 2)
		c0 = 0x67452301u;
	else
		c0 = std::strtoul(argv[1], 0, 0);
	z0 = f0(c0);
	w0 = g0(z0);
	if (argc < 2) {
		uint_least32_t z1 = f1(0xefcdab89u);
		pf("%x %x\n", w0, g1(z1));
	} else
		pf("%x\n", w0);
	return 0;
}
