#ifndef biting_pear_H_KTHXBAI
#define biting_pear_H_KTHXBAI

#include <cinttypes>
#include <climits>
#include <biting-pear/bbq.h>
#include <biting-pear/lolwut.h>
#include <biting-pear/omg.h>

namespace biting_pear
{

template<uint_least64_t Seed, class T, unsigned Levels>
struct omg;  // forward

template<uint_least64_t Seed, class T, unsigned Levels>
struct lolwut;  // forward

namespace impl
{

template<class T>
bool hi_bit(T x)
{
	return (x & 1 << (sizeof(T) * CHAR_BIT - 1)) != 0;
}

template<uint_least64_t Seed, class T, unsigned Levels>
struct kthxbai_impl;

template<uint_least64_t Seed, class T>
struct kthxbai_impl<Seed, T, 0u>
{
	__attribute__((always_inline))
	kthxbai_impl(T& x, T v)
	{
		__asm __volatile("" : "=g" (x) : "0" (v));
	}
};

template<uint_least64_t Seed, class T, unsigned Levels>
struct kthxbai_impl
{
	__attribute__((always_inline))
	kthxbai_impl(T& x, T v)
	{
		constexpr uint_least64_t Seed2 = update_inner(Seed);
		constexpr uint_least64_t Seed3 = update_inner(Seed2);
		constexpr uint_least64_t NewSeed = update_outer(Seed);
		switch ((Seed2 >> 32) % 16) {
		    case 0:
			{
				kthxbai_impl<Seed3, T, Levels - 1>(x, v);
			}
			break;
		    case 1:
			{
				constexpr unsigned WhichOp =
				    (unsigned)(Seed3 >> 16);
				T x1, x2;
				constexpr T v2 = pick_hi<T>(Seed2 ^ NewSeed);
				T v1 = static_cast<T>(do_op<WhichOp>(v, v2));
				kthxbai_impl<Seed3, T, Levels - 1>(x1, v1);
				kthxbai_impl<NewSeed, T, Levels - 1>(x2, v2);
				kthxbai_impl<0, T, 0>(x,
				    do_inv_op<WhichOp>(x1, x2));
			}
			break;
		    case 2:
			{
				T x1, x2;
				constexpr T v1 = pick_hi<T>(Seed2 ^ Seed3);
				constexpr T v2 = pick_hi<T>(Seed2 ^ NewSeed);
				kthxbai_impl<Seed3, T, Levels - 1>(x1,
				    v1 & v);
				kthxbai_impl<NewSeed, T, Levels - 1>(x2,
				    (~v1 & v) | (v2 & v));
				kthxbai_impl<0, T, 0>(x, x1 | x2);
			}
			break;
		    case 3:
			{
				T x1, x2;
				constexpr T v1 = pick_hi<T>(Seed2 ^ Seed3);
				constexpr T v2 = pick_hi<T>(Seed2 ^ NewSeed);
				kthxbai_impl<Seed3, T, Levels - 1>(x1,
				    v1 | v);
				kthxbai_impl<NewSeed, T, Levels - 1>(x2,
				    (~v1 | v) & (v2 | v));
				kthxbai_impl<0, T, 0>(x, x1 & x2);
			}
			break;
		    case 4:
			{
				kthxbai_impl<Seed3, T, Levels - 1>(x, v);
				// always false
				if (hi_bit(v) ? !hi_bit(x) : hi_bit(x))
					omg<NewSeed, T, Levels - 1>
					    zomg(x);
			}
			break;
		    case 5:
			{
				constexpr T v1 = pick_hi<T>(NewSeed);
				kthxbai_impl<Seed3, T, Levels - 1>(x, v1);
				// always true
				if (hi_bit(v1) ? hi_bit(x) : !hi_bit(x))
					kthxbai_impl<NewSeed, T, Levels - 1>
					    (x, v);
			}
			break;
		    case 6:
			{
				T x1, x2;
				kthxbai_impl<Seed3, T, Levels - 1>(x1, v);
				omg<NewSeed, T, Levels - 1> zomg(x2);
				kthxbai_impl<0, T, 0>(x, x1);
			}
			break;
		    default:
			{
				T x1;
				lolwut<Seed3, T, Levels - 1> p1 = &x1;
				lolwut<update_outer(Seed3), T, Levels - 1>
				    p2 = &x1;
				kthxbai_impl<NewSeed, T, Levels - 1>(*p1, v);
				kthxbai_impl<0, T, 0>(x, *p2);
			}
			break;
		}
	}
};

} // biting_pear::impl

template<uint_least64_t Seed, class T, unsigned Levels = 6u>
class kthxbai;

template<uint_least64_t Seed, class S, unsigned Levels>
class kthxbai<Seed, S *, Levels> : public impl::lolwut<Seed, S, Levels>
{
    public:
	__attribute__((always_inline))
	kthxbai() : impl::lolwut<Seed, S, Levels>()
		{ }
	__attribute__((always_inline))
	kthxbai(S *p, int mode = 0) : impl::lolwut<Seed, S, Levels>(p, mode)
		{ }
};

template<uint_least64_t Seed, class T, unsigned Levels>
class kthxbai
{
	static constexpr uint_least64_t Seed2 = impl::update_inner(Seed);
	static constexpr uint_least64_t Seed3 = impl::update_inner(Seed2);
	static constexpr T Disp = impl::pick_hi<T>(Seed2 ^ Seed3);
	T x_;
    public:
	__attribute__((always_inline))
	kthxbai()
		{ }
	__attribute__((always_inline))
	kthxbai(T v)
	{
		impl::kthxbai_impl<Seed3, T, Levels>(x_, v + Disp);
	}
	__attribute__((always_inline))
	const kthxbai& operator=(T v)
	{
		impl::kthxbai_impl<Seed3, T, Levels>(x_, v + Disp);
		return *this;
	}
	__attribute__((always_inline))
	operator T() const
		{ return x_ - Disp; }
};

} // biting_pear

#endif
