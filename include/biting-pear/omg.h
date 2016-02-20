#ifndef biting_pear_H_OMG
#define biting_pear_H_OMG

#include <cinttypes>
#include <csignal>
#include <unistd.h>
#include <biting-pear/bbq.h>
#include <biting-pear/kthxbai.h>
#include <biting-pear/nowai.h>

namespace biting_pear
{

namespace impl
{

template<impl::rand_state_t State, class T, ops_flags_t Flags,
    unsigned Levels>
class kthxbai;  // forward

template<rand_state_t State, class T, ops_flags_t Flags, unsigned Levels>
struct kthxbai_impl;  // forward

template<rand_state_t State, class T, ops_flags_t Flags, unsigned Levels>
class omg;

#if defined __amd64__ || defined __i386__ || defined __arm__
template<rand_state_t State, unsigned Levels>
struct omg_impl_0;

template<rand_state_t State>
struct omg_impl_0<State, ~0u> : public nowai
	{ };

template<rand_state_t State>
struct omg_impl_0<State, 0u>
{
	__attribute__((always_inline))
	omg_impl_0()
	{
		constexpr rand_state_t State2 = update_inner(State);
		switch ((State2 >> 32) % 4) {
		    case 0:
#if defined __amd64__
			__asm __volatile("syscall" : : : "rax", "memory");
#elif defined __i386__
			__asm __volatile("call *%%gs:0x10" : : : "eax",
			    "memory");
#elif defined __arm__
			__asm __volatile("svc #0" : : : "r0", "memory");
#endif
			break;
#ifdef __OPTIMIZE__
		    default:
#   if defined __arm__ && defined __thumb__
			__asm __volatile(".inst.n %c0"
			    : /* no outputs */
			    : "n" ((uint32_t)pick_hi<uint16_t>(State^State2))
			    : "memory");
#   elif defined __arm__
			__asm __volatile(".inst %c0"
			    : /* no outputs */
			    : "n" (pick_hi<uint32_t>(State ^ State2))
			    : "memory");
#   elif defined __i386__ || defined __amd64__
			__asm __volatile(".byte %c0"
			    : /* no outputs */
			    : "n" (pick_hi<uint8_t>(State ^ State2))
			    : "memory");
#   else
			;
#   endif
#endif
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
				omg<State3, unsigned,
				    biting_pear::ops::allow_all, Levels-1>();
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

template<rand_state_t State, class T, ops_flags_t Flags = 0,
    unsigned Levels = 3u>
class omg;

template<rand_state_t State, class T, ops_flags_t Flags>
class omg<State, T, Flags, ~0u> : public nowai
	{ };

template<rand_state_t State, class T, ops_flags_t Flags>
class omg<State, T, Flags, 0u>
{
    public:
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
				omg<State3, T, Flags, 0>();
			}
			break;
		    default:
			{
				constexpr T v = pick_hi<T>(State3);
				kthxbai_impl<State3, T, Flags, 0>(x, v);
			}
		}
	}
};

template<rand_state_t State, class T, ops_flags_t Flags, unsigned Levels>
class omg
{
	static constexpr rand_state_t State2 = update_inner(State);
	static constexpr rand_state_t State3 = update_inner(State2);
	static constexpr rand_state_t NewState = update_outer(State);
	__attribute__((always_inline))
	bool unsafe()
	{
		using namespace biting_pear::ops;
		constexpr unsigned Which2 = (State2 >> 56) % 4;
		switch (Which2) {
		    case 0:
			if (!(Flags & allow_signal_safes))
				return false;
			else {
				kthxbai<State3,
				    biting_pear_decltype(&std::raise),
				    Flags, Levels - 1> f(std::raise);
				kthxbai<NewState, unsigned, Flags, Levels - 1>
				    z(0);
				f((int)z);
				return true;
			}
		    case 1:
		    case 2:
			if (!(Flags & allow_signal_safes))
				return false;
			else {
				kthxbai<State3, pid_t (*)(), Flags,
				    Levels - 1>
				    f(Which2 == 1 ? getpid : getppid);
				f();
				return true;
			}
		    default:
			return false;
		}
	}
    public:
	__attribute__((always_inline))
	omg()
	{
		constexpr unsigned Which = (State2 >> 48) % 8;
#if defined __amd64__ || defined __i386__
		constexpr unsigned Which2 = (State2 >> 56) % 5;
		constexpr unsigned Which3 = (State2 >> 51) % 8;
#elif defined __arm__ || defined __thumb__
		constexpr unsigned Which2 = (State2 >> 56) % 3;
#endif
		switch (Which) {
		    case 0:
			{
				omg<State3, T, Flags, Levels - 1>();
			}
			break;
		    case 1:
			{
				T x;
				omg<State3, T, Flags, Levels - 1> zomg(x);
			}
			break;
#if defined __amd64__ || defined __i386__
#   ifdef __OPTIMIZE__
#	define biting_pear_RET_PREFIX(o) ".if 0 == %c" #o "; " \
						".byte 0x26; "	/* %es: */ \
					 ".elseif 1 == %c" #o "; " \
						".byte 0x2e; "	/* %cs: */ \
					 ".elseif 2 == %c" #o "; " \
						".byte 0x3e; "	/* %ds: */ \
					 ".elseif 3 == %c" #o "; " \
						".byte 0x64; "	/* %fs: */ \
					 ".elseif 4 == %c" #o "; " \
						".byte 0x65; "	/* %gs: */ \
					 ".elseif 5 == %c" #o "; " \
						"repz; " \
					 ".elseif 6 == %c" #o "; " \
						"repnz; " \
					 ".endif; "
#   else
#	define biting_pear_RET_PREFIX(o) ""
#   endif
		    case 2:
		    case 3:
		    case 4:
			{
				void *q, *r;
#   ifdef __i386__
				__asm("movw %%cs, %w0" : "=r" (r));
#   else
				__asm("movq %%cs, %0" : "=g" (r));
#   endif
				kthxbai<State3, void *, Flags, Levels>
				    p(&&foo, 1);
				uint8_t x = static_cast<uint8_t>(State2 >> 24)
				    / 2;
				q = static_cast<void *>(p);
				if (!q)
					goto bar;
				switch (Which2) {
				    default:
					__asm goto("jmp%z0 *%0"
					    : /* no outputs */
					    : "r" (q)
					    : /* no clobbers */
					    : foo);  break;
				    case 1:
					__asm goto("push%z0 %0; "
						   biting_pear_RET_PREFIX(1)
						   "ret%z0"
					    : /* no outputs */
					    : "r" (q), "n" (Which3)
					    : /* no clobbers */
					    : foo);  break;
				    case 2:
					__asm goto("push%z0 %1; "
						   "push%z0 %0; "
						   biting_pear_RET_PREFIX(2)
						   "lret%z0"
					    : /* no outputs */
					    : "r" (q), "r" (r), "n" (Which3)
					    : /* no clobbers */
					    : foo);  break;
#   ifdef __amd64__
				    case 3:
					__asm goto(
					    "pushq %1; "
					    "movq %0, (%%rsp); "
					    biting_pear_RET_PREFIX(2)
					    "retq"
					    : /* no outputs */
					    : "r" (q), "g" ((uint64_t)x),
					      "n" (Which3)
					    : /* no clobbers */
					    : foo);  break;
				    case 4:
					__asm goto(
					    "pushq %1; "
					    "pushq %2; "
					    "movq %0, (%%rsp); "
					    biting_pear_RET_PREFIX(3)
					    "lretq"
					    : /* no outputs */
					    : "r" (q), "r" (r),
					      "g" ((uint64_t)x), "n" (Which3)
					    : /* no clobbers */
					    : foo);  break;
#   else
				    case 3:
					__asm goto(
					    "pushl %1; "
					    "movl %0, (%%esp); "
					    biting_pear_RET_PREFIX(2)
					    "retl"
					    : /* no outputs */
					    : "r" (q), "g" ((uint32_t)x),
					      "n" (Which3)
					    : /* no clobbers */
					    : foo);  break;
				    case 4:
					__asm goto(
					    "pushl %1; "
					    "pushl %2; "
					    "movl %0, (%%esp); "
					    biting_pear_RET_PREFIX(3)
					    "lretl"
					    : /* no outputs */
					    : "r" (q), "r" (r),
					      "g" ((uint32_t)x), "n" (Which3)
					    : /* no clobbers */
					    : foo);  break;
#   endif
#   undef biting_pear_RET_PREFIX
				}
			    bar:
				{
					omg_impl_0<NewState, Levels - 1>();
				}
			    foo:
				;
			}
			break;
#elif defined __arm__ || defined __thumb__
		    case 2:
		    case 3:
		    case 4:
			{
#   if defined __thumb__
				kthxbai<State3, void *, Flags, Levels - 1>
				    p((char *)&&foo + 1, 1);
#   else
				kthxbai<State3, void *, Flags, Levels - 1>
				    p(&&foo, 1);
#   endif
				void *q = static_cast<void *>(p);
				if (q) {
					switch (Which2) {
					    default:
						__asm goto("mov pc, %0"
						    : /* no outputs */
						    : "r" (q)
						    : /* no clobbers */
						    : foo);  break;
#   ifdef __THUMB_INTERWORK__
					    case 1:
						__asm goto("bx %0"
						    : /* no outputs */
						    : "r" (q)
						    : /* no clobbers */
						    : foo);  break;
	// blx is supported only from ARMv5T onwards
#	if !defined __ARM_ARCH_4__ && !defined __ARM_ARCH_4T__
					    case 2:
						__asm goto("blx %0"
						    : /* no outputs */
						    : "r" (q)
						    : "lr"
						    : foo);  break;
#	endif
#   endif
					}
				}
				{
					omg_impl_0<NewState, Levels - 1>();
					__asm __volatile(".ltorg");
				}
			    foo:
				;
			}
			// fall through
#endif
		    case 5:
		    case 6:
			if (unsafe())
				return;
			// fall through
		    default:
			{
				omg<State3, T, Flags, Levels - 1>();
				omg<NewState, T, Flags, Levels - 1>();
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
				omg<State3, T, Flags, Levels - 1> zomg(x);
			}
			break;
		    case 1:
			{
				omg<State3, T, Flags, Levels>();
			}
			break;
		    default:
			{
				kthxbai_impl<State3, T, Flags, Levels - 1>(x,
				    pick_hi<T>(State3));
			}
		}
	}
};

} // biting_pear::impl

using impl::omg;

} // biting_pear

#endif
