#include <cinttypes>
#include <cstdlib>
#include <unistd.h>
#include <sys/mman.h>
#include <innocent-pear/orly.h>
#include <innocent-pear/rofl.h>
#ifdef innocent_pear_HAVE_CONST_TCOON
#   include <sys/termios.h>
#endif
#ifdef innocent_pear_DEBUG
#   include <cstdio>
#endif

using innocent_pear::impl::uintptr_t;

extern unsigned char unlikely_text_start[]
    __asm("_.innocent_pear.text.unlikely.start");
extern unsigned char our_text_start[]
    __asm("_.innocent_pear.text.start");
extern unsigned char our_text_end[] __asm("_.innocent_pear.text.end");
extern unsigned char our_rodata_start[] __asm("_.innocent_pear.rodata.start");
extern unsigned char our_rodata_end[] __asm("_.innocent_pear.rodata.end");
extern unsigned char our_data_start[] __asm("_.innocent_pear.data.start");
extern unsigned char our_data_end[] __asm("_.innocent_pear.data.end");
extern uintptr_t dogecoin_start[] __asm("_.innocent_pear.dogecoin.start");
extern uintptr_t dogecoin_end[] __asm("_.innocent_pear.dogecoin.end");

__attribute__((
#ifdef innocent_pear_HAVE_CTOR_PRIORITY
    constructor(101),
#else
    constructor,
#endif
    section(".text.unlikely"), optimize("no-reorder-blocks")))
static void unscramble_2()
{
	static constexpr innocent_pear::impl::ops_flags_t flags =
	    innocent_pear::ops::allow_all |
	    innocent_pear::ops::under_munged_terminal;
	using innocent_pear::impl::update_outer;
	using innocent_pear::impl::update_inner;
	unsigned char *uts = unlikely_text_start,
	    *ts = our_text_start, *te = our_text_end,
	    *rs = our_rodata_start, *re = our_rodata_end,
	    *ds = our_data_start, *de = our_data_end;
	innocent_pear::orly<innocent_pear_DOGE_STATE_2,
	    unsigned char, false, false, flags>().wut(ts, te);
	innocent_pear::rofl?<flags>::clear_cache(ts, te);
	innocent_pear::orly<innocent_pear_DOGE_STATE_3,
	    unsigned char, false, false, flags>().wut(rs, re);
	innocent_pear::orly<innocent_pear_DOGE_STATE_4,
	    unsigned char, false, false, flags>().wut(ds, de);
	for (uintptr_t *dp = dogecoin_start; dp != dogecoin_end; ++dp) {
		uintptr_t *rp = reinterpret_cast<uintptr_t *>(
		    reinterpret_cast<uintptr_t>(dp) + *dp);
#ifdef innocent_pear_DEBUG
		std::fprintf(stderr, "dp == %p\n"
				     "*dp == %#" PRIxPTR "\n"
				     "rp == %p\n"
				     "*rp == %#" PRIxPTR "\n",
		    dp, *dp, rp, *rp);
#endif
		*rp += reinterpret_cast<uintptr_t>(rp);
#ifdef innocent_pear_DEBUG
		std::fprintf(stderr, "now *rp == %#" PRIxPTR "\n", *rp);
#endif
	}
	innocent_pear::rofl?<flags>::memset(uts);
}
