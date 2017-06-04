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

extern unsigned char our_relro_start[] __asm("_.innocent_pear.relro.start");
extern unsigned char our_relro_end[] __asm("_.innocent_pear.relro.end");

innocent_pear_HERE_START
innocent_pear_NEXT

innocent_pear_DOGE unscramble_04_1()
{
	constexpr auto flags = innocent_pear_FLAGS;
	innocent_pear_CHAFF(flags);
#ifndef __ia16__
	innocent_pear::kthxbai?<unsigned char *, flags> nxs(next_start, 3);
	innocent_pear::kthxbai?<unsigned char *, flags> nxe(next_end, 3);
	innocent_pear::kthxbai?<unsigned char *, flags, 0u>
	    rrs(our_relro_start, 3);
	innocent_pear::kthxbai?<unsigned char *, flags, 0u>
	    rre(our_relro_end, 3);
#else
	/*
	 * It is quite unlikely for an ia16-elf program to have a .data.rel.ro
	 * section, so be a bit lax here.
	 */
	unsigned char *nxs = next_start, *nxe = next_end,
	    *rrs = our_relro_start, *rre = our_relro_end;
#endif
	innocent_pear_CHAFF(flags);
	innocent_pear::orly<innocent_pear_DOGE_STATE_5, unsigned char,
	    false, innocent_pear_BIG_BAD, flags>().wut(nxs, nxe);
	innocent_pear_CHAFF(flags);
	innocent_pear::orly<innocent_pear_DOGE_STATE_6,
	    unsigned char, false, false, flags>().wut(rrs, rre);
	innocent_pear_CHAFF(flags);
	innocent_pear::rofl?<flags>::clear_cache(nxs, nxe);
}

innocent_pear_DOGE_MEMSET unscramble_04_2()
{
	innocent_pear::rofl?<innocent_pear_FLAGS>::memset((void *)here_start);
}
