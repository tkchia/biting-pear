#ifndef biting_pear_H_BBQ
#define biting_pear_H_BBQ

#include <cinttypes>
#include <climits>

namespace biting_pear
{

namespace impl
{

inline constexpr uint_least64_t xorshr(uint_least64_t s, unsigned i)
{
	return s ^ s >> i;
}

inline constexpr uint_least64_t xorshl(uint_least64_t s, unsigned i)
{
	return s ^ s << i;
}

inline constexpr uint_least64_t update_outer(uint_least64_t s)
{
	// arxiv.org/abs/1402.6246
	return xorshr(xorshl(xorshr(s, 12), 25), 27) * 2685821657736338717ull;
}

inline constexpr uint_least64_t update_inner(uint_least64_t s)
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
inline constexpr T pick_hi(uint_least64_t x)
{
	return sizeof(T) >= sizeof(x) ? x :
	    static_cast<T>(x >> ((sizeof(x) - sizeof(T)) * CHAR_BIT));
}

} // biting_pear::impl

} // biting_pear

#endif
