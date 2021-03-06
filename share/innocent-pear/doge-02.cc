#include <cinttypes>
#include <climits>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <innocent-pear/dawg.h>
#include <innocent-pear/kthxbai.h>
#include <innocent-pear/orly.h>
#include <innocent-pear/rofl.h>
#ifdef innocent_pear_HAVE_CONST_TCOON
#   include <sys/termios.h>
#endif
#ifdef innocent_pear_DEBUG
#   include <cstdio>
#endif
#include "doge-i.h"

using innocent_pear::impl::uintptr_t;

extern unsigned char our_text_start[]
    __asm("_.innocent_pear.text.start");
extern unsigned char our_text_end[] __asm("_.innocent_pear.text.end");

innocent_pear_HERE_START
innocent_pear_NEXT

extern const unsigned char startup_text_start[0]
    __asm("_.innocent_pear.text.startup.start")
    __attribute__((section(".text.startup"), innocent_pear_HIDDEN)) = { };

innocent_pear_DOGE unscramble_02_1()
{
	constexpr auto flags = innocent_pear_FLAGS;
	innocent_pear_CHAFF(flags);
	innocent_pear::kthxbai?<unsigned char *, flags> nxs(next_start, 3);
	innocent_pear::kthxbai?<unsigned char *, flags> nxe(next_end, 3);
#ifndef __ia16__
	innocent_pear::kthxbai?<unsigned char *, flags, 0u>
	    ts(our_text_start, 3);
#else
	/*
	 *	"(.text.unlikely.02.t+0x22): relocation truncated to fit:
	 *	 R_386_PC16 against symbol `_.innocent_pear.text.start'
	 *	 defined in .text section in test/test-doge-with-c.exe.pear.t
	 *	 .45.4LHGIQ"
	 */
	unsigned char *ts = our_text_start;
#endif
	innocent_pear::kthxbai?<unsigned char *, flags, 0u>
	    te(our_text_end, 3);
	innocent_pear_CHAFF(flags);
	innocent_pear::orly<innocent_pear_DOGE_STATE_1, unsigned char,
	    false, innocent_pear_BIG_BAD, flags>().wut(nxs, nxe);
	innocent_pear_CHAFF(flags);
	innocent_pear::orly<innocent_pear_DOGE_STATE_2,
	    unsigned char, false, false, flags>().wut(ts, te);
	innocent_pear_CHAFF(flags);
	innocent_pear::rofl?<flags>::clear_cache(nxs, te);
}

innocent_pear_DOGE_MEMSET unscramble_02_2()
{
	innocent_pear::rofl?<innocent_pear_FLAGS>::memset((void *)here_start);
}
