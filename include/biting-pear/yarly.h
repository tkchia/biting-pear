#ifndef biting_pear_H_YARLY
#define biting_pear_H_YARLY

#include <climits>
#include <biting-pear/bbq.h>
#include <biting-pear/kthxbai.h>

namespace biting_pear
{

namespace impl
{

template<rand_state_t State, class T = unsigned, bool BigBad = false,
    unsigned Levels = 2u>
class yarly;  // forward

template<rand_state_t State, class T, bool BigBad, unsigned Levels>
class yarly_impl
{
    protected:
	static constexpr rand_state_t
	    State2  = update_inner(State),  State3  = update_inner(State2),
	    State4  = update_inner(State3), State5  = update_inner(State4),
	    State6  = update_inner(State5), State7  = update_inner(State6),
	    State8  = update_inner(State7), State9  = update_inner(State8),
	    State10 = update_inner(State9), State11 = update_inner(State10),
	    State12 = update_inner(State11),
	    NewState = update_outer(State12),
	    NewNewState = update_outer(NewState);
	static constexpr T DefX1 = pick_hi<T>(State2  ^ State3),
			   DefX2 = pick_hi<T>(State3  ^ State4),
			   DefX3 = pick_hi<T>(State4  ^ State5),
			   DefX4 = pick_hi<T>(State5  ^ State6),
			   DefX5 = pick_hi<T>(State6  ^ State7),
			   DefX6 = pick_hi<T>(State7  ^ State8),
			   DefX7 = pick_hi<T>(State8  ^ State9),
			   DefX8 = pick_hi<T>(State9  ^ State10),
			   DefX9 = pick_hi<T>(State10 ^ State11),
			   DefRetVal = pick_hi<T>(State11 ^ State12);
	typedef yarly<State, T, true, Levels> bad;
	typedef yarly<State, T, false, Levels> unbad;
};

template<rand_state_t State, class T, bool BigBad>
class yarly<State, T, BigBad, 0u> :
    public yarly_impl<State, T, BigBad, 0u>
{
	typedef yarly_impl<State, T, BigBad, 0u> super;
    public:
	__attribute__((always_inline))
	T operator()(T x1 = super::DefX1, T x2 = super::DefX2,
		     T x3 = super::DefX3, T x4 = super::DefX4,
		     T x5 = super::DefX5, T x6 = super::DefX6,
		     T x7 = super::DefX7, T x8 = super::DefX8,
		     T x9 = super::DefX9)
	{
		switch ((State ^ super::State2) >> 48 % 16) {
		    case 1:	return x1;
		    case 2:	return x2;
		    case 3:	return x3;
		    case 4:	return x4;
		    case 5:	return x5;
		    case 6:	return x6;
		    case 7:	return x7;
		    case 8:	return x8;
		    case 9:	return x9;
		    default:	if (BigBad) {
					T y;
					kthxbai_impl<super::State12, T,
					    BigBad ? 4u : 0u>
					    (y, super::DefRetVal);
					return y;
				} else
					return super::DefRetVal;
		}
	}
};

template<rand_state_t State, class T, bool BigBad, unsigned Levels>
class yarly : public yarly_impl<State, T, BigBad, Levels>
{
	typedef yarly_impl<State, T, BigBad, Levels> super;
    public:
	__attribute__((always_inline))
	T operator()(T x1 = super::DefX1, T x2 = super::DefX2,
		     T x3 = super::DefX3, T x4 = super::DefX4,
		     T x5 = super::DefX5, T x6 = super::DefX6,
		     T x7 = super::DefX7, T x8 = super::DefX8,
		     T x9 = super::DefX9)
	{
		T y1 = yarly<super::State12, T, BigBad, Levels - 1>()
		    (x1, x2, x3, x4, x5, x6, x7, x8, x9);
		T y2 = yarly<super::NewState, T, BigBad, Levels - 1>()
		    (x1, x2, x3, x4, x5, x6, x7, x8, x9);
		switch ((State ^ super::State2) >> 48 % 16) {
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

} // biting_pear::impl

using impl::yarly;

} // biting_pear

#endif
