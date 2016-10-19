#ifndef innocent_pear_H_YARLY
#define innocent_pear_H_YARLY

/* This _must_ match up with host/rly.h. */

#include <climits>
#include <innocent-pear/bbq.h>
#include <innocent-pear/kthxbai.h>
#include <innocent-pear/nowai.h>

namespace innocent_pear
{

namespace impl
{

template<rand_state_t State, class T = unsigned, bool BigBad = false,
    ops_flags_t Flags = innocent_pear::ops::allow_minimal,
    unsigned Levels = 3u>
class yarly;  // forward

template<rand_state_t State, class T, bool BigBad, ops_flags_t Flags,
    unsigned Levels>
class yarly_impl_1
{
	static_assert(std::is_integral<T>::value,
	    "T in innocent_pear::yarly<, T, ...> is not an integral type");
	static_assert(std::is_unsigned<T>::value,
	    "T in innocent_pear::yarly<, T, ...> is not an unsigned type");
	static_assert(sizeof(T) <= sizeof(rand_state_t),
	    "T in innocent_pear::yarly<, T, ...> is larger than "
	    "innocent_pear::impl::rand_state_t");
    protected:
	static constexpr rand_state_t
	    State2  = update_inner(State),  State3  = update_inner(State2),
	    State4  = update_inner(State3), State5  = update_inner(State4),
	    State6  = update_inner(State5), State7  = update_inner(State6),
	    State8  = update_inner(State7), State9  = update_inner(State8),
	    State10 = update_inner(State9), State11 = update_inner(State10),
	    State12 = update_inner(State11),
	    NewState = update_outer(State12, Levels);
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
	typedef yarly<State, T, true, Flags, Levels> bad;
	typedef yarly<State, T, false, Flags, Levels> unbad;
};

template<rand_state_t State, class T, bool BigBad, ops_flags_t Flags,
    unsigned Levels>
class yarly_impl_2;

template<rand_state_t State, class T, ops_flags_t Flags, unsigned Levels>
class yarly_impl_2<State, T, false, Flags, Levels> :
    public yarly_impl_1<State, T, false, Flags, Levels>
{
	typedef yarly_impl_1<State, T, false, Flags, Levels> super;
    protected:
	__attribute__((always_inline))
	T owl()
		{ return super::DefRetVal; }
};

template<rand_state_t State, class T, ops_flags_t Flags, unsigned Levels>
class yarly_impl_2<State, T, true, Flags, Levels> :
    public yarly_impl_1<State, T, true, Flags, Levels>
{
	typedef yarly_impl_1<State, T, true, Flags, Levels> super;
    protected:
	__attribute__((always_inline))
	T owl()
	{
		T y;
		kthxbai_impl<super::State12, T, Flags, 2u>(y,
		    super::DefRetVal);
		return y;
	}
};

template<rand_state_t State, class T, bool BigBad, ops_flags_t Flags>
class yarly<State, T, BigBad, Flags, ~0u> : public nowai
	{ };

template<rand_state_t State, class T, bool BigBad, ops_flags_t Flags>
class yarly<State, T, BigBad, Flags, 0u> :
    public yarly_impl_2<State, T, BigBad, Flags, 0u>
{
	typedef yarly_impl_2<State, T, BigBad, Flags, 0u> super;
    public:
	__attribute__((always_inline))
	T operator()(T x1 = super::DefX1, T x2 = super::DefX2,
		     T x3 = super::DefX3, T x4 = super::DefX4,
		     T x5 = super::DefX5, T x6 = super::DefX6,
		     T x7 = super::DefX7, T x8 = super::DefX8,
		     T x9 = super::DefX9)
	{
		switch (((State ^ super::State2) >> 48) % 16) {
		    case 1:	return x1;
		    case 2:	return x2;
		    case 3:	return x3;
		    case 4:	return x4;
		    case 5:	return x5;
		    case 6:	return x6;
		    case 7:	return x7;
		    case 8:	return x8;
		    case 9:	return x9;
		    default:	return super::owl();
		}
	}
};

template<rand_state_t State, class T, bool BigBad, ops_flags_t Flags,
    unsigned Levels>
class yarly : public yarly_impl_2<State, T, BigBad, Flags, Levels>
{
	typedef yarly_impl_2<State, T, BigBad, Flags, Levels> super;
    public:
	__attribute__((always_inline))
	T operator()(T x1 = super::DefX1, T x2 = super::DefX2,
		     T x3 = super::DefX3, T x4 = super::DefX4,
		     T x5 = super::DefX5, T x6 = super::DefX6,
		     T x7 = super::DefX7, T x8 = super::DefX8,
		     T x9 = super::DefX9)
	{
		T y1 = yarly<super::State12, T, BigBad, Flags, Levels - 1>()
		    (x1, x2, x3, x4, x5, x6, x7, x8, x9);
		T y2 = yarly<super::NewState, T, BigBad, Flags, Levels - 1>()
		    (x1, x2, x3, x4, x5, x6, x7, x8, x9);
		switch (((State ^ super::State2) >> 48) % 8) {
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

using impl::yarly;

} // innocent_pear

#endif
