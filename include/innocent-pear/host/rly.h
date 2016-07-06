#ifndef innocent_pear_H_RLY
#define innocent_pear_H_RLY

/* This _must_ match up with yarly.h. */

#include <climits>
#include <innocent-pear/bbq.h>
#include <innocent-pear/nowai.h>

namespace innocent_pear
{

namespace impl
{

template<class T = unsigned, unsigned Levels = 2u>
class rly;  // forward

template<class T, unsigned Levels>
class rly_impl
{
    protected:
	rand_state_t st_, st2_, st12_, new_st_;
	T xd1_, xd2_, xd3_, xd4_, xd5_, xd6_, xd7_, xd8_, xd9_, rvd_;
	rly_impl(rand_state_t st)
	{
		st_ = st;
		st2_ = update_inner(st);
		rand_state_t st3 = update_inner(st2_);
		rand_state_t st4 = update_inner(st3);
		rand_state_t st5 = update_inner(st4);
		rand_state_t st6 = update_inner(st5);
		rand_state_t st7 = update_inner(st6);
		rand_state_t st8 = update_inner(st7);
		rand_state_t st9 = update_inner(st8);
		rand_state_t st10 = update_inner(st9);
		rand_state_t st11 = update_inner(st10);
		st12_ = update_inner(st11);
		new_st_ = update_outer(st12_, Levels);
		xd1_ = pick_hi<T>(st2_ ^ st3);
		xd2_ = pick_hi<T>(st3 ^ st4);
		xd3_ = pick_hi<T>(st4 ^ st5);
		xd4_ = pick_hi<T>(st5 ^ st6);
		xd5_ = pick_hi<T>(st6 ^ st7);
		xd6_ = pick_hi<T>(st7 ^ st8);
		xd7_ = pick_hi<T>(st8 ^ st9);
		xd8_ = pick_hi<T>(st9 ^ st10);
		xd9_ = pick_hi<T>(st10 ^ st11);
		rvd_ = pick_hi<T>(st11 ^ st12_);
	}
};

template<class T>
class rly<T, ~0u> : public nowai
	{ };

template<class T>
class rly<T, 0u> :
    public rly_impl<T, 0u>
{
	typedef rly_impl<T, 0u> super;
    public:
	rly(rand_state_t st) : super(st)
		{ }
	T operator()(T x1 = super::xd1_, T x2 = super::xd2_,
		     T x3 = super::xd3_, T x4 = super::xd4_,
		     T x5 = super::xd5_, T x6 = super::xd6_,
		     T x7 = super::xd7_, T x8 = super::xd8_,
		     T x9 = super::xd9_)
	{
		switch (((super::st_ ^ super::st2_) >> 48) % 16) {
		    case 1:	return x1;
		    case 2:	return x2;
		    case 3:	return x3;
		    case 4:	return x4;
		    case 5:	return x5;
		    case 6:	return x6;
		    case 7:	return x7;
		    case 8:	return x8;
		    case 9:	return x9;
		    default:	return super::rvd_;
		}
	}
};

template<class T, unsigned Levels>
class rly : public rly_impl<T, Levels>
{
	typedef rly_impl<T, Levels> super;
    public:
	rly(rand_state_t st) : super(st)
		{ }
	T operator()(T x1 = super::xd1_, T x2 = super::xd2_,
		     T x3 = super::xd3_, T x4 = super::xd4_,
		     T x5 = super::xd5_, T x6 = super::xd6_,
		     T x7 = super::xd7_, T x8 = super::xd8_,
		     T x9 = super::xd9_)
	{
		T y1 = rly<T, Levels - 1>(super::st12_)
		    (x1, x2, x3, x4, x5, x6, x7, x8, x9);
		T y2 = rly<T, Levels - 1>(super::new_st_)
		    (x1, x2, x3, x4, x5, x6, x7, x8, x9);
		switch (((super::st_ ^ super::st2_) >> 48) % 8) {
		    case 0:	return y1 + y2;
		    case 1:	return y1 - y2;
		    case 2:	return y1 * y2;
		    case 3:	return y1 & y2;
		    case 4:	return y1 | y2;
		    case 5:	return y1 ^ y2;
		    case 6:	return y1 << (y2 % (sizeof(T) * CHAR_BIT));
		    default:	return y1 >> (y2 % (sizeof(T) * CHAR_BIT));
		}
	}
};

} // innocent_pear::impl

using impl::rly;

} // innocent_pear

#endif
