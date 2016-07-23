#include <iomanip>
#include <iostream>
#include <innocent-pear/kthxbai.h>

int main(void)
{
	using innocent_pear::ops::allow_all;
	// SHA-1 initialization constants, just for demonstration's sake
	innocent_pear::kthxbai?<uint32_t, allow_all> h0 = 0x67452301u;
	innocent_pear::kthxbai?<uint32_t, allow_all> h1 = 0xefcdab89u;
	innocent_pear::kthxbai?<uint32_t, allow_all> h2 = 0x98badcfeu;
	innocent_pear::kthxbai?<uint32_t, allow_all> h3 = 0x10325476u;
	innocent_pear::kthxbai?<uint32_t, allow_all> h4 = 0xc3d2e1f0u;
	std::cout << std::hex
		  << h0 << ' '
		  << h1 << ' '
		  << h2 << ' '
		  << h3 << ' '
		  << h4 << '\n';
	return 0;
}
