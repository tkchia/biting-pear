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

extern unsigned char our_relro_start[] __asm("_.innocent_pear.relro.start");
extern unsigned char our_relro_end[] __asm("_.innocent_pear.relro.end");

innocent_pear_HERE_START
innocent_pear_NEXT

innocent_pear_DOGE unscramble_04_1()
{
	constexpr ops_flags_t flags =
	    (ops_flags_t)(allow_for_startup | under_munged_terminal);
	unsigned char *nxs = next_start, *nxe = next_end,
	    *rrs = our_relro_start, *rre = our_relro_end;
	innocent_pear_CHAFF(flags);
	innocent_pear::orly<innocent_pear_DOGE_STATE_5,
	    unsigned char, false, true, flags>().wut(nxs, nxe);
	innocent_pear_CHAFF(flags);
	innocent_pear::orly<innocent_pear_DOGE_STATE_6,
	    unsigned char, false, false, flags>().wut(rrs, rre);
	innocent_pear_CHAFF(flags);
	innocent_pear::rofl?<flags>::clear_cache(nxs, nxe);
}

innocent_pear_DOGE_MEMSET unscramble_04_2()
{
	constexpr ops_flags_t flags =
	    (ops_flags_t)(allow_for_startup | under_munged_terminal);
	innocent_pear::rofl?<flags>::memset((void *)here_start);
}
