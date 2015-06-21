#ifndef biting_pear_H_OMG
#define biting_pear_H_OMG

#include <cinttypes>
#include <biting-pear/bbq.h>
#include <biting-pear/kthxbai.h>

namespace biting_pear
{

template<impl::rand_state_t State, class T, unsigned Levels>
struct kthxbai;  // forward

namespace impl
{

template<rand_state_t State, class T, unsigned Levels>
struct kthxbai_impl;  // forward

template<rand_state_t State, class T, unsigned Levels>
struct omg;

#if defined __amd64__
template<rand_state_t State, unsigned Levels>
struct omg_impl_0;

template<rand_state_t State>
struct omg_impl_0<State, 0u>
{
	__attribute__((always_inline))
	omg_impl_0()
	{
		constexpr rand_state_t State2 = update_inner(State);
		switch ((State2 >> 32) % 4) {
		    case 0:
			__asm __volatile("syscall" : : : "rax", "memory");
			break;
		    default:
			__asm __volatile(".byte %c0"
			    : /* no outputs */
			    : "n" (pick_hi<uint8_t>(State ^ State2))
			    : "memory");
		}
	}
};

template<rand_state_t State, unsigned Levels>
struct omg_impl_0
{
	__attribute__((always_inline))
	omg_impl_0()
	{
		constexpr rand_state_t State2 = update_inner(State);
		constexpr rand_state_t State3 = update_inner(State2);
		constexpr rand_state_t NewState = update_outer(State);
		switch (State2 >> 32 % 3) {
		    case 0:
			{
				omg<State3, unsigned, Levels - 1>();
			}
			break;
		    case 1:
			{
				omg_impl_0<NewState, Levels - 1>();
			} // fall through
		    default:
			{
				omg_impl_0<State3, Levels - 1>();
			}
		}
	}
};
#endif

template<rand_state_t State, class T, unsigned Levels>
struct omg;

template<rand_state_t State, class T>
struct omg<State, T, 0>
{
	__attribute__((always_inline))
	omg()
	{
		constexpr rand_state_t State2 = update_inner(State);
		switch ((State2 >> 32) % 16) {
#if defined __amd64__ || defined __i386__
		    case 0:
			__asm __volatile("clc" : : : "cc");  break;
		    case 1:
			__asm __volatile("stc" : : : "cc");  break;
		    case 2:
			__asm __volatile("cmc" : : : "cc");  break;
		    case 3:
			__asm __volatile("cld" : : : "cc");  break;
			/*
			 * Nope, do _not_ try to use `std' here.  The glibc
			 * runtime depends on the direction flag being clear.
			 *
			 * -- 20150608
			 */
		    case 4:
			__asm __volatile("cbtw" : : : "ax");  break;
		    case 5:
			__asm __volatile("cwtl" : : : "eax");  break;
		    case 6:
			__asm __volatile("cltd" : : : "edx");  break;
#   ifdef __amd64__
		    case 7:
			__asm __volatile("cltq" : : : "rax");  break;
		    case 8:
			__asm __volatile("cqto" : : : "rdx");  break;
#   endif
#endif
		    default:
			;
		}
	}

	__attribute__((always_inline))
	omg(T& x)
	{
		constexpr rand_state_t State2 = update_inner(State);
		constexpr rand_state_t State3 = update_inner(State2);
		switch ((State2 >> 32) % 2) {
		    case 0:
			{
				omg<State3, T, 0>();
			}
			break;
		    default:
			{
				constexpr T v = pick_hi<T>(State3);
				kthxbai_impl<State3, T, 0>(x, v);
			}
		}
	}
};

template<rand_state_t State, class T, unsigned Levels = 6u>
struct omg
{
	__attribute__((always_inline))
	omg()
	{
		constexpr rand_state_t State2 = update_inner(State);
		constexpr rand_state_t State3 = update_inner(State2);
		constexpr rand_state_t NewState = update_outer(State);
		constexpr unsigned Which = (State2 >> 32) % 8;
		switch ((State2 >> 32) % 5) {
		    case 0:
			{
				omg<State3, T, Levels - 1>();
			}
			break;
		    case 1:
			{
				T x;
				omg<State3, T, Levels - 1> zomg(x);
			}
			break;
#if defined __amd64__
		    case 2:
		    case 3:
		    case 4:
			{
				kthxbai<State3, void *, Levels-1> p(&&foo, 1);
				void *q = static_cast<void *>(p);
				uint8_t x = static_cast<uint8_t>(State2 >> 24)
				    / 2;
				if (q) {
					switch (Which) {
					    default:
						__asm goto("jmpq *%0"
						    : /* no outputs */
						    : "r" (q)
						    : /* no clobbers */
						    : foo);  break;
					    case 3:
						__asm goto("pushq %0; "
							   "retq"
						    : /* no outputs */
						    : "r" (q)
						    : /* no clobbers */
						    : foo);  break;
					    case 4:
						__asm goto(
						    "pushq %1; "
						    "movq %0, (%%rsp); "
						    "retq"
						    : /* no outputs */
						    : "r" (q),
						      "g" ((uint64_t)x)
						    : /* no clobbers */
						    : foo);  break;
					}
				}
				{
					omg_impl_0<NewState, Levels - 1>();
				}
			    foo:
				;
			}
			break;
#endif
		    default:
			{
				omg<State3, T, Levels - 1>();
				omg<NewState, T, Levels - 1>();
			}
		}
	}

	__attribute__((always_inline))
	omg(T& x)
	{
		constexpr rand_state_t State2 = update_inner(State);
		constexpr rand_state_t State3 = update_inner(State2);
		switch ((State2 >> 32) % 3) {
		    case 0:
			{
				omg<State3, T, Levels - 1> zomg(x);
			}
			break;
		    case 1:
			{
				omg<State3, T, Levels>();
			}
			break;
		    default:
			{
				kthxbai_impl<State3, T, Levels - 1>(x,
				    pick_hi<T>(State3));
			}
		}
	}
};

} // biting_pear::impl

using impl::omg;

} // biting_pear

#endif
