#ifndef innocent_pear_H_BBQ
#define innocent_pear_H_BBQ

#include <cinttypes>
#include <climits>
#include <limits>
#ifdef innocent_pear_HOST_SIDE
#   include <innocent-pear/host/derp.h>
#else
#   include <innocent-pear/derp.h>
#endif

namespace innocent_pear
{

namespace impl
{

typedef uint_least64_t rand_state_t;

#ifdef __ELF__
#   define innocent_pear_always_inline \
	__attribute__((always_inline, visibility("hidden"))) inline
#   define innocent_pear_always_inline_and(...) \
	__attribute__((always_inline, visibility("hidden"), __VA_ARGS__)) \
	inline
#else
#   define innocent_pear_always_inline \
	__attribute__((always_inline)) inline
#   define innocent_pear_always_inline_and(...) \
	__attribute__((always_inline, __VA_ARGS__)) inline
#endif

template<class T, T P = std::numeric_limits<T>::max() / 2>
innocent_pear_always_inline
constexpr T pow(T x)
{
	/*
	 * The seemingly redundant conditionals, e.g. `P > 17 ? 17 : 0', are
	 * to prevent clang++ from giving a
	 *
	 *	"fatal error: recursive template instantiation exceeded
	 *	 maximum depth of 256"
	 */
	return P == 0 ? (T)1 :
	    P % 17 == 0 && P > 17 ?
		pow<T, (P > 17 ? P / 17 : 0)>(pow<T, (P > 17 ? 17 : 0)>(x)) :
	    P % 15 == 0 && P > 15 ?
		pow<T, (P > 15 ? P / 15 : 0)>(pow<T, (P > 15 ? 15 : 0)>(x)) :
	    P % 2 == 0 ? pow<T, P / 2>(x * x) :
			 pow<T, P / 2>(x * x) * x;
}

template<class T>
innocent_pear_always_inline
constexpr T creal(T x, T y)
{
	/* Consider the mapping w -> 2w + 1. */
	return (y + y + (T)1) * x + y;
}

template<class T, T P = (std::numeric_limits<T>::max() > 3 ?
			 std::numeric_limits<T>::max() / 2 :
			 std::numeric_limits<T>::max())>
innocent_pear_always_inline
constexpr T cpow(T x)
{
	return P == 0 ? (T)0 :
	    P % 17 == 0 && P > 17 ?
		cpow<T, (P > 17 ? P / 17 : 0)>(cpow<T, (P > 17 ? 17 : 0)>(x)) :
	    P % 15 == 0 && P > 15 ?
		cpow<T, (P > 15 ? P / 15 : 0)>(cpow<T, (P > 15 ? 15 : 0)>(x)) :
	    P % 2 == 0 ?
		cpow<T, P / 2>((T)2 * (x + (T)1) * x) :
		creal(cpow<T, P / 2>((T)2 * (x + (T)1) * x), x);
}

template<class T>
innocent_pear_always_inline
constexpr T crealf(T x, T y)
{
	/* Consider the mapping w -> 4w + 1. */
	return ((T)4 * y + (T)1) * x + y;
}

template<class T, T P = std::numeric_limits<T>::max()>
innocent_pear_always_inline
constexpr T cpowf(T x)
{
	return P == 0 ? (T)0 :
	    P % 17 == 0 && P > 17 ?
		cpowf<T, (P>17 ? P / 17 : 0)>(cpowf<T, (P>17 ? 17 : 0)>(x)) :
	    P % 15 == 0 && P > 15 ?
		cpowf<T, (P>15 ? P / 15 : 0)>(cpowf<T, (P>15 ? 15 : 0)>(x)) :
	    P % 2 == 0 ?
		cpowf<T, P / 2>((T)2 * (x + x + (T)1) * x) :
		crealf(cpowf<T, P / 2>((T)2 * (x + x + (T)1) * x), x);
}

inline constexpr rand_state_t clip(rand_state_t s)
{
	/* In case rand_state_t is not _exactly_ 64 bits wide. */
	return s & (((rand_state_t)1 << 63 << 1) - 1);
}

// .. arxiv.org/abs/1402.6246
// :
inline constexpr rand_state_t xorshr(rand_state_t s, unsigned i)
{
	return s ^ clip(s) >> i;
}

inline constexpr rand_state_t xorshl(rand_state_t s, unsigned i)
{
	return s ^ s << i;
}

inline constexpr uint_least64_t i_vigna(uint_least64_t m)
	{ return pow<uint_least64_t>(m); }

inline constexpr rand_state_t vigna_1(rand_state_t s, unsigned a,
    unsigned b, unsigned c, uint_least64_t m)
{
	return clip(xorshl(xorshl(xorshr(i_vigna(m) * (s ? s : 1), a), b), c)
	    * m);
}

inline constexpr rand_state_t vigna_5(rand_state_t s, unsigned a,
    unsigned b, unsigned c, uint_least64_t m)
{
	return clip(xorshl(xorshr(xorshr(i_vigna(m) * (s ? s : 1), a), c), b)
	    * m);
}

inline constexpr rand_state_t vigna_7(rand_state_t s, unsigned a,
    unsigned b, unsigned c, uint_least64_t m)
{
	return clip(xorshr(xorshr(xorshl(i_vigna(m) * (s ? s : 1), b), a), c)
	    * m);
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
innocent_pear_always_inline
T do_op(T x, T y)
{
	switch (WhichOp % 6) {
	    case 0:
		return x + y;
	    case 1:
		return x - y;
	    case 2:
		return creal(x, cpow(y));
	    case 3:
		return crealf(x, cpowf(y));
	    case 4:
		return (T)5 * x + y;
	    default:
		return x ^ y;
	}
}

/* This _must_ match up with host/srsly.h. */
template<unsigned WhichOp, class T>
innocent_pear_always_inline
T do_inv_op(T x, T y)
{
	switch (WhichOp % 6) {
	    case 0:
		return x - y;
	    case 1:
		return x + y;
	    case 2:
		return creal(x, y);
	    case 3:
		return crealf(x, y);
	    case 4:
		return pow<T>(5) * (x - y);
	    default:
		return x ^ y;
	}
}

/* This _must_ match up with do_op(...) above. */
template<unsigned WhichOp, uintptr_t N, class T>
innocent_pear_always_inline
T do_op_rept(T x, T y)
{
	switch (WhichOp % 6) {
	    case 0:
		return x + N * y;
	    case 1:
		return x - N * y;
	    case 2:
		return creal(x, cpow(cpow<T, (T)N>(y)));
	    case 3:
		return crealf(x, cpowf<T, (T)-(T)N>(y));
	    case 4:
		return pow<T, (T)N>(5) * x + cpowf<T, (T)N>(1) * y;
	    default:
		return N % 2 ? x ^ y : x;
	}
}

/* This _must_ match up with do_inv_op(...) above. */
template<unsigned WhichOp, uintptr_t N, class T>
innocent_pear_always_inline
T do_inv_op_rept(T x, T y)
{
	switch (WhichOp % 6) {
	    case 0:
		return x - N * y;
	    case 1:
		return x + N * y;
	    case 2:
		return creal(x, cpow<T, (T)N>(y));
	    case 3:
		return crealf(x, cpowf<T, (T)N>(y));
	    case 4:
		return pow<T, std::numeric_limits<T>::max() / 2 + 1 - (T)N>(5)
		    * (x - cpowf<T, (T)N>(1) * y);
	    default:
		return N % 2 ? x ^ y : x;
	}
}

template<class T>
inline constexpr T pick_hi(rand_state_t x)
{
	return sizeof(T) * CHAR_BIT >= 64u ? clip(x) :
	    static_cast<T>(x >> (sizeof(x) * CHAR_BIT - 64u));
}

template<class T>
bool bit_set(T x, unsigned i)
{
	return (x & ((T)1 << i)) != 0;
}

} // innocent_pear::impl

namespace ops
{

enum ops_flags_t
{
    allow_minimal		= 0x00000000u,
    allow_signal_safes		= 0x00000001u,
    allow_signal_unsafes	= 0x00000002u,
    allow_debugger_unsafes	= 0x00000004u,
    allow_resource_unsafes	= 0x00000008u,
    allow_for_startup		= allow_signal_safes |
				  allow_signal_unsafes |
				  allow_debugger_unsafes |
				  allow_resource_unsafes,
    under_munged_terminal	= 0x00000010u,
    under_ptrace		= 0x00000020u,
    under_unpossible		= 0x00000040u
};

} // innocent_pear::ops

using ops::ops_flags_t;

} // innocent_pear

#if defined __amd64__ || defined __i386__
#   ifdef __OPTIMIZE__
#	define innocent_pear_X86_PREFIX(o) \
		".if 0 == %c" #o "; " \
			".byte 0x26; "	/* %es: */ \
		".elseif 1 == %c" #o "; " \
			".byte 0x2e; "	/* %cs: */ \
		".elseif 2 == %c" #o "; " \
			".byte 0x36; "	/* %ss: */ \
		".elseif 3 == %c" #o "; " \
			".byte 0x3e; "	/* %ds: */ \
		".elseif 4 == %c" #o "; " \
			".byte 0x64; "	/* %fs: */ \
		".elseif 5 == %c" #o "; " \
			".byte 0x65; "	/* %gs: */ \
		".endif; "
#	define innocent_pear_X86_BR_PREFIX(o) \
		innocent_pear_X86_PREFIX(o) \
		".if 6 == %c" #o "; " \
			"repz; " \
		".elseif 7 == %c" #o "; " \
			"repnz; " \
		".endif; "
#	ifdef __amd64__
#	    define innocent_pear_X86_PREFIXED_PUSH(o, p, q) \
		innocent_pear_X86_PREFIX(o) \
		".if (%c" #p ")&0x100; " \
			"pushq $((%c" #p ")&0xff)-0x80;" \
			"movq %" #q ", (%%rsp); " \
		".elseif ((%c" #p ")&0xe0)==0; " \
			"pushfq; " \
			"movq %" #q ", (%%rsp); " \
		".else; " \
			"pushq %" #q "; " \
		".endif; "
#	else
#	    define innocent_pear_X86_PREFIXED_PUSH(o, p, q) \
		innocent_pear_X86_PREFIX(o) \
		".if (%c" #p ")&0x100; " \
			"pushl $((%c" #p ")&0xff)-0x80;" \
			"movl %" #q ", (%%esp); " \
		".elseif ((%c" #p ")&0xe0)==0; " \
			"pushfl; " \
			"movl %" #q ", (%%esp); " \
		".else; " \
			"pushl %" #q "; " \
		".endif; "
#	endif
#   else
#	define innocent_pear_X86_PREFIX(o) ""
#	define innocent_pear_X86_BR_PREFIX(o) ""
#	ifdef __amd64__
#	    define innocent_pear_X86_PREFIXED_PUSH(o, p, q) "pushq %" #q "; "
#	else
#	    define innocent_pear_X86_PREFIXED_PUSH(o, p, q) "pushl %" #q "; "
#	endif
#   endif
#elif defined __ia16__
#   ifdef __OPTIMIZE__
#	define innocent_pear_X86_PREFIX(o) \
		".if 0 == %c" #o "; " \
			".byte 0x26; "	/* %es: */ \
		".elseif 1 == %c" #o "; " \
			".byte 0x2e; "	/* %cs: */ \
		".elseif 2 == %c" #o "; " \
			".byte 0x36; "	/* %ss: */ \
		".elseif 3 == %c" #o "; " \
			".byte 0x3e; "	/* %ds: */ \
		".endif; "
#	define innocent_pear_X86_BR_PREFIX(o) \
		innocent_pear_X86_PREFIX(o) \
		".if 6 == %c" #o "; " \
			"repz; " \
		".elseif 7 == %c" #o "; " \
			"repnz; " \
		".endif; "
#   else
#	define innocent_pear_X86_PREFIX(o) ""
#	define innocent_pear_X86_BR_PREFIX(o) ""
#   endif
#endif
#ifndef __ia16__
#   define innocent_pear_ASM_GEN_OUT	"=g"
#   define innocent_pear_ASM_GEN_IN	"g"
#   define innocent_pear_ASM_GEN_MATCH	"0"
#else
#   define innocent_pear_ASM_GEN_OUT	"=r,m"
#   define innocent_pear_ASM_GEN_IN	"r,m"
#   define innocent_pear_ASM_GEN_MATCH	"0,0"
#endif

#endif
