#include <cinttypes>
#include <climits>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <sys/mman.h>
#include <innocent-pear/dawg.h>
#include <innocent-pear/kthxbai.h>
#include <innocent-pear/orly.h>
#include <innocent-pear/rofl.h>
#include "doge-i.h"

using innocent_pear::impl::uintptr_t;

extern unsigned char our_relro_start[] __asm("_.innocent_pear.relro.start");
extern unsigned char our_relro_end[] __asm("_.innocent_pear.relro.end");

innocent_pear_HERE_START
innocent_pear_NEXT

innocent_pear_DOGE unscramble_04_1()
{
	constexpr auto flags = innocent_pear_FLAGS;
	innocent_pear::kthxbai?<unsigned char *, flags> nxs(next_start);
	innocent_pear::kthxbai?<unsigned char *, flags> nxe(next_end);
	innocent_pear::kthxbai?<unsigned char *, flags, 0u>
	    rrs(our_relro_start);
	innocent_pear::kthxbai?<unsigned char *, flags, 0u> rre(our_relro_end);
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
	constexpr auto flags = innocent_pear_FLAGS;
	innocent_pear::rofl?<flags>::memset((void *)here_start);
}
