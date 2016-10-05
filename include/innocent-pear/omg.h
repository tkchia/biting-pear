#ifndef innocent_pear_H_OMG
#define innocent_pear_H_OMG

#include <cinttypes>
#include <csignal>
#include <cstring>
#include <unistd.h>
#include <innocent-pear/bbq.h>
#include <innocent-pear/kthxbai.h>
#include <innocent-pear/nowai.h>
#include <innocent-pear/ohai.h>
#include <innocent-pear/rofl.h>
#include <innocent-pear/yarly.h>
#ifdef __unix__
#   include <fcntl.h>
#endif

namespace innocent_pear
{

namespace impl
{

template<impl::rand_state_t State, class T, ops_flags_t Flags,
    unsigned Levels>
class kthxbai;  // forward

template<rand_state_t State, class T, ops_flags_t Flags, unsigned Levels>
class kthxbai_impl;  // forward

template<impl::rand_state_t State, ops_flags_t Flags, unsigned Levels>
class rofl;  // forward

template<rand_state_t State, class CT, ops_flags_t Flags, unsigned Levels,
    CT... Chs>
class dawg_impl;  // forward

template<rand_state_t State, class T, bool BigBad, ops_flags_t Flags,
    unsigned Levels>
class yarly;  // forward

template<rand_state_t State, class T, ops_flags_t Flags, unsigned Levels>
class omg;

#if defined __amd64__ || defined __i386__ || defined __arm__
template<rand_state_t State, unsigned Levels>
struct omg_impl_0;

template<rand_state_t State>
struct omg_impl_0<State, ~0u> : public nowai
	{ };

#if defined __amd64__ || defined __i386__
#   ifdef __OPTIMIZE__
#	define innocent_pear_PREFIX(o)	".if 0 == %c" #o "; " \
						".byte 0x26; "	/* %es: */ \
					".elseif 1 == %c" #o "; " \
						".byte 0x2e; "	/* %cs: */ \
					".elseif 2 == %c" #o "; " \
						".byte 0x36; "	/* %ss: */ \
					".elseif 3 == %c" #o "; " \
						".byte 0x3e; "	/* %ds: */ \
					".elseif 4 == %c" #o "; " \
						".byte 0x64; "	/* %fs: */ \
					".elseif 5 == %c" #o "; " \
						".byte 0x65; "	/* %gs: */ \
					".endif; "
#	define innocent_pear_BR_PREFIX(o) \
					innocent_pear_PREFIX(o) \
					".if 6 == %c" #o "; " \
						"repz; " \
					".elseif 7 == %c" #o "; " \
						"repnz; " \
					".endif; "
#   else
#	define innocent_pear_PREFIX(o)	""
#	define innocent_pear_BR_PREFIX(o) ""
#   endif
#endif

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
		constexpr rand_state_t
		    State2 = update_inner(State),
		    NewState = update_outer(State, Levels),
		    NewState2 = update_outer(NewState, Levels);
		switch ((State2 >> 32) % 3) {
		    case 0:
			{
				omg<NewState, unsigned,
				    innocent_pear::ops::allow_for_startup,
				    Levels - 1>();
			}
			break;
		    case 1:
			{
				omg_impl_0<NewState, Levels - 1>();
			} // fall through
		    default:
			{
				omg_impl_0<NewState2, Levels - 1>();
			}
		}
	}
};
#endif

