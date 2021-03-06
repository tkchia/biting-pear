#ifndef innocent_pear_H_SRSLY
#define innocent_pear_H_SRSLY

/* This _must_ match up with orly.h and bbq.h. */

#include <cstdio>
#include <cstdlib>
#include <innocent-pear/bbq.h>
#include <innocent-pear/nowai.h>
#include <innocent-pear/host/rly.h>

namespace innocent_pear
{

namespace impl
{

template<class T = unsigned, bool Boreal = true, unsigned Levels = 2u>
class srsly;  // forward

template<class T, bool Boreal, unsigned Levels>
class srsly_impl
{
    protected:
	rand_state_t st_, st12_, new_st_;
	unsigned which_op_;
	T xd0_, xd1_, xd2_, xd3_, xd4_, xd5_, xd6_, xd7_, xd8_, xd9_;
	T do_op(T x, T y)
	{
		switch (which_op_ % 6) {
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
	T do_inv_op(T x, T y)
	{
		switch (which_op_ % 6) {
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
	srsly_impl(rand_state_t st)
	{
		st_ = st;
		rand_state_t st2 = update_inner(st);
		rand_state_t st3 = update_inner(st2);
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
		which_op_ = ((st ^ st2) >> 32) % 8191u;
		xd0_ = pick_hi<T>(st2 ^ st3);
		xd1_ = pick_hi<T>(st3 ^ st4);
		xd2_ = pick_hi<T>(st4 ^ st5);
		xd3_ = pick_hi<T>(st5 ^ st6);
		xd4_ = pick_hi<T>(st6 ^ st7);
		xd5_ = pick_hi<T>(st7 ^ st8);
		xd6_ = pick_hi<T>(st8 ^ st9);
		xd7_ = pick_hi<T>(st9 ^ st10);
		xd8_ = pick_hi<T>(st10 ^ st11);
		xd9_ = pick_hi<T>(st11 ^ st12_);
	}
};

template<class T, bool Boreal>
class srsly<T, Boreal, ~0u> : public nowai
	{ };

template<class T, bool Boreal>
class srsly<T, Boreal, 0u> :
    public srsly_impl<T, Boreal, 0u>
{
	typedef srsly_impl<T, Boreal, 0u> super;
    public:
	srsly(rand_state_t st) : super(st)
		{ }
	T operator()(T x0, T x1, T x2, T x3, T x4, T x5, T x6, T x7, T x8,
		     T x9)
	{
		T y = rly<T>(super::new_st_)
		    (x1, x2, x3, x4, x5, x6, x7, x8, x9);
		if (Boreal)
			return super::do_op(x0, y);
		else	return super::do_inv_op(x0, y);
	}
	T operator()(T x0, T x1, T x2, T x3, T x4, T x5, T x6, T x7, T x8)
	{
		return (*this)(x0, x1, x2, x3, x4, x5, x6, x7, x8,
		    super::xd9_);
	}
	T operator()(T x0, T x1, T x2, T x3, T x4, T x5, T x6, T x7)
	{
		return (*this)(x0, x1, x2, x3, x4, x5, x6, x7, super::xd8_);
	}
	T operator()(T x0, T x1, T x2, T x3, T x4, T x5, T x6)
		{ return (*this)(x0, x1, x2, x3, x4, x5, x6, super::xd7_); }
	T operator()(T x0, T x1, T x2, T x3, T x4, T x5)
		{ return (*this)(x0, x1, x2, x3, x4, x5, super::xd6_); }
	T operator()(T x0, T x1, T x2, T x3, T x4)
		{ return (*this)(x0, x1, x2, x3, x4, super::xd5_); }
	T operator()(T x0, T x1, T x2, T x3)
		{ return (*this)(x0, x1, x2, x3, super::xd4_); }
	T operator()(T x0, T x1, T x2)
		{ return (*this)(x0, x1, x2, super::xd3_); }
	T operator()(T x0, T x1)
		{ return (*this)(x0, x1, super::xd2_); }
	T operator()(T x0)
		{ return (*this)(x0, super::xd1_); }
	T operator()()
		{ return (*this)(super::xd0_); }
};

template<class T, bool Boreal, unsigned Levels>
class srsly : public srsly_impl<T, Boreal, Levels>
{
	typedef srsly_impl<T, Boreal, Levels> super;
	typedef srsly<T, false, Levels> austral;
    public:
	srsly(rand_state_t st) : super(st)
		{ }
	T operator()(T x0, T x1, T x2, T x3, T x4, T x5, T x6, T x7, T x8,
		     T x9)
	{
		T y = rly<T>(super::new_st_)
		    (x1, x2, x3, x4, x5, x6, x7, x8, x9);
		if (Boreal) {
			T z = srsly<T, true, Levels - 1>(super::st12_)
			    (x0, x1, x2, x3, x4, x5, x6, x7, x8, x9);
			return super::do_op(z, y);
		} else {
			T z = super::do_inv_op(x0, y);
			return srsly<T, false, Levels - 1>(super::st12_)
			    (z, x1, x2, x3, x4, x5, x6, x7, x8, x9);
		}
	}
	T operator()(T x0, T x1, T x2, T x3, T x4, T x5, T x6, T x7, T x8)
	{
		return (*this)(x0, x1, x2, x3, x4, x5, x6, x7, x8,
		    super::xd9_);
	}
	T operator()(T x0, T x1, T x2, T x3, T x4, T x5, T x6, T x7)
	{
		return (*this)(x0, x1, x2, x3, x4, x5, x6, x7, super::xd8_);
	}
	T operator()(T x0, T x1, T x2, T x3, T x4, T x5, T x6)
		{ return (*this)(x0, x1, x2, x3, x4, x5, x6, super::xd7_); }
	T operator()(T x0, T x1, T x2, T x3, T x4, T x5)
		{ return (*this)(x0, x1, x2, x3, x4, x5, super::xd6_); }
	T operator()(T x0, T x1, T x2, T x3, T x4)
		{ return (*this)(x0, x1, x2, x3, x4, super::xd5_); }
	T operator()(T x0, T x1, T x2, T x3)
		{ return (*this)(x0, x1, x2, x3, super::xd4_); }
	T operator()(T x0, T x1, T x2)
		{ return (*this)(x0, x1, x2, super::xd3_); }
	T operator()(T x0, T x1)
		{ return (*this)(x0, x1, super::xd2_); }
	T operator()(T x0)
		{ return (*this)(x0, super::xd1_); }
	T operator()()
		{ return (*this)(super::xd0_); }
	void wut(T *p, T *q)
	{
		austral a(this->st_);
		T y0,
		  y1 = a(),
		  y2 = a(y1),
		  y3 = a(y2, y1),
		  y4 = a(y3, y2, y1),
		  y5 = a(y4, y3, y2, y1),
		  y6 = a(y5, y4, y3, y2, y1),
		  y7 = a(y6, y5, y4, y3, y2, y1),
		  y8 = a(y7, y6, y5, y4, y3, y2, y1),
		  y9 = a(y8, y7, y6, y5, y4, y3, y2, y1);
		std::size_t n = q - p;
		if (Boreal) {
			while (n-- != 0) {
				y0 = (*this)(*p, y1, y2, y3, y4,
					     y5, y6, y7, y8, y9);
				y1 = y2;
				y2 = y3;
				y3 = y4;
				y4 = y5;
				y5 = y6;
				y6 = y7;
				y7 = y8;
				y8 = y9;
				*p++ = y9 = y0;
			}
		} else {
			while (n-- != 0) {
				y0 = *p;
				*p++ = (*this)(y0, y1, y2, y3, y4,
					       y5, y6, y7, y8, y9);
				y1 = y2;
				y2 = y3;
				y3 = y4;
				y4 = y5;
				y5 = y6;
				y6 = y7;
				y7 = y8;
				y8 = y9;
				y9 = y0;
			}
		}
	}
};

} // innocent_pear::impl

using impl::srsly;

} // innocent_pear

#endif
