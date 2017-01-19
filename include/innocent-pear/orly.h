#ifndef innocent_pear_H_ORLY
#define innocent_pear_H_ORLY

/* This _must_ match up with host/srsly.h. */

#include <innocent-pear/bbq.h>
#include <innocent-pear/nowai.h>
#include <innocent-pear/yarly.h>
#ifdef innocent_pear_DEBUG
#   include <cstdio>
#endif

namespace innocent_pear
{

namespace impl
{

template<rand_state_t State, class T = unsigned, bool Boreal = true,
    bool BigBad = false,
    ops_flags_t Flags = innocent_pear::ops::allow_minimal,
    unsigned Levels = 2u>
class orly;  // forward

template<rand_state_t State, class T, bool Boreal, bool BigBad,
    ops_flags_t Flags, unsigned Levels>
class orly_impl
{
    protected:
	static constexpr rand_state_t
	    State2  = update_inner(State),  State3  = update_inner(State2),
	    State4  = update_inner(State3), State5  = update_inner(State4),
	    State6  = update_inner(State5), State7  = update_inner(State6),
	    State8  = update_inner(State7), State9  = update_inner(State8),
	    State10 = update_inner(State9), State11 = update_inner(State10),
	    State12 = update_inner(State11),
	    NewState = update_outer(State12, Levels);
	static constexpr unsigned WhichOp = pick_hi<unsigned>(State ^ State2);
	static constexpr unsigned TaintOp = pick_hi<unsigned>(State ^ State12);
	static constexpr T DefX0 = pick_hi<T>(State2  ^ State3),
			   DefX1 = pick_hi<T>(State3  ^ State4),
			   DefX2 = pick_hi<T>(State4  ^ State5),
			   DefX3 = pick_hi<T>(State5  ^ State6),
			   DefX4 = pick_hi<T>(State6  ^ State7),
			   DefX5 = pick_hi<T>(State7  ^ State8),
			   DefX6 = pick_hi<T>(State8  ^ State9),
			   DefX7 = pick_hi<T>(State9  ^ State10),
			   DefX8 = pick_hi<T>(State10 ^ State11),
			   DefX9 = pick_hi<T>(State11 ^ State12);
    public:
	typedef orly<State, T, !Boreal, BigBad, Flags, Levels> inv;
	typedef orly<State, T, Boreal, true, Flags, Levels> bad;
	typedef orly<State, T, Boreal, false, Flags, Levels> unbad;
};

template<rand_state_t State, class T, bool Boreal, bool BigBad,
    ops_flags_t Flags>
class orly<State, T, Boreal, BigBad, Flags, ~0u> : public nowai
	{ };

template<rand_state_t State, class T, bool Boreal, bool BigBad,
    ops_flags_t Flags>
class orly<State, T, Boreal, BigBad, Flags, 0u> :
    public orly_impl<State, T, Boreal, BigBad, Flags, 0u>
{
	typedef orly_impl<State, T, Boreal, BigBad, Flags, 0u> super;
    public:
	innocent_pear_always_inline
	T operator()(T x0 = super::DefX0,
		     T x1 = super::DefX1, T x2 = super::DefX2,
		     T x3 = super::DefX3, T x4 = super::DefX4,
		     T x5 = super::DefX5, T x6 = super::DefX6,
		     T x7 = super::DefX7, T x8 = super::DefX8,
		     T x9 = super::DefX9)
	{
		T y = yarly<super::NewState, T, BigBad, Flags>()
		    (x1, x2, x3, x4, x5, x6, x7, x8, x9);
		if (Boreal)
			return do_op<super::WhichOp>(x0, y);
		else	return do_inv_op<super::WhichOp>(x0, y);
	}
};

template<rand_state_t State, class T, bool Boreal, bool BigBad,
    ops_flags_t Flags, unsigned Levels>
class orly : public orly_impl<State, T, Boreal, BigBad, Flags, Levels>
{
	typedef orly_impl<State, T, Boreal, BigBad, Flags, Levels> super;
	typedef orly<State, T, false, BigBad, Flags, Levels> austral;
	class woot
	{
		T *o_;
	    public:
		innocent_pear_always_inline
		woot(T *o) : o_(o)
			{ }
		innocent_pear_always_inline
		void operator()(T i, T *p)
			{ *o_++ = i; }
	};
    public:
	innocent_pear_always_inline
	T operator()(T x0 = super::DefX0,
		     T x1 = super::DefX1, T x2 = super::DefX2,
		     T x3 = super::DefX3, T x4 = super::DefX4,
		     T x5 = super::DefX5, T x6 = super::DefX6,
		     T x7 = super::DefX7, T x8 = super::DefX8,
		     T x9 = super::DefX9)
	{
		T y = yarly<super::NewState, T, BigBad, Flags>()
		    (x1, x2, x3, x4, x5, x6, x7, x8, x9);
		if (BigBad) {
			y = do_op<super::TaintOp>(y, x0);
			y = do_inv_op<super::TaintOp>(y, x0);
		}
		if (Boreal) {
			T z = orly<super::State12, T, true, BigBad,
			    Flags, Levels - 1>()
			    (x0, x1, x2, x3, x4, x5, x6, x7, x8, x9);
			return do_op<super::WhichOp>(z, y);
		} else {
			T z = do_inv_op<super::WhichOp>(x0, y);
			return orly<super::State12, T, false, BigBad,
			    Flags, Levels - 1>()
			    (z, x1, x2, x3, x4, x5, x6, x7, x8, x9);
		}
	}
	template<class C>
	innocent_pear_always_inline
	void wot(T *p, T *q, C& c)
	{
		T y0,
		  y1 = austral()(),
		  y2 = austral()(y1),
		  y3 = austral()(y2, y1),
		  y4 = austral()(y3, y2, y1),
		  y5 = austral()(y4, y3, y2, y1),
		  y6 = austral()(y5, y4, y3, y2, y1),
		  y7 = austral()(y6, y5, y4, y3, y2, y1),
		  y8 = austral()(y7, y6, y5, y4, y3, y2, y1),
		  y9 = austral()(y8, y7, y6, y5, y4, y3, y2, y1);
		/*
		 * Prevent g++'s alias analysis from assuming that p != q at
		 * the outset -- if the precise distance between p and q is
		 * not already known.
		 */
		if (!__builtin_constant_p(q - p))
			__asm __volatile("" : "=g" (p), "=g" (q)
					    : "0" (p), "1" (q));
		std::size_t n = q - p;
		if (Boreal) {
			while (n >= 10) {
				y0 = (*this)(*p, y1, y2, y3, y4,
					     y5, y6, y7, y8, y9);
				c(y0, p++);
				y1 = (*this)(*p, y2, y3, y4, y5,
					     y6, y7, y8, y9, y0);
				c(y1, p++);
				y2 = (*this)(*p, y3, y4, y5, y6,
					     y7, y8, y9, y0, y1);
				c(y2, p++);
				y3 = (*this)(*p, y4, y5, y6, y7,
					     y8, y9, y0, y1, y2);
				c(y3, p++);
				y4 = (*this)(*p, y5, y6, y7, y8,
					     y9, y0, y1, y2, y3);
				c(y4, p++);
				y5 = (*this)(*p, y6, y7, y8, y9,
					     y0, y1, y2, y3, y4);
				c(y5, p++);
				y6 = (*this)(*p, y7, y8, y9, y0,
					     y1, y2, y3, y4, y5);
				c(y6, p++);
				y7 = (*this)(*p, y8, y9, y0, y1,
					     y2, y3, y4, y5, y6);
				c(y7, p++);
				y8 = (*this)(*p, y9, y0, y1, y2,
					     y3, y4, y5, y6, y7);
				c(y8, p++);
				y9 = (*this)(*p, y0, y1, y2, y3,
					     y4, y5, y6, y7, y8);
				c(y9, p++);
				n -= 10;
			}
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
				y9 = y0;
				c(y9, p++);
			}
		} else {
			while (n >= 10) {
				y0 = *p;
				c((*this)(y0, y1, y2, y3, y4,
					  y5, y6, y7, y8, y9), p++);
				y1 = *p;
				c((*this)(y1, y2, y3, y4, y5,
					  y6, y7, y8, y9, y0), p++);
				y2 = *p;
				c((*this)(y2, y3, y4, y5, y6,
					  y7, y8, y9, y0, y1), p++);
				y3 = *p;
				c((*this)(y3, y4, y5, y6, y7,
					  y8, y9, y0, y1, y2), p++);
				y4 = *p;
				c((*this)(y4, y5, y6, y7, y8,
					  y9, y0, y1, y2, y3), p++);
				y5 = *p;
				c((*this)(y5, y6, y7, y8, y9,
					  y0, y1, y2, y3, y4), p++);
				y6 = *p;
				c((*this)(y6, y7, y8, y9, y0,
					  y1, y2, y3, y4, y5), p++);
				y7 = *p;
				c((*this)(y7, y8, y9, y0, y1,
					  y2, y3, y4, y5, y6), p++);
				y8 = *p;
				c((*this)(y8, y9, y0, y1, y2,
					  y3, y4, y5, y6, y7), p++);
				y9 = *p;
				c((*this)(y9, y0, y1, y2, y3,
					  y4, y5, y6, y7, y8), p++);
				n -= 10;
			}
			while (n-- != 0) {
				y0 = *p;
				c((*this)(y0, y1, y2, y3, y4,
					  y5, y6, y7, y8, y9), p++);
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
	innocent_pear_always_inline
	void wut(T *p, T *q, T *r)
	{
#ifdef innocent_pear_DEBUG
		std::fprintf(stderr, "orly<...>::wut(%p, %p, %p)\n", p, q, r);
#endif
		woot w(r);
		wot(p, q, w);
	}
	innocent_pear_always_inline
	void wut(T *p, T *q)
		{ wut(p, q, p); }
	template<class DT>
	innocent_pear_always_inline
	T wat(const DT *p, const DT *q)
	{
		static_assert(std::is_integral<DT>::value,
		    "DT in innocent_pear::orly<, T, ...>::wat(const DT *, "
		    "...) is not an integral type");
		static_assert(std::is_unsigned<DT>::value,
		    "DT in innocent_pear::orly<, T, ...>::wat(const DT *, "
		    "...) is not an unsigned type");
		T x0,
		  x1 = (*this)(),
		  x2 = (*this)(x1),
		  x3 = (*this)(x2, x1),
		  x4 = (*this)(x3, x2, x1),
		  x5 = (*this)(x4, x3, x2, x1),
		  x6 = (*this)(x5, x4, x3, x2, x1),
		  x7 = (*this)(x6, x5, x4, x3, x2, x1),
		  x8 = (*this)(x7, x6, x5, x4, x3, x2, x1),
		  x9 = (*this)(x8, x7, x6, x5, x4, x3, x2, x1);
		if (!__builtin_constant_p(q - p))
			__asm __volatile("" : "=g" (p), "=g" (q)
					    : "0" (p), "1" (q));
		std::size_t n = q - p;
		while (n >= 10) {
			x0 = (*this)((T)*p++, x1, x2, x3, x4,
					  x5, x6, x7, x8, x9);
			x1 = (*this)((T)*p++, x2, x3, x4, x5,
					  x6, x7, x8, x9, x0);
			x2 = (*this)((T)*p++, x3, x4, x5, x6,
					  x7, x8, x9, x0, x1);
			x3 = (*this)((T)*p++, x4, x5, x6, x7,
					  x8, x9, x0, x1, x2);
			x4 = (*this)((T)*p++, x5, x6, x7, x8,
					  x9, x0, x1, x2, x3);
			x5 = (*this)((T)*p++, x6, x7, x8, x9,
					  x0, x1, x2, x3, x4);
			x6 = (*this)((T)*p++, x7, x8, x9, x0,
					  x1, x2, x3, x4, x5);
			x7 = (*this)((T)*p++, x8, x9, x0, x1,
					  x2, x3, x4, x5, x6);
			x8 = (*this)((T)*p++, x9, x0, x1, x2,
					  x3, x4, x5, x6, x7);
			x9 = (*this)((T)*p++, x0, x1, x2, x3,
					  x4, x5, x6, x7, x8);
			n -= 10;
		}
		while (n-- != 0) {
			x0 = (*this)((T)*p++, x1, x2, x3, x4,
					  x5, x6, x7, x8, x9);
			x1 = x2;
			x2 = x3;
			x3 = x4;
			x4 = x5;
			x5 = x6;
			x6 = x7;
			x7 = x8;
			x8 = x9;
			x9 = x0;
		}
		return x9;
	}
	innocent_pear_always_inline
	void zot(T *p, T *q)
	{
		T x0,
		  x1 = (*this)(),
		  x2 = (*this)(x1),
		  x3 = (*this)(x2, x1),
		  x4 = (*this)(x3, x2, x1),
		  x5 = (*this)(x4, x3, x2, x1),
		  x6 = (*this)(x5, x4, x3, x2, x1),
		  x7 = (*this)(x6, x5, x4, x3, x2, x1),
		  x8 = (*this)(x7, x6, x5, x4, x3, x2, x1),
		  x9 = (*this)(x8, x7, x6, x5, x4, x3, x2, x1);
		if (!__builtin_constant_p(q - p))
			__asm __volatile("" : "=g" (p), "=g" (q)
					    : "0" (p), "1" (q));
		T *r = p;
		std::size_t n = q - p;
		while (n-- != 0) {
			x0 = (*this)((T)n, x1, x2, x3, x4,
				       x5, x6, x7, x8, x9);
			*r++ = x0;
			x1 = x2;
			x2 = x3;
			x3 = x4;
			x4 = x5;
			x5 = x6;
			x6 = x7;
			x7 = x8;
			x8 = x9;
			x9 = x0;
		}
		__asm __volatile("" : : "g" (p) : "memory");
	}
};

} // innocent_pear::impl

using impl::orly;

} // innocent_pear

#endif
