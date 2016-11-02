#ifndef innocent_pear_H_TFW
#define innocent_pear_H_TFW

#include <climits>
#include <innocent-pear/bbq.h>
#include <innocent-pear/kthxbai.h>

namespace innocent_pear
{

namespace impl
{

template<rand_state_t State, class T, ops_flags_t Flags, unsigned Levels>
class kthxbai_impl;  // forward

template<rand_state_t State, class T, ops_flags_t Flags, unsigned Levels>
class tfw
{
	static constexpr rand_state_t State2 = update_inner(State),
				      State3 = update_inner(State2),
				      NewState = update_outer(State, Levels);
	static constexpr T Val = pick_hi<T>(State3 ^ NewState);
	static constexpr unsigned Bit =
	    pick_hi<T>(State2 ^ NewState) % (sizeof(T) * CHAR_BIT);
	T x_;
	__attribute__((always_inline))
	static void set(T& x)
		{ kthxbai_impl<NewState, T, Flags, Levels>(x, Val); }
    public:
	__attribute__((always_inline))
	tfw()
		{ set(x_); }
	__attribute__((always_inline))
	tfw(T& x)
	{
		set(x);
		x_ = x;
	}
	__attribute__((always_inline))
	operator bool() const
	{
		return bit_set(Val, Bit) ? bit_set(x_, Bit) :
					   !bit_set(x_, Bit);
	}
	__attribute__((always_inline))
	bool operator !() const
		{ return !(bool)*this; }
};

} // innocent_pear::impl

using impl::tfw;

} // innocent_pear

#endif