template<rand_state_t State, class T, ops_flags_t Flags = 0,
    unsigned Levels = 2u>
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
		constexpr rand_state_t State3 = update_inner(State2);
		constexpr unsigned Which2 = (State2 >> 32) % 16;
		constexpr unsigned Which3 = (State3 >> 32) % 15;
		switch (Which2) {
#if defined __amd64__ || defined __i386__
#   define innocent_pear_PREFIXED_INSN(insn, ...) \
			__asm __volatile(innocent_pear_PREFIX(0) insn \
			    : /* no outputs */ \
			    : "n" (Which3) \
			    : __VA_ARGS__)
		    case 0:
			innocent_pear_PREFIXED_INSN("clc", "cc");  break;
		    case 1:
			innocent_pear_PREFIXED_INSN("stc", "cc");  break;
		    case 2:
			innocent_pear_PREFIXED_INSN("cmc", "cc");  break;
		    case 3:
			innocent_pear_PREFIXED_INSN("cld", "cc");  break;
			/*
			 * Nope, do _not_ try to use `std' here.  The glibc
			 * runtime depends on the direction flag being clear.
			 *
			 * -- 20150608
			 */
		    case 4:
			innocent_pear_PREFIXED_INSN("cbtw", "ax");  break;
		    case 5:
			innocent_pear_PREFIXED_INSN("cwtl", "eax");  break;
		    case 6:
			innocent_pear_PREFIXED_INSN("cltd", "edx");  break;
#   ifdef __amd64__
		    case 7:
			innocent_pear_PREFIXED_INSN("cltq", "rax");  break;
		    case 8:
			innocent_pear_PREFIXED_INSN("cqto", "rdx");  break;
#   endif
		    case 9:
			innocent_pear_PREFIXED_INSN("rdtsc", "eax", "edx");
			break;
#   undef innocent_pear_PREFIXED_INSN
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
		switch (State2 % 5) {
		    case 0:
		    case 1:
			{
				omg<State3, T, Flags, 0>();
				__asm __volatile("" : "=g" (x));
			}
			break;
#if defined __i386__ || defined __amd64__
		    case 2:
			{
				unsigned y;
				__asm(innocent_pear_PREFIX(1) "rdtsc"
				    : "=a" (y)
				    : "n" ((State3 >> 32) % 6)
				    : "edx");
				x = static_cast<T>(y);
			}
			break;
#endif
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
	static constexpr rand_state_t
	    State2 = update_inner(State),
	    State3 = update_inner(State2),
	    State4 = update_inner(State3),
	    State5 = update_inner(State4),
	    State6 = update_inner(State5),
	    State7 = update_inner(State6),
	    State8 = update_inner(State7),
	    State9 = update_inner(State8),
	    State10 = update_inner(State9),
	    State11 = update_inner(State10),
	    NewState = update_outer(State, Levels),
	    NewState2 = update_outer(NewState, Levels),
	    NewState3 = update_outer(NewState2, Levels),
	    NewState4 = update_outer(NewState3, Levels),
	    NewState5 = update_outer(NewState4, Levels);
	static constexpr unsigned char
	    Frob0 = pick_hi<unsigned char>(State2  ^ State3),
	    Frob1 = pick_hi<unsigned char>(State3  ^ State4),
	    Frob2 = pick_hi<unsigned char>(State4  ^ State5),
	    Frob3 = pick_hi<unsigned char>(State5  ^ State6),
	    Frob4 = pick_hi<unsigned char>(State6  ^ State7),
	    Frob5 = pick_hi<unsigned char>(State7  ^ State8),
	    Frob6 = pick_hi<unsigned char>(State8  ^ State9),
	    Frob7 = pick_hi<unsigned char>(State9  ^ State10),
	    Frob8 = pick_hi<unsigned char>(State10 ^ State11);
	typedef kthxbai<NewState, unsigned, Flags, Levels - 1> kthxbai1;
	typedef rofl<NewState2, Flags, Levels - 1> rofl2;
	typedef rofl<NewState3, Flags, Levels - 1> rofl3;
	typedef rofl<NewState4, Flags, Levels - 1> rofl4;
    public:
	__attribute__((always_inline))
	static bool special()
	{
		using namespace innocent_pear::ops;
		constexpr unsigned Which2 = (State2 >> 56) % 6;
		pid_t pid;
#ifdef innocent_pear_HAVE_CONST_TCOOFF
		int fd;
#endif
		switch (Which2) {
		    default:
		    case 1:
			if (!(Flags & allow_signal_safes))
				return false;
			break;
#ifdef innocent_pear_HAVE_CONST_TCOOFF
		    case 2:
		    case 3:
		    case 4:
			if (!(Flags & under_munged_terminal))
				return false;
#   ifdef  __unix__
		    case 5:
			if (!(Flags & under_munged_terminal) ||
			    !(Flags & allow_resource_unsafes))
				return false;
#   endif
#endif
		}
		switch (Which2) {
		    default:
			pid = rofl2::getppid();
			break;
		    case 1:
			pid = rofl2::getpid();
			break;
#ifdef innocent_pear_HAVE_CONST_TCOOFF
		    case 2:
			fd = kthxbai1(0);
			break;
		    case 3:
			fd = kthxbai1(1);
			break;
		    case 4:
			fd = kthxbai1(2);
			break;
#   ifdef __unix__
		    case 5:
			{
				static volatile char cfn[9] = {
				    '/' ^ Frob0, 'd' ^ Frob1, 'e' ^ Frob2,
				    'v' ^ Frob3, '/' ^ Frob4, 't' ^ Frob5,
				    't' ^ Frob6, 'y' ^ Frob7, Frob8 };
				ohai<char, 9> fn;
				fn[0] = cfn[0] ^ Frob0;
				fn[1] = cfn[1] ^ Frob1;
				fn[2] = cfn[2] ^ Frob2;
				fn[3] = cfn[3] ^ Frob3;
				fn[4] = cfn[4] ^ Frob4;
				fn[5] = cfn[5] ^ Frob5;
				fn[6] = cfn[6] ^ Frob6;
				fn[7] = cfn[7] ^ Frob7;
				fn[8] = cfn[8] ^ Frob8;
				fd = rofl2::open(fn, O_RDONLY);
			}
#   endif
#endif
		}
		omg<NewState5, T, Flags, Levels - 1>();
		switch (Which2) {
		    default:
		    case 1:
			rofl3::kill(pid, kthxbai1(0));
			break;
#ifdef innocent_pear_HAVE_CONST_TCOOFF
		    case 2:
		    case 3:
		    case 4:
			rofl2::tcflow(fd, innocent_pear_VAL_CONST_TCOOFF);
			break;
#   ifdef __unix__
		    case 5:
			rofl3::tcflow(fd, innocent_pear_VAL_CONST_TCOOFF);
			rofl4::close(fd);
			break;
#   endif
#endif
		}
		return true;
	}
    public:
	__attribute__((always_inline))
	omg()
	{
		constexpr unsigned Which = (State2 >> 48) % 8;
#if defined __amd64__ || defined __i386__
#   ifdef innocent_pear_HAVE_ASM_GOTO
#	ifdef __amd64__
		constexpr unsigned Which2 = (State2 >> 40) % 5;
#	else
		constexpr unsigned Which2 = (State2 >> 40) % 6;
#	endif
		constexpr unsigned Which3 = (State3 >> 40) % 15;
		constexpr unsigned Which4 = (State4 >> 40) % 15;
		constexpr unsigned Which5 = (State5 >> 40) % 15;
		constexpr unsigned Which6 = (State6 >> 40) % 15;
#	ifdef __amd64__
		constexpr unsigned Which7 = (State7 >> 40) % 15;
#	endif
#   endif
#elif defined __arm__ || defined __thumb__
		constexpr unsigned Which2 = (State2 >> 56) % 4;
#endif
		switch (Which) {
		    case 0:
			{
				omg<NewState, T, Flags, Levels - 1>();
			}
			break;
		    case 1:
			{
				T x;
				omg<NewState, T, Flags, Levels - 1> zomg(x);
			}
			break;
		    case 2:
		    case 3:
		    case 4:
			if (special())
				return;
			// fall through
#if (defined __amd64__ || defined __i386__) && \
    defined innocent_pear_HAVE_ASM_GOTO
		    case 5:
		    case 6:
			{
				void *q, *r;
				__asm("movw %%cs, %w0" : "=g" (r));
				kthxbai<NewState, void *, Flags, Levels>
				    p(&&foo, 1);
#   ifdef __amd64__
				uint64_t rzsz = 128 + 8 * Which7;
#   endif
				uint8_t x = static_cast<uint8_t>(State2 >> 24)
				    / 2;
				q = static_cast<void *>(p);
				if (!q)
					goto bar;
				switch (Which2) {
				    default:
					__asm goto(innocent_pear_BR_PREFIX(1)
						   "jmp%z0 *%0"
					    : /* no outputs */
					    : "r" (q), "n" (Which3)
					    : /* no clobbers */
					    : foo);  break;
#   ifdef __amd64__
				    case 1:
					__asm goto(innocent_pear_PREFIX(3)
						   "subq %1, %%rsp; "
						   innocent_pear_PREFIX(4)
						   "pushq %0; "
						   innocent_pear_BR_PREFIX(5)
						   "retq %2"
					    : /* no outputs */
					    : "r" (q), "r" (rzsz),
					      "n" (rzsz), "n" (Which3),
					      "n" (Which4), "n" (Which5)
					    : /* no clobbers */
					    : foo);  break;
				    case 2:
					__asm goto(innocent_pear_PREFIX(4)
						   "subq %2, %%rsp; "
						   innocent_pear_PREFIX(5)
						   "pushq %1; "
						   innocent_pear_PREFIX(6)
						   "pushq %0; "
						   innocent_pear_BR_PREFIX(7)
						   "lretq %3"
					    : /* no outputs */
					    : "r" (q), "r" (r), "r" (rzsz),
					      "n" (rzsz), "n" (Which3),
					      "n" (Which4), "n" (Which5),
					      "n" (Which6)
					    : /* no clobbers */
					    : foo);  break;
				    case 3:
					__asm goto(
					    innocent_pear_PREFIX(4)
					    "subq %2, %%rsp; "
					    "pushq %1; "
					    "movq %0, (%%rsp); "
					    innocent_pear_BR_PREFIX(5)
					    "retq %3"
					    : /* no outputs */
					    : "r" (q), "g" ((uint64_t)x),
					      "r" (rzsz), "n" (rzsz),
					      "n" (Which3), "n" (Which4)
					    : /* no clobbers */
					    : foo);  break;
				    case 4:
					__asm goto(
					    innocent_pear_PREFIX(5)
					    "subq %3, %%rsp; "
					    innocent_pear_PREFIX(6)
					    "pushq %1; "
					    "pushq %2; "
					    "movq %0, (%%rsp); "
					    innocent_pear_BR_PREFIX(7)
					    "lretq %4"
					    : /* no outputs */
					    : "r" (q), "r" (r),
					      "g" ((uint64_t)x), "r" (rzsz),
					      "n" (rzsz), "n" (Which3),
					      "n" (Which4), "n" (Which5)
					    : /* no clobbers */
					    : foo);  break;
#   else
				    case 1:
					__asm goto(innocent_pear_PREFIX(1)
						   "pushl %0; "
						   innocent_pear_BR_PREFIX(2)
						   "retl"
					    : /* no outputs */
					    : "r" (q), "n" (Which3),
					      "n" (Which4)
					    : /* no clobbers */
					    : foo);  break;
				    case 2:
					__asm goto(innocent_pear_PREFIX(2)
						   "pushl %1; "
						   innocent_pear_PREFIX(3)
						   "pushl %0; "
						   innocent_pear_BR_PREFIX(4)
						   "lretl"
					    : /* no outputs */
					    : "r" (q), "r" (r), "n" (Which3),
					      "n" (Which4), "n" (Which5)
					    : /* no clobbers */
					    : foo);  break;
				    case 3:
					__asm goto(
					    "pushl %1; "
					    "movl %0, (%%esp); "
					    innocent_pear_BR_PREFIX(2)
					    "retl"
					    : /* no outputs */
					    : "r" (q), "g" ((uint32_t)x),
					      "n" (Which3)
					    : /* no clobbers */
					    : foo);  break;
				    case 4:
					__asm goto(
					    innocent_pear_PREFIX(3)
					    "pushl %1; "
					    "pushl %2; "
					    "movl %0, (%%esp); "
					    innocent_pear_BR_PREFIX(4)
					    "lretl"
					    : /* no outputs */
					    : "r" (q), "r" (r),
					      "g" ((uint32_t)x), "n" (Which3),
					      "n" (Which4)
					    : /* no clobbers */
					    : foo);  break;
				    case 5:
					__asm goto(
					    innocent_pear_PREFIX(2)
					    "pushfl; "
					    innocent_pear_PREFIX(3)
					    "pushl %1; "
					    innocent_pear_PREFIX(4)
					    "pushl %0; "
					    innocent_pear_BR_PREFIX(5)
					    "iretl"
					    : /* no outputs */
					    : "r" (q), "r" (r), "n" (Which3),
					      "n" (Which4), "n" (Which5),
					      "n" (Which6)
					    : /* no clobbers */
					    : foo);  break;
#   endif
				}
			    bar:
				{
					omg_impl_0<NewState2, Levels - 1>();
				}
			    foo:
				;
			}
			break;
#elif (defined __arm__ || defined __thumb__) && \
    defined innocent_pear_HAVE_ASM_GOTO
		    case 5:
		    case 6:
			{
#   if defined __thumb__
				kthxbai<NewState, void *, Flags, Levels - 1>
				    p((char *)&&foo + 1, 1);
#   else
				kthxbai<NewState, void *, Flags, Levels - 1>
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
#   if defined __thumb2__ || !defined __thumb__
					    case 1:
						__asm goto("ldr pc, %0"
						    : /* no outputs */
						    : "m" (q)
						    : /* no clobbers */
						    : foo);  break;
#   endif
#   ifdef __THUMB_INTERWORK__
					    case 2:
						__asm goto("bx %0"
						    : /* no outputs */
						    : "r" (q)
						    : /* no clobbers */
						    : foo);  break;
	// blx is supported only from ARMv5T onwards
#	if !defined __ARM_ARCH_4__ && !defined __ARM_ARCH_4T__
					    case 3:
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
					omg_impl_0<NewState2, Levels - 1>();
					__asm __volatile(".ltorg");
				}
			    foo:
				;
			}
			// fall through
#endif
		    default:
			{
				omg<NewState, T, Flags, Levels - 1>();
				omg<NewState2, T, Flags, Levels - 1>();
			}
		}
	}
	__attribute__((always_inline))
	omg(T& x)
	{
		using namespace innocent_pear::ops;
		switch ((State2 >> 32) % 11) {
		    case 0:
		    case 1:
			{
				T y;
				omg<NewState, T, Flags, Levels - 1> zomg(x);
				omg<NewState2, T, Flags, Levels - 1> zomg2(y);
				__asm __volatile(""
				    : "=g" (x)
				    : "0" (do_op<pick_hi<unsigned>(NewState3)>
					   (x, y)));
			}
			break;
		    case 2:
		    case 3:
			{
				omg<NewState, T, Flags, Levels>();
				__asm __volatile("" : "=g" (x));
			}
			break;
		    case 4:
		    case 5:
			if (!(Flags & allow_signal_safes)) {
				x = static_cast<T>(rofl2::getppid());
				break;
			} // else fall through
		    case 6:
		    case 7:
			if (!(Flags & allow_signal_safes)) {
				x = static_cast<T>(rofl2::getpid());
				break;
			} // else fall through
		    case 8:
		    case 9:
			if (!(Flags & allow_signal_safes)) {
				x = static_cast<T>(rofl2::time(0));
				break;
			} // else fall through
		    default:
			{
				kthxbai_impl<NewState2, T, Flags, Levels - 1>
				    (x, pick_hi<T>(NewState));
			}
		}
	}
};

#if defined __amd64__ || defined __i386__
#   undef innocent_pear_PREFIX
#   undef innocent_pear_BR_PREFIX
#endif

} // innocent_pear::impl

using impl::omg;

} // innocent_pear

#endif
