#ifndef biting_pear_H_BBQ
#define biting_pear_H_BBQ

#include <cinttypes>
#include <climits>
#include <biting-pear/derp.h>

namespace biting_pear
{

namespace impl
{

typedef uint_least32_t ops_flags_t;
typedef uint_least64_t rand_state_t;

inline constexpr rand_state_t xorshr(rand_state_t s, unsigned i)
{
	return s ^ s >> i;
}

inline constexpr rand_state_t xorshl(rand_state_t s, unsigned i)
{
	return s ^ s << i;
}

inline constexpr rand_state_t update_outer(rand_state_t s)
{
	// arxiv.org/abs/1402.6246
	return xorshr(xorshl(xorshr(s, 12), 25), 27) * 2685821657736338717ull;
}

inline constexpr rand_state_t update_inner(rand_state_t s)
{
	return s * 6364136223846793005ull + 1ull;
}

template<unsigned WhichOp, class T>
inline T do_op(T x, T y)
{
	switch (WhichOp % 3) {
	    case 0:
		return x + y;
	    case 1:
		return x - y;
	    default:
		return x ^ y;
	}
}

template<unsigned WhichOp, class T>
inline T do_inv_op(T x, T y)
{
	switch (WhichOp % 3) {
	    case 0:
		return x - y;
	    case 1:
		return x + y;
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

template<class T, T P = ((T)1 << (sizeof(T) * CHAR_BIT - 1)) - 1>
inline constexpr T pow(T x)
{
	return P == 0 ? (T)1 :
	    P % 2 == 0 ? pow<T, P / 2>(x * x) :
			 pow<T, P / 2>(x * x) * x;
}

} // biting_pear::impl

namespace ops {

static const biting_pear::impl::ops_flags_t
    allow_signal_safes		= 0x00000001u,
    allow_signal_unsafes	= 0x00000002u,
    allow_debugger_unsafes	= 0x00000004u,
    allow_emulator_unsafes	= 0x00000008u,
    allow_resource_unsafes	= 0x00000010u,
    allow_all			= 0xffffffffu;

} // biting_pear::ops

} // biting_pear

#endif
