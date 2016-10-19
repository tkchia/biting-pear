#include <cinttypes>
#include <climits>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <sys/mman.h>
#include <innocent-pear/dawg.h>
#include <innocent-pear/orly.h>
#include <innocent-pear/rofl.h>
#ifdef innocent_pear_DEBUG
#   include <cstdio>
#endif
#include "doge-i.h"

using innocent_pear::impl::uintptr_t;
using innocent_pear::impl::ops_flags_t;
using innocent_pear::ops;

extern unsigned char dogecoin_start[] __asm("_.innocent_pear.dogecoin.start");
extern unsigned char dogecoin_end[] __asm("_.innocent_pear.dogecoin.end");

innocent_pear_HERE_START
innocent_pear_NEXT

class dogecoin_t
{
	static constexpr std::size_t l_ = sizeof(uintptr_t) - 1;
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
		dp -= sizeof(dp) - 1;
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

innocent_pear_DOGE unscramble_06_1()
{
	static constexpr ops_flags_t flags =
	    (ops_flags_t)(allow_for_startup | under_munged_terminal);
	unsigned char *nxs = next_start, *nxe = next_end;
	innocent_pear_CHAFF(flags);
	innocent_pear::orly<innocent_pear_DOGE_STATE_9,
	    unsigned char, false, true, flags>().wut(nxs, nxe);
	innocent_pear_CHAFF(flags);
	innocent_pear::rofl?<flags>::clear_cache(nxs, nxe);
	innocent_pear_CHAFF(flags);
	dogecoin_t dogecoin;
	innocent_pear::orly<innocent_pear_DOGE_STATE_10,
	    unsigned char, false, false, flags>().wot(dogecoin_start,
	    dogecoin_end, dogecoin);
	innocent_pear_CHAFF(flags);
}

innocent_pear_DOGE_MEMSET unscramble_06_2()
{
	static constexpr ops_flags_t flags =
	    (ops_flags_t)(allow_for_startup | under_munged_terminal);
	innocent_pear::rofl?<flags>::memset((void *)here_start);
}
