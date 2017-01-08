#ifndef innocent_pear_H_UNPOSSIBLE
#define innocent_pear_H_UNPOSSIBLE

#include <cinttypes>
#include <climits>
#include <type_traits>
#include <innocent-pear/bbq.h>
#include <innocent-pear/nowai.h>
#include <innocent-pear/omg.h>
#include <innocent-pear/yarly.h>

namespace innocent_pear
{

namespace impl
{

template<rand_state_t State, class T, ops_flags_t Flags, unsigned Levels>
class omg;

template<rand_state_t State, class T, unsigned Levels>
struct unpossible;

template<rand_state_t State, class T>
struct unpossible<State, T, ~0u> : public nowai
	{ };

template<rand_state_t State, class T>
struct unpossible<State, T, 0u>
{
	innocent_pear_always_inline
	unpossible()
	{
		constexpr rand_state_t State2 = update_inner(State);
		switch ((State2 >> 32) % 4) {
		    case 0:
#if defined __amd64__ || defined __i386__
			void (*p)();
			__asm __volatile("call *%0" : "=g" (p) : : "cc",
			    "memory");
#endif
			break;
		    case 1:
#if defined __amd64__
			__asm __volatile("syscall" : : : "rax", "cc",
			    "memory");
#elif defined __i386__
			__asm __volatile("int $0x80" : : : "eax",
			    "cc", "memory");
#elif defined __arm__
			__asm __volatile("svc #0" : : : "r0", "cc", "memory");
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
struct unpossible
{
	innocent_pear_always_inline
	unpossible(T& x)
	{
		constexpr rand_state_t
		    State2 = update_inner(State),
		    NewState = update_outer(State, Levels),
		    NewState2 = update_outer(NewState, Levels);
		constexpr unsigned WhichTyp = (State2 >> 48) % 4;
		constexpr unsigned BitP =
		    (State2 >> 52) % (sizeof(T) * CHAR_BIT);
		constexpr ops_flags_t Flags = (ops_flags_t)
		    (innocent_pear::ops::allow_for_startup |
		     innocent_pear::ops::under_unpossible);
		switch ((State2 >> 32) % 4) {
		    case 0:
			{ omg<NewState, T, Flags, Levels - 1> zomg(x); }
			break;
		    case 1:
			{
				T y;
				omg<NewState, T, Flags, Levels - 1> zomg(y);
				if (bit_set(x, BitP)) {
					unpossible<NewState, T, Levels - 1>
					    un(x);
				} else {
					unpossible<NewState2, T, Levels - 1>
					    un(x);
				}
			}
			break;
		    case 2:
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
