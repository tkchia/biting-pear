#ifndef biting_pear_H_KTHXBAI
#define biting_pear_H_KTHXBAI

#include <cinttypes>
#include <climits>
#include <biting-pear/bbq.h>
#include <biting-pear/lolwut.h>
#include <biting-pear/omg.h>

namespace biting_pear
{

template<impl::rand_state_t State, class T, unsigned Levels>
struct omg;  // forward

template<impl::rand_state_t State, class T, unsigned Levels>
struct lolwut;  // forward

namespace impl
{

template<class T>
bool hi_bit(T x)
{
	return (x & 1 << (sizeof(T) * CHAR_BIT - 1)) != 0;
}

template<rand_state_t State, class T, unsigned Levels>
struct kthxbai_impl;

template<rand_state_t State, class T>
struct kthxbai_impl<State, T, 0u>
{
	__attribute__((always_inline))
	kthxbai_impl(T& x, T v)
	{
		__asm __volatile("" : "=g" (x) : "0" (v));
	}
};

template<rand_state_t State, class T, unsigned Levels>
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
				kthxbai_impl<State3, T, Levels - 1>(x, v);
			}
			break;
		    case 1:
			{
				constexpr unsigned WhichOp =
				    (unsigned)(State3 >> 16);
				T x1, x2;
				constexpr T v2 = pick_hi<T>(State2 ^ NewState);
				T v1 = static_cast<T>(do_op<WhichOp>(v, v2));
				kthxbai_impl<State3, T, Levels - 1>(x1, v1);
				kthxbai_impl<NewState, T, Levels - 1>(x2, v2);
				kthxbai_impl<0, T, 0>(x,
				    do_inv_op<WhichOp>(x1, x2));
			}
			break;
		    case 2:
			{
				T x1, x2;
				constexpr T v1 = pick_hi<T>(State2 ^ State3);
				constexpr T v2 = pick_hi<T>(State2 ^ NewState);
				kthxbai_impl<State3, T, Levels - 1>(x1,
				    v1 & v);
				kthxbai_impl<NewState, T, Levels - 1>(x2,
				    (~v1 & v) | (v2 & v));
				kthxbai_impl<0, T, 0>(x, x1 | x2);
			}
			break;
		    case 3:
			{
				T x1, x2;
				constexpr T v1 = pick_hi<T>(State2 ^ State3);
				constexpr T v2 = pick_hi<T>(State2 ^ NewState);
				kthxbai_impl<State3, T, Levels - 1>(x1,
				    v1 | v);
				kthxbai_impl<NewState, T, Levels - 1>(x2,
				    (~v1 | v) & (v2 | v));
				kthxbai_impl<0, T, 0>(x, x1 & x2);
			}
			break;
		    case 4:
			{
				kthxbai_impl<State3, T, Levels - 1>(x, v);
				// always false
				if (hi_bit(v) ? !hi_bit(x) : hi_bit(x))
					omg<NewState, T, Levels - 1>
					    zomg(x);
			}
			break;
		    case 5:
			{
				constexpr T v1 = pick_hi<T>(NewState);
				kthxbai_impl<State3, T, Levels - 1>(x, v1);
				// always true
				if (hi_bit(v1) ? hi_bit(x) : !hi_bit(x))
					kthxbai_impl<NewState, T, Levels - 1>
					    (x, v);
			}
			break;
		    case 6:
			{
				T x1, x2;
				kthxbai_impl<State3, T, Levels - 1>(x1, v);
				omg<NewState, T, Levels - 1> zomg(x2);
				kthxbai_impl<0, T, 0>(x, x1);
			}
			break;
		    default:
			{
				T x1;
				lolwut<State3, T, Levels - 1> p1 = &x1;
				lolwut<update_outer(State3), T, Levels - 1>
				    p2 = &x1;
				kthxbai_impl<NewState, T, Levels - 1>(*p1, v);
				kthxbai_impl<0, T, 0>(x, *p2);
			}
			break;
		}
	}
};

} // biting_pear::impl

template<impl::rand_state_t State, class T, unsigned Levels = 6u>
class kthxbai;

template<impl::rand_state_t State, class S, unsigned Levels>
class kthxbai<State, S *, Levels> : public impl::lolwut<State, S, Levels>
{
    public:
	__attribute__((always_inline))
	kthxbai() : impl::lolwut<State, S, Levels>()
		{ }
	__attribute__((always_inline))
	kthxbai(S *p, int mode = 0) : impl::lolwut<State, S, Levels>(p, mode)
		{ }
};

template<impl::rand_state_t State, class T, unsigned Levels>
class kthxbai
{
	static constexpr impl::rand_state_t State2 =
	    impl::update_inner(State);
	static constexpr impl::rand_state_t State3 =
	    impl::update_inner(State2);
	static constexpr T Disp = impl::pick_hi<T>(State2 ^ State3);
	T x_;
    public:
	__attribute__((always_inline))
	kthxbai()
		{ }
	__attribute__((always_inline))
	kthxbai(T v)
	{
		impl::kthxbai_impl<State3, T, Levels>(x_, v + Disp);
	}
	__attribute__((always_inline))
	const kthxbai& operator=(T v)
	{
		impl::kthxbai_impl<State3, T, Levels>(x_, v + Disp);
		return *this;
	}
	__attribute__((always_inline))
	operator T() const
		{ return x_ - Disp; }
};

} // biting_pear

#endif
