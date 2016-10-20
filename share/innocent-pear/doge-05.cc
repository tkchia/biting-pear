#include <cinttypes>
#include <climits>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <sys/mman.h>
#include <innocent-pear/dawg.h>
#include <innocent-pear/orly.h>
#include <innocent-pear/rofl.h>
#include "doge-i.h"

using innocent_pear::impl::uintptr_t;
using innocent_pear::ops_flags_t;
using namespace innocent_pear::ops;

extern unsigned char our_data_start[] __asm("_.innocent_pear.data.start");
extern unsigned char our_data_end[] __asm("_.innocent_pear.data.end");

innocent_pear_HERE_START
innocent_pear_NEXT

innocent_pear_DOGE unscramble_05_1()
{
	constexpr ops_flags_t flags =
	    (ops_flags_t)(allow_for_startup | under_munged_terminal);
	unsigned char *nxs = next_start, *nxe = next_end,
	    *ds = our_data_start, *de = our_data_end;
	innocent_pear_CHAFF(flags);
	innocent_pear::orly<innocent_pear_DOGE_STATE_7,
	    unsigned char, false, true, flags>().wut(nxs, nxe);
	innocent_pear_CHAFF(flags);
	innocent_pear::orly<innocent_pear_DOGE_STATE_8,
	    unsigned char, false, false, flags>().wut(ds, de);
	innocent_pear_CHAFF(flags);
	innocent_pear::rofl?<flags>::clear_cache(nxs, nxe);
}

innocent_pear_DOGE_MEMSET unscramble_05_2()
{
	constexpr ops_flags_t flags =
	    (ops_flags_t)(allow_for_startup | under_munged_terminal);
	innocent_pear::rofl?<flags>::memset((void *)here_start);
}
