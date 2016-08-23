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

#ifdef innocent_pear_HAVE_CTOR_PRIORITY
#   define innocent_pear_CTOR	constructor(101)
#else
#   define innocent_pear_CTOR	constructor
#endif
#define innocent_pear_DOGE \
	__attribute__((innocent_pear_CTOR, section(".text.unlikely"))) \
	static void
#define innocent_pear_DOGE_MEMSET \
	__attribute__((innocent_pear_CTOR, section(".text.unlikely"), \
	    optimize("no-reorder-blocks"))) \
	static void

static constexpr innocent_pear::impl::ops_flags_t flags =
    innocent_pear::ops::allow_all |
    innocent_pear::ops::under_munged_terminal;
static constexpr innocent_pear::impl::ops_flags_t flags2 =
    innocent_pear::ops::allow_all &
   ~innocent_pear::ops::allow_terminal_unsafes;

innocent_pear_DOGE unscramble_03_1()
{
	unsigned char *ts = our_text_start, *te = our_text_end;
	innocent_pear::orly<innocent_pear_DOGE_STATE_2,
	    unsigned char, false, false, flags>().wut(ts, te);
	innocent_pear::rofl?<flags, 3u>::clear_cache(ts, te);
}

innocent_pear_DOGE_MEMSET unscramble_03_2()
{
	unsigned char *uts = unlikely_text_start;
	innocent_pear::rofl?<flags, 3u>::memset(uts);
}

innocent_pear_DOGE unscramble_03_3()
{
	unsigned char *rs = our_rodata_start, *re = our_rodata_end;
	innocent_pear::orly<innocent_pear_DOGE_STATE_3,
	    unsigned char, false, false, flags>().wut(rs, re);
}

innocent_pear_DOGE_MEMSET unscramble_03_4()
{
	innocent_pear::rofl?<flags, 3u>::memset((void *)unscramble_03_2);
}

innocent_pear_DOGE unscramble_03_5()
{
	unsigned char *ds = our_data_start, *de = our_data_end;
	innocent_pear::orly<innocent_pear_DOGE_STATE_4,
	    unsigned char, false, false, flags>().wut(ds, de);
}

innocent_pear_DOGE_MEMSET unscramble_03_6()
{
	innocent_pear::rofl?<flags, 3u>::memset((void *)unscramble_03_4);
}

innocent_pear_DOGE unscramble_03_7()
{
#ifdef __i386__
#   define ADJ		4
#else
#   define ADJ		0
#endif
	for (uintptr_t *dp = dogecoin_start; dp != dogecoin_end; ++dp) {
		uintptr_t *rp = reinterpret_cast<uintptr_t *>(
		    reinterpret_cast<uintptr_t>(dp) + *dp + ADJ);
#ifdef innocent_pear_DEBUG
		std::fprintf(stderr, "dp == %p\n"
				     "*dp == %#" PRIxPTR "\n"
				     "rp == %p\n"
				     "*rp == %#" PRIxPTR "\n",
		    dp, *dp, rp, *rp);
#endif
		*rp += reinterpret_cast<uintptr_t>(rp) + ADJ;
#ifdef innocent_pear_DEBUG
		std::fprintf(stderr, "now *rp == %#" PRIxPTR "\n", *rp);
#endif
	}
}

innocent_pear_DOGE_MEMSET unscramble_03_8()
{
	innocent_pear::rofl?<flags, 3u>::memset((void *)unscramble_03_6);
}

#ifdef innocent_pear_HAVE_CONST_TCOON
innocent_pear_DOGE unscramble_03_9()
{
	innocent_pear::rofl?<flags2>::tcflow(0, TCOON);
	innocent_pear::rofl?<flags2>::tcflow(1, TCOON);
	innocent_pear::rofl?<flags2>::tcflow(2, TCOON);
}

innocent_pear_DOGE_MEMSET unscramble_03_10()
{
	innocent_pear::rofl?<flags, 3u>::memset((void *)unscramble_03_8);
}
#endif
