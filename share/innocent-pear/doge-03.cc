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

extern unsigned char unlikely_text_start[]
    __asm("_.innocent_pear.text.unlikely.start");
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

innocent_pear_DOGE("03") unscramble_03_03()
{
	unsigned char *rs = our_rodata_start, *re = our_rodata_end;
	innocent_pear::orly<innocent_pear_DOGE_STATE_3,
	    unsigned char, false, false, flags>().wut(rs, re);
}

innocent_pear_DOGE_MEMSET("03") unscramble_03_04()
{
	innocent_pear::rofl?<flags, 3u>::memset((void *)unscramble_03_03);
}

innocent_pear_DOGE("03") unscramble_03_05()
{
	unsigned char *rrs = our_relro_start, *rre = our_relro_end;
	innocent_pear::orly<innocent_pear_DOGE_STATE_4,
	    unsigned char, false, false, flags>().wut(rrs, rre);
}

innocent_pear_DOGE_MEMSET("03") unscramble_03_06()
{
	innocent_pear::rofl?<flags, 3u>::memset((void *)unscramble_03_04);
}

innocent_pear_DOGE("03") unscramble_03_07()
{
	unsigned char *ds = our_data_start, *de = our_data_end;
	innocent_pear::orly<innocent_pear_DOGE_STATE_5,
	    unsigned char, false, false, flags>().wut(ds, de);
}

innocent_pear_DOGE_MEMSET("03") unscramble_03_08()
{
	innocent_pear::rofl?<flags, 3u>::memset((void *)unscramble_03_06);
}

class dogecoin_t
{
	const std::size_t l_ = sizeof(uintptr_t) - 1;
	union {
		uintptr_t d;
		unsigned char c[sizeof(uintptr_t)];
	} u_;
	__attribute__((always_inline))
	void reset()
	{
#if innocent_pear_ENDIANNESS - 0 == 1234  /* little endian */
		u_.d = (uintptr_t)1 << (l_ * CHAR_BIT);
#else
		std::memset(u_.c, 0, l_);
		u_.c[l_] = 1;
#endif
	}
    public:
	dogecoin_t()
		{ reset(); }
	__attribute__((always_inline))
	void operator()(unsigned char c, const unsigned char *dp)
	{
#if innocent_pear_ENDIANNESS - 0 == 1234  /* little endian */
		bool a = (u_.d & 1) != 0;
		u_.d = u_.d >> CHAR_BIT | (uintptr_t)c << (l_ * CHAR_BIT);
#else
		bool a = u_.c[0] != 0;
		std::memmove(u_.c, u_.c + 1, l_);
		u_.c[l_] = c;
#endif
#ifdef __i386__
#   define ADJ		4
#else
#   define ADJ		0
#endif
		if (!a)
			return;
		uintptr_t d = u_.d;
		uintptr_t *rp = reinterpret_cast<uintptr_t *>(
		    reinterpret_cast<uintptr_t>(dp) + d + ADJ);
#ifdef innocent_pear_DEBUG
		std::fprintf(stderr, "dp == %p\n"
				     "d == %#" PRIxPTR "\n"
				     "rp == %p\n"
				     "*rp == %#" PRIxPTR "\n",
		    dp, d, rp, *rp);
#endif
		*rp += reinterpret_cast<uintptr_t>(rp) + ADJ;
#ifdef innocent_pear_DEBUG
		std::fprintf(stderr, "now *rp == %#" PRIxPTR "\n", *rp);
#endif
		reset();
	}
};

innocent_pear_DOGE("03") unscramble_03_09()
{
	dogecoin_t dogecoin;
	innocent_pear::orly<innocent_pear_DOGE_STATE_6,
	    unsigned char, false, false, flags>().wot(dogecoin_start,
	    dogecoin_end, dogecoin);
}

innocent_pear_DOGE_MEMSET("03") unscramble_03_10()
{
	innocent_pear::rofl?<flags, 3u>::memset((void *)unscramble_03_08);
}

innocent_pear_DOGE("03") unscramble_03_11()
{
	uintptr_t pg_sz = (uintptr_t)getpagesize();
	unsigned char *prot_start =
	    (unsigned char *)(((uintptr_t)our_rodata_start+pg_sz-1) & -pg_sz);
	/*
	 * Apply mprotect(...) to one page at a time, since there may be
	 * gaps in the virtual memory mapping between the end of .rodata and
	 * the end of .data.rel.ro .
	 */
	while (prot_start + pg_sz <= our_relro_end) {
		innocent_pear::rofl?<flags>::mprotect(prot_start, pg_sz,
		    PROT_READ);
		prot_start += pg_sz;
	}
#if 0
	/*
	 * This is only needed if the linker is lumping the .data section
	 * (and friends) along with the .text section into a single rwx
	 * segment.
	 */
	unsigned char *prot_end =
	    (unsigned char *)(((uintptr_t)our_bss_end + pg_sz - 1)& -pg_sz);
	innocent_pear::rofl?<flags, 3u>::mprotect(prot_start,
	    prot_end - prot_start, PROT_READ | PROT_WRITE);
#endif
}

innocent_pear_DOGE_MEMSET("03") unscramble_03_12()
{
	innocent_pear::rofl?<flags, 3u>::memset((void *)unscramble_03_10);
}

#ifdef innocent_pear_HAVE_CONST_TCOON
innocent_pear_DOGE("03") unscramble_03_13()
{
	innocent_pear::rofl?<flags2>::tcflow(0, TCOON);
	innocent_pear::rofl?<flags2>::tcflow(1, TCOON);
	innocent_pear::rofl?<flags2>::tcflow(2, TCOON);
#ifdef __unix__
	char fn[9];
	$"/dev/tty" >> fn;
	int fd = innocent_pear::rofl?<flags2>::open(fn, O_RDONLY);
	std::memset(fn, 0, 9);
	innocent_pear::rofl?<flags2>::tcflow(fd, TCOON);
	innocent_pear::rofl?<flags2>::close(fd);
#endif
}

innocent_pear_DOGE_MEMSET("03") unscramble_03_14()
{
	innocent_pear::rofl?<flags2, 3u>::memset((void *)unscramble_03_12);
}
#endif
