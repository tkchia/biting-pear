#ifndef innocent_pear_H_KTHXBAI
#define innocent_pear_H_KTHXBAI

#include <cinttypes>
#include <climits>
#include <cstdlib>
#include <type_traits>
#include <innocent-pear/bbq.h>
#include <innocent-pear/lolwut.h>
#include <innocent-pear/nowai.h>
#include <innocent-pear/omg.h>
#include <innocent-pear/orly.h>

namespace innocent_pear
{

namespace impl
{

template<impl::rand_state_t State, class T, ops_flags_t Flags,
    unsigned Levels>
class omg;  // forward

template<rand_state_t State, class T, ops_flags_t Flags, unsigned Levels>
class lolwut;  // forward

template<rand_state_t State, class T, bool Boreal, bool BigBad,
    ops_flags_t Flags, unsigned Levels>
class orly;  // forward

template<class T>
bool hi_bit(T x)
{
	return (x & ((T)1 << (sizeof(T) * CHAR_BIT - 1))) != 0;
}

template<rand_state_t State, class T, ops_flags_t Flags, unsigned Levels>
class kthxbai_impl;

template<rand_state_t State, class T, class IntoT, ops_flags_t Flags,
    unsigned Levels,
    unsigned Left = (sizeof(T) + sizeof(IntoT) - 1) / sizeof(IntoT),
    bool Good = (sizeof(T) > sizeof(IntoT))>
struct kthxbai_impl_split;

template<rand_state_t State, class T, ops_flags_t Flags>
class kthxbai_impl<State, T, Flags, ~0u> : public nowai
	{ };

template<rand_state_t State, class T, ops_flags_t Flags>
class kthxbai_impl<State, T, Flags, 0u>
{
    public:
	__attribute__((always_inline))
	kthxbai_impl(T& x, T v)
	{
		__asm __volatile("" : "=g" (x) : "0" (v));
	}
};

template<rand_state_t State, class T, ops_flags_t Flags, unsigned Levels>
class kthxbai_impl
{
	static constexpr rand_state_t
	    State2 = update_inner(State),
	    State3 = update_inner(State2),
	    State4 = update_inner(State3),
	    State5 = update_inner(State4),
	    NewState = update_outer(State, Levels),
	    NewState2 = update_outer(NewState, Levels),
	    NewState3 = update_outer(NewState2, Levels);
	static constexpr bool Boreal1 = (State2 >> 20) % 2 != 0;
	typedef kthxbai_impl<NewState, T, Flags, Levels - 1> impl_n;
	typedef kthxbai_impl<NewState2, T, Flags, Levels - 1> impl_n2;
	typedef kthxbai_impl<0, T, Flags, 0> impl_z;
	typedef omg<NewState, T, Flags, Levels - 1> omg_n;
	typedef omg<NewState2, T, Flags, Levels - 1> omg_n2;
    public:
	__attribute__((always_inline))
	static bool special(T& x, T v)
	{
		return false;
	}
	__attribute__((always_inline))
	kthxbai_impl(T& x, T v)
	{
		switch ((State2 >> 32) % 16) {
		    case 0:
			{
				kthxbai_impl<State3,T,Flags,Levels-1>(x, v);
			}
			break;
		    case 1:
			{
				constexpr unsigned WhichOp =
				    (unsigned)(State3 >> 16);
				T x1, x2;
				constexpr T v2 = pick_hi<T>(State2^NewState);
				T v1 = static_cast<T>(do_op<WhichOp>(v, v2));
				impl_n(x1, v1);
				impl_n2(x2, v2);
				impl_z(x, do_inv_op<WhichOp>(x1, x2));
			}
			break;
		    case 2:
			{
				T x1, x2;
				constexpr T v1 = pick_hi<T>(State2 ^ State3);
				constexpr T v2 = pick_hi<T>(State2^NewState);
				impl_n(x1, v1 & v);
				impl_n2(x2, (~v1 & v) | (v2 & v));
				impl_z(x, x1 | x2);
			}
			break;
		    case 3:
			{
				T x1, x2;
				constexpr T v1 = pick_hi<T>(State2 ^ State3);
				constexpr T v2 = pick_hi<T>(State2^NewState);
				impl_n(x1, v1 | v);
				impl_n2(x2, (~v1 | v) & (v2 | v));
				impl_z(x, x1 & x2);
			}
			break;
		    case 4:
			{
				impl_n(x, v);
				// always false
				if (hi_bit(v) ? !hi_bit(x) : hi_bit(x)) {
					omg_n2 zomg(x);
					__asm __volatile("" : : "g" (&zomg));
				}
			}
			break;
		    case 5:
			{
				constexpr T v1 = pick_hi<T>(NewState);
				impl_n(x, v1);
				// always true
				if (hi_bit(v1) ? hi_bit(x) : !hi_bit(x))
					impl_n2(x, v);
			}
			break;
		    case 6:
			{
				T x1, x2;
				impl_n(x1, v);
				omg_n2 zomg(x2);
				__asm __volatile("" : : "g" (&zomg));
				impl_z(x, x1);
			}
			break;
		    case 7:
			{
				T x1, x2;
				constexpr T v2 =
				    pick_hi<T>(State2 ^ NewState) | 1;
				T v2i = pow(v2);
				T v1 = v * v2i;
				impl_n(x1, v1);
				impl_n2(x2, v2);
				impl_z(x, x1 * x2);
			}
			break;
		    case 8:
			{
				constexpr unsigned WhichOp =
				    (unsigned)(State3 >> 16);
				constexpr T v2 = pick_hi<T>(State ^ State2
				    ^ State3 ^ NewState);
				T x1;
				static T x2 = v2;
				lolwut<NewState, T, Flags, Levels - 1>
				    p(&x2, 3);
				impl_n2(x1, do_op<WhichOp>(v, v2));
				x = do_inv_op<WhichOp>(x1, *p);
			}
			break;
		    case 9:
			{
				constexpr unsigned WhichOp =
				    (unsigned)(State3 >> 16);
				constexpr T v2 = pick_hi<T>(State ^ State2
				    ^ State3 ^ NewState);
				T x1;
				static const T x2 = v2;
				lolwut<NewState, T, Flags, Levels - 1>
				    p((T *)&x2, 3);
				impl_n2(x1, do_op<WhichOp>(v, v2));
				x = do_inv_op<WhichOp>(x1, *p);
			}
			break;
		    case 10:
			{
				T x1, x2;
				omg_n zomg(x1);
				impl_n2(x2, v);
				__asm __volatile(""
				    : "=g" (x2)
				    : "0" (orly<NewState3, T, Boreal1, false,
					       Flags, 1u>()(x2, x1)));
				__asm __volatile(""
				    : "=g" (x)
				    : "0" (orly<NewState3, T, !Boreal1, false,
					       Flags, 1u>()(x2, x1)));
			}
			break;
#ifdef __i386__
		    case 11:
			if (sizeof(T) <= sizeof(unsigned)) {
				unsigned x1, x2;
				constexpr unsigned t =
				    pick_hi<unsigned>(State3 ^ NewState);
				unsigned v2 =
				    (pick_hi<unsigned>(State2 ^ NewState)
					& ~3u) | (v & 3u);
				unsigned v1 = (v & ~3u) |
				    (t & ~(unsigned)(T)~(T)0u) |
				    (t % ((v & 3u) + 1u));
				impl_n(x1, v1);
				impl_n2(x2, v2);
				__asm("arpl %w2, %w0" : "=r,m" (x1)
				    : "0,0" (x1), "r,r" (x2) : "cc");
				x = (T)x1;
				break;
			}
			// else fall through
#endif
		    case 12:
			switch ((State2 >> 48) % 4) {
			    case 3:
				if (sizeof(T) > sizeof(unsigned long)) {
					kthxbai_impl_split<NewState, T,
					    unsigned long, Flags, Levels - 1>
					    (x, v);
					break;
				} // else fall through
			    case 2:
				if (sizeof(T) > sizeof(unsigned)) {
					kthxbai_impl_split<NewState, T,
					    unsigned, Flags, Levels - 1>(x, v);
					break;
				} // else fall through
			    case 1:
				if (sizeof(T) > sizeof(unsigned short)) {
					kthxbai_impl_split<NewState, T,
					    unsigned short, Flags, Levels - 1>
					    (x, v);
					break;
				} // else fall through
			    default:
				if (sizeof(T) > sizeof(unsigned char)) {
					kthxbai_impl_split<NewState, T,
					    unsigned char, Flags, Levels - 1>
					    (x, v);
					break;
				}
			} // fall through
		    case 13:
			if (special(x, v))
				return;
			// else fall through
		    default:
			{
				T x1;
				lolwut<State3, T, Flags, Levels - 1> p1(&x1);
				lolwut<update_outer(State3, Levels), T, Flags,
				    Levels - 1> p2(&x1);
				impl_n(*p1, v);
				impl_z(x, *p2);
			}
			break;
		}
	}
};

template<rand_state_t State, class T, class IntoT, ops_flags_t Flags,
    unsigned Levels, unsigned Left>
struct kthxbai_impl_split<State, T, IntoT, Flags, Levels, Left, false>
{
	// we should never come here...
	__attribute__((always_inline))
	kthxbai_impl_split(T& x, T v)
		{ x = v; }
};

template<rand_state_t State, class T, class IntoT, ops_flags_t Flags,
    unsigned Left>
struct kthxbai_impl_split<State, T, IntoT, Flags, ~0u, Left, true> :
    public nowai
	{ };

template<rand_state_t State, class T, class IntoT, ops_flags_t Flags,
    unsigned Levels>
struct kthxbai_impl_split<State, T, IntoT, Flags, Levels, ~0u, true> :
    public nowai
	{ };

template<rand_state_t State, class T, class IntoT, ops_flags_t Flags,
    unsigned Levels>
struct kthxbai_impl_split<State, T, IntoT, Flags, Levels, 0u, true>
{
	__attribute__((always_inline))
	kthxbai_impl_split(T& x, T v)
		{ x = v; }
};

template<rand_state_t State, class T, class IntoT, ops_flags_t Flags,
    unsigned Levels, unsigned Left>
struct kthxbai_impl_split<State, T, IntoT, Flags, Levels, Left, true>
{
	__attribute__((always_inline))
	kthxbai_impl_split(T& x, T v)
	{
		constexpr rand_state_t
		    NewState = Levels ? update_outer(State, Levels - 1) :
			update_inner(State),
		    NewState2 = update_outer(State, Levels);
		constexpr unsigned Shift = sizeof(IntoT) * CHAR_BIT;
		IntoT y;
		T z;
		kthxbai_impl<NewState, IntoT, Flags, Levels ? Levels - 1 : 0>
		    (y, (IntoT)v);
		kthxbai_impl_split<NewState2, T, IntoT, Flags, Levels,
		    Left - 1>(z, v >> Shift);
		x = (T)y | z << Shift;
	}
};

template<rand_state_t State, class T, ops_flags_t Flags = 0,
    unsigned Levels = 2u>
class kthxbai;

template<rand_state_t State, ops_flags_t Flags, unsigned Levels>
class kthxbai<State, void *, Flags, Levels> :
    public lolwut<State, void, Flags, Levels>
{
    public:
	__attribute__((always_inline))
	kthxbai() : lolwut<State, void, Flags, Levels>()
		{ }
	__attribute__((always_inline))
	kthxbai(void *p, int mode = 0) :
	    lolwut<State, void, Flags, Levels>(p, mode)
		{ }
};

template<rand_state_t State, class RetT, ops_flags_t Flags, unsigned Levels,
    class... ArgT>
class kthxbai<State, RetT (*)(ArgT...), Flags, Levels> :
    public lolwut<State, RetT(ArgT...), Flags, Levels>
{
	typedef RetT func_type(ArgT...);
    public:
	__attribute__((always_inline))
	kthxbai() : lolwut<State, func_type, Flags, Levels>()
		{ }
	__attribute__((always_inline))
	kthxbai(func_type *p, int mode = 2) :
	    lolwut<State, func_type, Flags, Levels>(p, mode)
		{ }
};

template<rand_state_t State, class RetT, ops_flags_t Flags, unsigned Levels,
    class... ArgT>
class kthxbai<State, RetT (*)(ArgT..., ...), Flags, Levels> :
    public lolwut<State, RetT(ArgT..., ...), Flags, Levels>
{
	typedef RetT func_type(ArgT..., ...);
    public:
	__attribute__((always_inline))
	kthxbai() : lolwut<State, func_type, Flags, Levels>()
		{ }
	__attribute__((always_inline))
	kthxbai(func_type *p, int mode = 2) :
	    lolwut<State, func_type, Flags, Levels>(p, mode)
		{ }
};

template<rand_state_t State, class S, ops_flags_t Flags, unsigned Levels>
class kthxbai<State, S *, Flags, Levels> :
    public lolwut<State, S, Flags, Levels>
{
	typedef kthxbai<State, S *, Flags, Levels> our_type;
    public:
	__attribute__((always_inline))
	kthxbai() : lolwut<State, S, Flags, Levels>()
		{ }
	__attribute__((always_inline))
	kthxbai(S *p, int mode = 0) : lolwut<State, S, Flags, Levels>(p, mode)
		{ }
	__attribute__((always_inline))
	const our_type& operator+=(std::ptrdiff_t n)
	{
		this->advance_chars(n * sizeof(S));
		return *this;
	}
	__attribute__((always_inline))
	const our_type& operator-=(std::ptrdiff_t n)
	{
		this->advance_chars(-n * sizeof(S));
		return *this;
	}
	__attribute__((always_inline))
	const our_type& operator++()
		{ return *this += 1; }
	const our_type& operator--()
		{ return *this -= 1; }
};

template<rand_state_t State, class T, ops_flags_t Flags, unsigned Levels>
class kthxbai
{
	static_assert(std::is_integral<T>::value,
	    "T in innocent_pear::kthxbai<, T, ...> is not an integral type");
	static_assert(std::is_unsigned<T>::value,
	    "T in innocent_pear::kthxbai<, T, ...> is not an unsigned type");
	static_assert(sizeof(T) <= sizeof(rand_state_t),
	    "T in innocent_pear::kthxbai<, T, ...> is larger than "
	    "innocent_pear::impl::rand_state_t");
	static constexpr rand_state_t State2 = update_inner(State);
	static constexpr rand_state_t State3 = update_inner(State2);
	static constexpr rand_state_t State4 = update_inner(State3);
	static constexpr unsigned WhichOp =
	    (unsigned)((State2 ^ State3) >> 32);
	static constexpr T Disp = pick_hi<T>(State3 ^ State4);
	T x_;
    public:
	__attribute__((always_inline))
	kthxbai()
		{ }
	__attribute__((always_inline))
	kthxbai(T v)
	{
		kthxbai_impl<State4, T, Flags, Levels>(x_,
		    do_op<WhichOp>(v, Disp));
	}
	__attribute__((always_inline))
	const kthxbai& operator=(T v)
	{
		kthxbai_impl<State4, T, Flags, Levels>(x_,
		    do_op<WhichOp>(v, Disp));
		return *this;
	}
	__attribute__((always_inline))
	operator T() const
		{ return do_inv_op<WhichOp>(x_, Disp); }
};

} // innocent_pear::impl

using impl::kthxbai;

} // innocent_pear

#endif
