#ifndef innocent_pear_H_UNPOSSIBLE
#define innocent_pear_H_UNPOSSIBLE

#include <cinttypes>
#include <climits>
#include <type_traits>
#include <innocent-pear/bbq.h>
#include <innocent-pear/nowai.h>
#include <innocent-pear/omg.h>
#include <innocent-pear/rofl.h>
#include <innocent-pear/yarly.h>

namespace innocent_pear
{

namespace impl
{

template<rand_state_t State, class T, ops_flags_t Flags, unsigned Levels>
class omg;  // forward

template<rand_state_t State, ops_flags_t Flags, unsigned Levels>
class rofl;  // forward

template<rand_state_t State, class T, unsigned Levels>
class unpossible;

template<rand_state_t State, class T>
class unpossible<State, T, ~0u> : public nowai
	{ };

template<rand_state_t State, class T>
class unpossible<State, T, 0u>
{
    public:
	innocent_pear_always_inline
	unpossible()
	{
		constexpr rand_state_t State2 = update_inner(State);
		switch ((State2 >> 32) % 3) {
		    case 0:
#if defined __amd64__ || defined __i386__
			void (*p)();
			__asm __volatile("call *%0" : "=g" (p) : : "cc",
			    "memory");
#endif
			break;
#ifdef __OPTIMIZE__
		    default:
#   if defined __arm__ && defined __thumb__
			__asm __volatile(".inst.n %c0"
			    : /* no outputs */
			    : "n" ((uint_least32_t)pick_hi<uint_least16_t>
				(State ^ State2))
			    : "cc", "memory");
#   elif defined __arm__
			__asm __volatile(".inst %c0"
			    : /* no outputs */
			    : "n" (pick_hi<uint_least32_t>(State ^ State2))
			    : "cc", "memory");
#   elif defined __i386__ || defined __amd64__
			__asm __volatile(".byte %c0"
			    : /* no outputs */
			    : "n" (pick_hi<uint_least8_t>(State ^ State2))
			    : "cc", "memory");
#   else
			;
#   endif
#endif
		}
	}
	innocent_pear_always_inline
	unpossible(T& x)
	{
		unpossible();
		__asm("" : "=g" (x));
	}
};

template<rand_state_t State, class T, unsigned Levels>
class unpossible
{
    public:
	innocent_pear_always_inline
	unpossible(T& x)
	{
		constexpr rand_state_t
		    State2 = update_inner(State),
		    NewState = update_outer(State, Levels),
		    NewState2 = update_outer(State2, Levels);
		constexpr unsigned BitP =
		    (State2 >> 52) % (sizeof(T) * CHAR_BIT);
		constexpr ops_flags_t Flags = (ops_flags_t)
		    (innocent_pear::ops::allow_for_startup |
		     innocent_pear::ops::under_unpossible);
		switch ((State2 >> 32) % 6) {
		    case 0:
			{ omg<NewState, T, Flags, Levels - 1> zomg(x); }
			break;
		    case 1:
			{
				T y;
				omg<NewState, T, Flags, Levels - 1> zomg(y);
				if (bit_set(y, BitP)) {
					unpossible<NewState, T, Levels - 1>
					    un(x);
				} else {
					unpossible<NewState2, T, Levels - 1>
					    un(x);
				}
			}
			break;
		    case 2:
			x = (T)rofl<NewState2, Flags, Levels - 1>::syscall
			    ((long)pick_hi<unsigned long>(State2 ^ NewState));
			break;
		    case 3:
			{
				uintptr_t y;
				unpossible<NewState, uintptr_t, Levels - 1>
				    un(y);
				x = (T)rofl<NewState2, Flags, Levels - 1>::
				    syscall((long)pick_hi<unsigned long>
					(State2 ^ NewState), y);
			}
			break;
		    case 4:
			{ unpossible<NewState, T, Levels - 1> un(x); }
			// fall through
		    default:
			{ unpossible<NewState2, T, Levels - 1> un(x); }
		}
	}
	innocent_pear_always_inline
	unpossible()
	{
		T x;
		unpossible un(x);
	}
};

} // innocent_pear::impl

} // innocent_pear

#endif
