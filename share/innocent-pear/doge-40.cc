#include <cinttypes>
#include <climits>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <innocent-pear/dawg.h>
#include <innocent-pear/kthxbai.h>
#include <innocent-pear/orly.h>
#include <innocent-pear/rofl.h>
#ifdef innocent_pear_DEBUG
#   include <cstdio>
#endif
#include "doge-i.h"

using innocent_pear::impl::uintptr_t;

extern unsigned char dogecoin_start[] __asm("_.innocent_pear.dogecoin.start");
extern unsigned char dogecoin_end[] __asm("_.innocent_pear.dogecoin.end");

innocent_pear_HERE_START
innocent_pear_NEXT

class dogecoin_t
{
#ifndef __ia16__
	static constexpr std::size_t l_ = sizeof(uintptr_t) - 1;
	union {
		uintptr_t d;
		unsigned char c[sizeof(uintptr_t)];
	} u_;
	innocent_pear_always_inline
	void reset()
	{
#   if innocent_pear_ENDIANNESS - 0 == 1234  /* little endian */
		u_.d = (uintptr_t)1 << (l_ * CHAR_BIT);
#   else
		std::memset(u_.c, 0, l_);
		u_.c[l_] = 1;
#   endif
	}
    public:
	dogecoin_t()
		{ reset(); }
	template<class DPT>
	innocent_pear_always_inline
	void operator()(unsigned char c, DPT dp)
	{
#   if innocent_pear_ENDIANNESS - 0 == 1234  /* little endian */
		bool a = (u_.d & 1) != 0;
		u_.d = u_.d >> CHAR_BIT | (uintptr_t)c << (l_ * CHAR_BIT);
#   else
		bool a = u_.c[0] != 0;
		std::memmove(u_.c, u_.c + 1, l_);
		u_.c[l_] = c;
#   endif
#   ifdef __i386__
#	define ADJ	4
#   else
#	define ADJ	0
#   endif
		if (!a)
			return;
		dp -= sizeof(dp) - 1;
		uintptr_t d = u_.d;
		uintptr_t *rp = reinterpret_cast<uintptr_t *>
		    (reinterpret_cast<uintptr_t>
			(static_cast<unsigned char *>(dp)) + d + ADJ);
#   ifdef innocent_pear_DEBUG
		std::fprintf(stderr, "dp == %p\n"
				     "d == %#" PRIxPTR "\n"
				     "rp == %p\n"
				     "*rp == %#" PRIxPTR "\n",
		    +dp, d, rp, *rp);
#   endif
		*rp += reinterpret_cast<uintptr_t>(rp) + ADJ;
#   ifdef innocent_pear_DEBUG
		std::fprintf(stderr, "now *rp == %#" PRIxPTR "\n", *rp);
#   endif
		reset();
	}
#else
	static_assert(sizeof(void *) == 2, "we are compiling for IA-16 "
	    "but not with 2-char-wide pointers?");
	unsigned char x_;
	bool y_;
    public:
	dogecoin_t() : x_(0), y_(0)
		{ }
	template<class DPT>
	void operator()(unsigned char c, DPT dp)
	{
		if (!y_) {
			x_ = c;
			y_ = true;
			return;
		}
		dp -= sizeof(dp) - 1;
		uintptr_t d = (uintptr_t)c << CHAR_BIT | x_;
		uintptr_t *rp = reinterpret_cast<uintptr_t *>
		    (reinterpret_cast<uintptr_t>
			(static_cast<unsigned char *>(dp)) + d);
		*rp += reinterpret_cast<uintptr_t>(rp);
		y_ = false;
	}
#endif
};

innocent_pear_DOGE unscramble_40_1()
{
	constexpr auto flags = innocent_pear_FLAGS;
	innocent_pear_CHAFF(flags);
	innocent_pear::kthxbai?<unsigned char *, flags> nxs(next_start);
	innocent_pear::kthxbai?<unsigned char *, flags> nxe(next_end);
	innocent_pear_CHAFF(flags);
	innocent_pear::orly<innocent_pear_DOGE_STATE_9,
	    unsigned char, false, innocent_pear_BIG_BAD, flags>().
	    wut(nxs, nxe);
	innocent_pear_CHAFF(flags);
	innocent_pear::kthxbai?<unsigned char *, flags, 0u>
	    dcs(dogecoin_start);
	innocent_pear::kthxbai?<unsigned char *, flags, 0u> dce(dogecoin_end);
	dogecoin_t dogecoin;
	innocent_pear::orly<innocent_pear_DOGE_STATE_10,
	    unsigned char, false, false, flags>().wot(dogecoin_start,
	    dogecoin_end, dogecoin);
	innocent_pear_CHAFF(flags);
}

#ifndef __ia16__
innocent_pear_DOGE unscramble_40_2()
{
	constexpr auto flags = innocent_pear_FLAGS;
	innocent_pear_CHAFF(flags);
	innocent_pear::kthxbai?<unsigned char *, flags> nxs(next_start);
	innocent_pear::kthxbai?<unsigned char *, flags> nxe(next_end);
	innocent_pear_CHAFF(flags);
	innocent_pear::rofl?<flags>::clear_cache(nxs, nxe);
	innocent_pear_CHAFF(flags);
}
#endif

innocent_pear_DOGE_MEMSET unscramble_40_3()
{
	innocent_pear::rofl?<innocent_pear_FLAGS>::memset((void *)here_start);
}
