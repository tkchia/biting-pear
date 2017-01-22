#include <cstdio>
#include <innocent-pear/orly.h>

int main(int argc, char **argv)
{
	using innocent_pear::ops::allow_for_startup;
	using innocent_pear::impl::uint_least64_t;
	typedef innocent_pear::orly?<uint_least64_t, false, true,
	    allow_for_startup> f0_t;
	typedef f0_t::inv::bad g0_t;
	f0_t f0;
	g0_t g0;
	innocent_pear::kthxbai?<innocent_pear_decltype(&std::printf),
	    allow_for_startup, 1u> pf(std::printf);
	uint_least64_t c0, z0, w0;
	if (argc < 2)
		c0 = 0x67452301efcdab89ull;
	else
		c0 = std::strtoul(argv[1], 0, 0);
	z0 = f0(c0);
	w0 = g0(z0);
	pf("%#" PRIxLEAST64 "\n", w0);
	return 0;
}
