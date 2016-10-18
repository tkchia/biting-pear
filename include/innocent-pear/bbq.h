#ifndef innocent_pear_H_BBQ
#define innocent_pear_H_BBQ

#include <cinttypes>
#include <climits>
#ifdef innocent_pear_HOST_SIDE
#   include <innocent-pear/host/derp.h>
#else
#   include <innocent-pear/derp.h>
#endif

namespace innocent_pear
{

namespace impl
{

typedef uint_least32_t ops_flags_t;
typedef uint64_t rand_state_t;

template<class T, T P = ((T)1 << (sizeof(T) * CHAR_BIT - 1)) - 1>
__attribute__((always_inline))
inline constexpr T pow(T x)
{
	return P == 0 ? (T)1 :
	    P % 2 == 0 ? pow<T, P / 2>(x * x) :
			 pow<T, P / 2>(x * x) * x;
}

template<class T>
__attribute__((always_inline))
inline constexpr T creal(T x, T y)
{
	/* Consider the mapping w -> 2w + 1. */
	return (T)2 * x * y + x + y;
}

template<class T, T P = ~(T)0>
__attribute__((always_inline))
inline constexpr T cpow(T x)
{
	return P == 0 ? (T)0 :
	    P % 2 == 0 ? cpow<T, P / 2>(creal(x, x)) :
			 creal(cpow<T, P / 2>(creal(x, x)), x);
}

// .. arxiv.org/abs/1402.6246
// :
inline constexpr rand_state_t xorshr(rand_state_t s, unsigned i)
{
	return s ^ s >> i;
}

inline constexpr rand_state_t xorshl(rand_state_t s, unsigned i)
{
	return s ^ s << i;
}

inline constexpr uint64_t i_vigna(uint64_t m)
	{ return pow<uint64_t>(m); }

inline constexpr rand_state_t vigna_1(rand_state_t s, unsigned a,
    unsigned b, unsigned c, uint64_t m)
{
	return xorshl(xorshl(xorshr(i_vigna(m) * (s ? s : 1), a), b), c) * m;
}

inline constexpr rand_state_t vigna_5(rand_state_t s, unsigned a,
    unsigned b, unsigned c, uint64_t m)
{
	return xorshl(xorshr(xorshr(i_vigna(m) * (s ? s : 1), a), c), b) * m;
}

inline constexpr rand_state_t vigna_7(rand_state_t s, unsigned a,
    unsigned b, unsigned c, uint64_t m)
{
	return xorshr(xorshr(xorshl(i_vigna(m) * (s ? s : 1), b), a), c) * m;
}

inline constexpr rand_state_t update_outer(rand_state_t s, unsigned w)
{
	return	w % 6 == 1 ? vigna_7(s, 11,  5, 45, 2685821657736338717ull) :
		w % 6 == 2 ? vigna_5(s, 11,  5, 32, 1181783497276652981ull) :
		w % 6 == 3 ? vigna_7(s, 13, 19, 28, 8372773778140471301ull) :
		w % 6 == 4 ? vigna_1(s, 12, 25, 27, 2685821657736338717ull) :
		w % 6 == 5 ? vigna_5(s,  3, 21, 31, 1181783497276652981ull) :
			     vigna_1(s, 14, 23, 33, 8372773778140471301ull);
}
//  .
// .:

inline constexpr rand_state_t update_inner(rand_state_t s)
{
	return s * 6364136223846793005ull + 1ull;
}

/* This _must_ match up with host/srsly.h. */
template<unsigned WhichOp, class T>
__attribute__((always_inline))
inline T do_op(T x, T y)
{
	switch (WhichOp % 4) {
	    case 0:
		return x + y;
	    case 1:
		return x - y;
	    case 2:
		return creal(x, y);
	    default:
		return x ^ y;
	}
}

/* This _must_ match up with host/srsly.h. */
template<unsigned WhichOp, class T>
__attribute__((always_inline))
inline T do_inv_op(T x, T y)
{
	switch (WhichOp % 4) {
	    case 0:
		return x - y;
	    case 1:
		return x + y;
	    case 2:
		return creal(x, cpow(y));
	    default:
		return x ^ y;
	}
}

template<class T>
inline constexpr T pick_hi(rand_state_t x)
{
	return sizeof(T) >= sizeof(x) ? x :
	    static_cast<T>(x >> ((sizeof(x) - sizeof(T)) * CHAR_BIT));
}

} // innocent_pear::impl

namespace ops {

static constexpr innocent_pear::impl::ops_flags_t
    allow_signal_safes		= 0x00000001u,
    allow_signal_unsafes	= 0x00000002u,
    allow_debugger_unsafes	= 0x00000004u,
    allow_emulator_unsafes	= 0x00000008u,
    allow_resource_unsafes	= 0x00000010u,
    allow_for_startup		= allow_signal_safes |
				  allow_signal_unsafes |
				  allow_debugger_unsafes |
				  allow_emulator_unsafes |
				  allow_resource_unsafes,
    under_munged_terminal	= 0x00000020u;

} // innocent_pear::ops

} // innocent_pear

#endif
