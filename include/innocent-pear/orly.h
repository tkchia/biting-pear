#ifndef innocent_pear_H_ORLY
#define innocent_pear_H_ORLY

#include <innocent-pear/bbq.h>
#include <innocent-pear/nowai.h>
#include <innocent-pear/yarly.h>

namespace innocent_pear
{

namespace impl
{

template<rand_state_t State, class T = unsigned, bool Boreal = true,
    bool BigBad = false, ops_flags_t Flags = 0, unsigned Levels = 2u>
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
	__attribute__((always_inline))
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
    public:
	__attribute__((always_inline))
	T operator()(T x0 = super::DefX0,
		     T x1 = super::DefX1, T x2 = super::DefX2,
		     T x3 = super::DefX3, T x4 = super::DefX4,
		     T x5 = super::DefX5, T x6 = super::DefX6,
		     T x7 = super::DefX7, T x8 = super::DefX8,
		     T x9 = super::DefX9)
	{
		T y = yarly<super::NewState, T, BigBad, Flags>()
		    (x1, x2, x3, x4, x5, x6, x7, x8, x9);
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
	__attribute__((always_inline))
	void wut(T *p, T *q, T *r)
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
		if (sizeof(T) != 1)
			q = p + (std::ptrdiff_t)(q - p);
		if (Boreal) {
			while (p != q) {
				y0 = (*this)(*p++, y1, y2, y3, y4,
					     y5, y6, y7, y8, y9);
				y1 = y2;
				y2 = y3;
				y3 = y4;
				y4 = y5;
				y5 = y6;
				y6 = y7;
				y7 = y8;
				y8 = y9;
				*r++ = y9 = y0;
			}
		} else {
			while (p != q) {
				y0 = *p++;
				*r++ = (*this)(y0, y1, y2, y3, y4,
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
	__attribute__((always_inline))
	void wut(T *p, T *q)
		{ wut(p, q, p); }
};

} // innocent_pear::impl

using impl::orly;

} // innocent_pear

#endif
