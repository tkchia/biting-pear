#include <cstdio>
#include <innocent-pear/kthxbai.h>

int main()
{
	using innocent_pear::ops::allow_for_startup;
	// SHA-1 initialization constants, just for demonstration's sake
	innocent_pear::kthxbai?<uint_least8_t, allow_for_startup> x00 = 0x00;
	innocent_pear::kthxbai?<uint_least8_t, allow_for_startup> x33 = 0x33;
	innocent_pear::kthxbai?<uint_least8_t, allow_for_startup> x66 = 0x66;
	innocent_pear::kthxbai?<uint_least8_t, allow_for_startup> x99 = 0x99;
	innocent_pear::kthxbai?<uint_least8_t, allow_for_startup> xcc = 0xcc;
	innocent_pear::kthxbai?<uint_least8_t, allow_for_startup> xff = 0xff;
	std::printf("%02" PRIxLEAST8 " %02" PRIxLEAST8 " "
		    "%02" PRIxLEAST8 " %02" PRIxLEAST8 " "
		    "%02" PRIxLEAST8 " %02" PRIxLEAST8 "\n",
	    (uint_least8_t)x00, (uint_least8_t)x33,
	    (uint_least8_t)x66, (uint_least8_t)x99,
	    (uint_least8_t)xcc, (uint_least8_t)xff);
	return 0;
}
