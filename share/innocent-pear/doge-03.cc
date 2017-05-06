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

using innocent_pear::impl::uintptr_t;

extern unsigned char our_rodata_start[] __asm("_.innocent_pear.rodata.start");
extern unsigned char our_rodata_end[] __asm("_.innocent_pear.rodata.end");

innocent_pear_HERE_START
innocent_pear_NEXT

innocent_pear_DOGE unscramble_03_1()
{
	constexpr auto flags = innocent_pear_FLAGS;
	innocent_pear_CHAFF(flags);
	innocent_pear::kthxbai?<unsigned char *, flags> nxs(next_start);
	innocent_pear::kthxbai?<unsigned char *, flags> nxe(next_end);
	innocent_pear::kthxbai?<unsigned char *, flags, 0u>
	    rs(our_rodata_start);
	innocent_pear::kthxbai?<unsigned char *, flags, 0u> re(our_rodata_end);
	innocent_pear_CHAFF(flags);
	innocent_pear::orly<innocent_pear_DOGE_STATE_3, unsigned char,
	    false, innocent_pear_BIG_BAD, flags>().wut(nxs, nxe);
	innocent_pear_CHAFF(flags);
	innocent_pear::orly<innocent_pear_DOGE_STATE_4,
	    unsigned char, false, false, flags>().wut(rs, re);
	innocent_pear_CHAFF(flags);
	innocent_pear::rofl?<flags>::clear_cache(nxs, nxe);
}

innocent_pear_DOGE_MEMSET unscramble_03_2()
{
	constexpr auto flags = innocent_pear_FLAGS;
	innocent_pear::rofl?<flags>::memset((void *)here_start);
}
