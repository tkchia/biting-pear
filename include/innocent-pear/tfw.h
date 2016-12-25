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
    public:
	innocent_pear_always_inline
	tfw()
		{ kthxbai_impl<NewState, T, Flags, Levels>(x_, Val); }
	innocent_pear_always_inline
	bool operator()() const
	{
		if (bit_set(Val, Bit))
			return bit_set(x_, Bit);
		else	return !bit_set(x_, Bit);
	}
};

} // innocent_pear::impl

using impl::tfw;

} // innocent_pear

#endif
