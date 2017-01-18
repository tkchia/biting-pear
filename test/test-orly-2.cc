#include <cstdio>
#include <cstdlib>
#include <innocent-pear/kthxbai.h>
#include <innocent-pear/orly.h>

int main(int argc, char **argv)
{
	using innocent_pear::ops::allow_for_startup;
	using innocent_pear::impl::uint_least32_t;
	typedef innocent_pear::orly?<uint_least32_t, true, true,
	    allow_for_startup, 3u> f2_t;
	typedef innocent_pear::orly?<uint_least32_t, false, false,
	    allow_for_startup> f3_t;
	typedef innocent_pear::orly?<uint_least32_t, true, false,
	    allow_for_startup, 1u> f4_t;
	typedef f2_t::inv::unbad g2_t;
	typedef f3_t::inv::unbad g3_t;
	typedef f4_t::inv::unbad g4_t;
	f2_t f2;  f3_t f3;  f4_t f4;
	g2_t g2;  g3_t g3;  g4_t g4;
	innocent_pear::kthxbai?<innocent_pear_decltype(&std::printf),
	    allow_for_startup, 1u> pf(std::printf);
	uint_least32_t c2, z2, w2;
	if (argc < 2)
		c2 = 0x98badcfeu;
	else
		c2 = std::strtoul(argv[1], 0, 0);
	z2 = f2(c2);
	w2 = g2(z2);
	if (argc < 2) {
		uint_least32_t z3 = f3(0x10325476u), z4 = f4(0xc3d2e1f0u);
		pf("%x %x %x\n", w2, g3(z3), g4(z4));
	} else
		pf("%x\n", w2);
	return 0;
}
