#ifndef biting_pear_H_KTHXBAI
#define biting_pear_H_KTHXBAI

#include <cinttypes>
#include <climits>
#include <cstdlib>
#include <biting-pear/bbq.h>
#include <biting-pear/lolwut.h>
#include <biting-pear/nowai.h>
#include <biting-pear/omg.h>

namespace biting_pear
{

template<impl::rand_state_t State, class T, impl::ops_flags_t Flags,
    unsigned Levels>
struct omg;  // forward

template<impl::rand_state_t State, class T, impl::ops_flags_t Flags,
    unsigned Levels>
struct lolwut;  // forward

namespace impl
{

template<class T>
bool hi_bit(T x)
{
	return (x & 1 << (sizeof(T) * CHAR_BIT - 1)) != 0;
}

template<rand_state_t State, class T, ops_flags_t Flags, unsigned Levels>
struct kthxbai_impl;

template<rand_state_t State, class T, ops_flags_t Flags>
struct kthxbai_impl<State, T, Flags, ~0u> : public nowai
	{ };

template<rand_state_t State, class T, ops_flags_t Flags>
struct kthxbai_impl<State, T, Flags, 0u>
{
	__attribute__((always_inline))
	kthxbai_impl(T& x, T v)
	{
		__asm __volatile("" : "=g" (x) : "0" (v));
	}
};

template<rand_state_t State, class T, ops_flags_t Flags, unsigned Levels>
struct kthxbai_impl
{
	__attribute__((always_inline))
	kthxbai_impl(T& x, T v)
	{
		constexpr rand_state_t State2 = update_inner(State);
		constexpr rand_state_t State3 = update_inner(State2);
		constexpr rand_state_t NewState = update_outer(State);
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
				kthxbai_impl<State3, T, Flags, Levels - 1>
				    (x1, v1);
				kthxbai_impl<NewState, T, Flags, Levels - 1>
				    (x2, v2);
				kthxbai_impl<0, T, Flags, 0>(x,
				    do_inv_op<WhichOp>(x1, x2));
			}
			break;
		    case 2:
			{
				T x1, x2;
				constexpr T v1 = pick_hi<T>(State2 ^ State3);
				constexpr T v2 = pick_hi<T>(State2^NewState);
				kthxbai_impl<State3, T, Flags, Levels - 1>(x1,
				    v1 & v);
				kthxbai_impl<NewState, T, Flags, Levels - 1>
				    (x2, (~v1 & v) | (v2 & v));
				kthxbai_impl<0, T, Flags, 0>(x, x1 | x2);
			}
			break;
		    case 3:
			{
				T x1, x2;
				constexpr T v1 = pick_hi<T>(State2 ^ State3);
				constexpr T v2 = pick_hi<T>(State2^NewState);
				kthxbai_impl<State3, T, Flags, Levels - 1>
				    (x1, v1 | v);
				kthxbai_impl<NewState, T, Flags, Levels - 1>
				    (x2, (~v1 | v) & (v2 | v));
				kthxbai_impl<0, T, Flags, 0>(x, x1 & x2);
			}
			break;
		    case 4:
			{
				kthxbai_impl<State3, T, Flags, Levels - 1>
				    (x, v);
				// always false
				if (hi_bit(v) ? !hi_bit(x) : hi_bit(x)) {
					omg<NewState, T, Flags, Levels - 1>
					    zomg(x);
					__asm __volatile("" : : "g" (&zomg));
				}
			}
			break;
		    case 5:
			{
				constexpr T v1 = pick_hi<T>(NewState);
				kthxbai_impl<State3, T, Flags, Levels - 1>
				    (x, v1);
				// always true
				if (hi_bit(v1) ? hi_bit(x) : !hi_bit(x))
					kthxbai_impl<NewState, T, Flags,
					    Levels - 1>(x, v);
			}
			break;
		    case 6:
			{
				T x1, x2;
				kthxbai_impl<State3, T, Flags, Levels - 1>
				    (x1, v);
				omg<NewState, T, Flags, Levels - 1> zomg(x2);
				__asm __volatile("" : : "g" (&zomg));
				kthxbai_impl<0, T, Flags, 0>(x, x1);
			}
			break;
		    case 7:
			{
				T x1, x2;
				constexpr T v2 =
				    pick_hi<T>(State2 ^ NewState) | 1;
				constexpr T v2i = pow(v2);
				T v1 = v * v2i;
				kthxbai_impl<State3, T, Flags, Levels - 1>
				    (x1, v1);
				kthxbai_impl<NewState, T, Flags, Levels - 1>
				    (x2, v2);
				kthxbai_impl<0, T, Flags, 0>(x, x1 * x2);
			}
			break;
		    default:
			{
				T x1;
				lolwut<State3, T, Flags, Levels - 1> p1 = &x1;
				lolwut<update_outer(State3), T, Flags,
				    Levels - 1> p2 = &x1;
				kthxbai_impl<NewState, T, Flags, Levels - 1>
				    (*p1, v);
				kthxbai_impl<0, T, Flags, 0>(x, *p2);
			}
			break;
		}
	}
};

template<rand_state_t State, class T, ops_flags_t Flags = 0,
    unsigned Levels = 5u>
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

#if __cplusplus >= 201103L
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
#endif

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
	static constexpr rand_state_t State2 = update_inner(State);
	static constexpr rand_state_t State3 = update_inner(State2);
	static constexpr T Disp = pick_hi<T>(State2 ^ State3);
	T x_;
    public:
	__attribute__((always_inline))
	kthxbai()
		{ }
	__attribute__((always_inline))
	kthxbai(T v)
	{
		kthxbai_impl<State3, T, Flags, Levels>(x_, v + Disp);
	}
	__attribute__((always_inline))
	const kthxbai& operator=(T v)
	{
		kthxbai_impl<State3, T, Flags, Levels>(x_, v + Disp);
		return *this;
	}
	__attribute__((always_inline))
	operator T() const
		{ return x_ - Disp; }
};

} // biting_pear::impl

using impl::kthxbai;

} // biting_pear

#endif
