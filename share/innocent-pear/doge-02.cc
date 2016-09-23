#include <cinttypes>
#include <climits>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <sys/mman.h>
#include <innocent-pear/dawg.h>
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

extern unsigned char next_start[]
    __asm("_.innocent_pear.text.doge.03.start");
extern unsigned char next_end[]
    __asm("_.innocent_pear.text.doge.45.start");
extern unsigned char our_text_start[]
    __asm("_.innocent_pear.text.start");
extern unsigned char our_text_end[] __asm("_.innocent_pear.text.end");
extern unsigned char our_rodata_start[] __asm("_.innocent_pear.rodata.start");
extern unsigned char our_rodata_end[] __asm("_.innocent_pear.rodata.end");
extern unsigned char our_relro_start[] __asm("_.innocent_pear.relro.start");
extern unsigned char our_relro_end[] __asm("_.innocent_pear.relro.end");
extern unsigned char our_data_start[] __asm("_.innocent_pear.data.start");
extern unsigned char our_data_end[] __asm("_.innocent_pear.data.end");
extern unsigned char our_bss_end[] __asm("_end");
extern unsigned char dogecoin_start[] __asm("_.innocent_pear.dogecoin.start");
extern unsigned char dogecoin_end[] __asm("_.innocent_pear.dogecoin.end");

static constexpr innocent_pear::impl::ops_flags_t flags =
    innocent_pear::ops::allow_all |
    innocent_pear::ops::under_munged_terminal;
static constexpr innocent_pear::impl::ops_flags_t flags2 =
    innocent_pear::ops::allow_all &
   ~innocent_pear::ops::allow_terminal_unsafes;

innocent_pear_HERE_START;

extern const unsigned char startup_text_start[0]
    __asm("_.innocent_pear.text.startup.start")
    __attribute__((section(".text.startup"))) = { };

innocent_pear_DOGE unscramble_02_1()
{
	unsigned char *nxs = next_start, *nxe = next_end,
	    *ts = our_text_start, *te = our_text_end;
	innocent_pear_CHAFF(flags);
	innocent_pear::orly<innocent_pear_DOGE_STATE_1,
	    unsigned char, false, true, flags>().wut(nxs, nxe);
	innocent_pear_CHAFF(flags);
	innocent_pear::rofl?<flags, 3u>::clear_cache(nxs, nxe);
	innocent_pear_CHAFF(flags);
	innocent_pear::orly<innocent_pear_DOGE_STATE_2,
	    unsigned char, false, false, flags>().wut(ts, te);
	innocent_pear_CHAFF(flags);
	innocent_pear::rofl?<flags, 3u>::clear_cache(ts, te);
	innocent_pear_CHAFF(flags);
}

innocent_pear_DOGE_MEMSET unscramble_02_2()
{
	innocent_pear::rofl?<flags, 3u>::memset((void *)here_start);
}
