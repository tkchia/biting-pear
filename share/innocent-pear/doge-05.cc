#include <cinttypes>
#include <climits>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <innocent-pear/dawg.h>
#include <innocent-pear/kthxbai.h>
#include <innocent-pear/orly.h>
#include <innocent-pear/rofl.h>
#include "doge-i.h"

extern unsigned char our_data_start[] __asm("_.innocent_pear.data.start");
extern unsigned char our_data_end[] __asm("_.innocent_pear.data.end");

innocent_pear_HERE_START
innocent_pear_NEXT

innocent_pear_DOGE unscramble_05_1()
{
	constexpr auto flags = innocent_pear_FLAGS;
	innocent_pear_CHAFF(flags);
	innocent_pear::kthxbai?<unsigned char *, flags> nxs(next_start, 3);
	innocent_pear::kthxbai?<unsigned char *, flags> nxe(next_end, 3);
	innocent_pear::kthxbai?<unsigned char *, flags, 0u>
	    ds(our_data_start, 3);
	innocent_pear::kthxbai?<unsigned char *, flags, 0u>
	    de(our_data_end, 3);
	innocent_pear_CHAFF(flags);
	innocent_pear::orly<innocent_pear_DOGE_STATE_7, unsigned char,
	    false, innocent_pear_BIG_BAD, flags>().wut(nxs, nxe);
	innocent_pear_CHAFF(flags);
	innocent_pear::orly<innocent_pear_DOGE_STATE_8,
	    unsigned char, false, false, flags>().wut(ds, de);
	innocent_pear_CHAFF(flags);
	innocent_pear::rofl?<flags>::clear_cache(nxs, nxe);
}

innocent_pear_DOGE_MEMSET unscramble_05_2()
{
	innocent_pear::rofl?<innocent_pear_FLAGS>::memset((void *)here_start);
}
