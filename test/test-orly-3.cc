#include <cstdio>
#include <innocent-pear/orly.h>

int main(int argc, char **argv)
{
	using innocent_pear::ops::allow_for_startup;
	using innocent_pear::impl::uint_least64_t;
	typedef innocent_pear::orly?<uint_least64_t, false, false,
	    allow_for_startup, 4u> f0_t;
	typedef f0_t::inv::bad g0_t;
	f0_t f0;
	g0_t g0;
	innocent_pear::kthxbai?<innocent_pear_decltype(&std::printf),
	    allow_for_startup, 1u> pf(std::printf);
	uint_least64_t c0, z0, w0;
	c0 = 0x67452301efcdab89ull;
#ifndef __ia16__
	if (argc > 1)
		c0 = std::strtoul(argv[1], 0, 0);
#endif
	z0 = f0(c0);
	w0 = g0(z0);
#ifndef __ia16__
	pf("%#" PRIxLEAST64 "\n", w0);
#else
	/* PRIxLEAST64 does not work correctly under ia16-elf. */
	using innocent_pear::impl::uint_least32_t;
	pf("0x%08" PRIxLEAST32 "%08" PRIxLEAST32 "\n",
	    (uint_least32_t)(w0 >> 32), (uint_least32_t)w0);
#endif
	return 0;
}
