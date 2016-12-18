#ifndef innocent_pear_H_OMG
#define innocent_pear_H_OMG

#include <cinttypes>
#include <csignal>
#include <cstring>
#include <unistd.h>
#include <innocent-pear/bbq.h>
#include <innocent-pear/kthxbai.h>
#include <innocent-pear/nowai.h>
#include <innocent-pear/rofl.h>
#include <innocent-pear/teh.h>
#include <innocent-pear/tfw.h>
#include <innocent-pear/unpossible.h>
#include <innocent-pear/yarly.h>
#ifdef __unix__
#   include <fcntl.h>
#endif
#ifdef innocent_pear_DEBUG
#   include <cstdio>
#   include <cstdlib>
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

template<rand_state_t State, unsigned Levels>
struct unpossible;  // forward

template<rand_state_t State, class T,
    ops_flags_t Flags = innocent_pear::ops::allow_minimal,
    unsigned Levels = 2u>
class omg;

template<rand_state_t State, class T, ops_flags_t Flags>
class omg<State, T, Flags, ~0u> : public nowai
	{ };

template<rand_state_t State, class T, ops_flags_t Flags>
class
#ifdef __ELF__
__attribute__((visibility("hidden")))
#endif
omg<State, T, Flags, 0u>
{
    public:
	innocent_pear_always_inline
	omg(T& x, bool bogo = false)
	{
		constexpr rand_state_t
		    State2 = update_inner(State),
		    State3 = update_inner(State2),
		    State4 = update_inner(State3),
		    State5 = update_inner(State4);
		constexpr unsigned Which = (State2 >> 16) % 37;
		constexpr unsigned WhichPfx = (State3 >> 32) % 6;
#if defined __amd64__ || defined __i386__ || defined __arm__
		uintptr_t y, z;
#   ifndef __arm__
		struct { uintptr_t h, l; } dt;
		unsigned w;
		unsigned short h;
#   endif
#endif
		switch (Which) {
#if defined __amd64__ || defined __i386__
		    case 0:
		    case 1:
#   if defined __amd64__
			__asm(innocent_pear_X86_PREFIX(1) "rdtsc"
			    : "=a" (y) : "n" (WhichPfx) : "rdx");
			x = static_cast<T>(y);
			break;
#   elif defined __i486__ || defined __i586__ || defined __i686__
			__asm(innocent_pear_X86_PREFIX(1) "rdtsc"
			    : "=a" (y) : "n" (WhichPfx) : "edx");
			x = static_cast<T>(y);
			break;
#   endif
		    case 2:
		    case 3:
			__asm(innocent_pear_X86_PREFIX(1) "smsw %0"
			    : "=r" (w) : "n" (WhichPfx));
			x = static_cast<T>(w);
			break;
		    case 4:
		    case 5:
			__asm(innocent_pear_X86_PREFIX(1) "sldt %0"
			    : "=r" (w) : "n" (WhichPfx));
			x = static_cast<T>(w);
			break;
		    case 6:
		    case 7:
			__asm __volatile("sgdt %0" : "=m" (dt));
			x = static_cast<T>(Which % 2 ? dt.h : dt.l);
			break;
		    case 8:
		    case 9:
			__asm __volatile("sidt %0" : "=m" (dt));
			x = static_cast<T>(Which % 2 ? dt.h : dt.l);
			break;
		    case 10:
			__asm __volatile("" : "=a" (z));
			__asm __volatile(innocent_pear_X86_PREFIX(2) "cbtw"
			    : "=a" (y) : "0" (z), "n" (WhichPfx));
			x = static_cast<T>(y);
			break;
		    case 11:
			__asm __volatile("" : "=a" (z));
			__asm __volatile(innocent_pear_X86_PREFIX(2) "cwtl"
			    : "=a" (y) : "0" (z), "n" (WhichPfx));
			x = static_cast<T>(y);
			break;
#   ifdef __amd64__
		    case 12:
			__asm __volatile("" : "=a" (z));
			__asm __volatile(innocent_pear_X86_PREFIX(2) "cltq"
			    : "=a" (y) : "0" (z), "n" (WhichPfx));
			x = static_cast<T>(y);
			break;
		    case 13:
			__asm __volatile(innocent_pear_X86_PREFIX(1) "cqto"
			    : "=d" (y) : "n" (WhichPfx));
			x = static_cast<T>(y);
			break;
#   endif
		    case 14:
			__asm __volatile(innocent_pear_X86_PREFIX(1) "clc"
			    : "=r" (y) : "n" (WhichPfx) : "cc");
			x = static_cast<T>(y);
			break;
		    case 15:
			__asm __volatile(innocent_pear_X86_PREFIX(1) "stc"
			    : "=r" (y) : "n" (WhichPfx) : "cc");
			x = static_cast<T>(y);
			break;
		    case 16:
			__asm __volatile(innocent_pear_X86_PREFIX(1) "cmc"
			    : "=r" (y) : "n" (WhichPfx) : "cc");
			x = static_cast<T>(y);
			break;
		    case 17:
			__asm __volatile(innocent_pear_X86_PREFIX(1) "cld"
			    : "=r" (y) : "n" (WhichPfx) : "cc");
			x = static_cast<T>(y);
			break;
			/*
			 * Nope, do _not_ try to use `std' here.  The glibc
			 * runtime depends on the direction flag being clear.
			 *
			 * -- 20150608
			 */
		    case 18:
			__asm __volatile(innocent_pear_X86_PREFIX(1) "nop"
			    : "=r" (y) : "n" (WhichPfx));
			x = static_cast<T>(y);
			break;
		    case 19:
		    case 20:
			__asm __volatile(innocent_pear_X86_PREFIX(1) "verr %0"
			    : "=r" (h) : "n" (WhichPfx) : "cc");
			x = static_cast<T>(h);
			break;
		    case 21:
		    case 22:
			__asm __volatile(innocent_pear_X86_PREFIX(1) "verw %0"
			    : "=r" (h) : "n" (WhichPfx) : "cc");
			x = static_cast<T>(h);
			break;
#elif defined __arm__ && defined __thumb2__
		    case 0:
		    case 1:
			__asm("mrs %0, CPSR" : "=r" (y));
			x = static_cast<T>(y);
			break;
		    case 2:
		    case 3:
			__asm __volatile("sxtb %0, %1" : "=r" (y), "=r" (z));
			x = static_cast<T>(y);
			break;
		    case 4:
		    case 5:
			__asm __volatile("sxtb16 %0, %1" : "=r" (y), "=r" (z));
			x = static_cast<T>(y);
			break;
		    case 6:
		    case 7:
			__asm __volatile("sxth %0, %1" : "=r" (y), "=r" (z));
			x = static_cast<T>(y);
			break;
		    case 8:
		    case 9:
			__asm __volatile("uxtb %0, %1" : "=r" (y), "=r" (z));
			x = static_cast<T>(y);
			break;
		    case 10:
		    case 11:
			__asm __volatile("uxtb16 %0, %1" : "=r" (y), "=r" (z));
			x = static_cast<T>(y);
			break;
		    case 12:
		    case 13:
			__asm __volatile("uxth %0, %1" : "=r" (y), "=r" (z));
			x = static_cast<T>(y);
			break;
		    case 14:
		    case 15:
			__asm __volatile("msr CPSR_f, %0" : "=r" (y) : : "cc");
			x = static_cast<T>(y);
			break;
		    case 16:
		    case 17:
			__asm __volatile("tst %0, %1" : "=r" (y), "=r" (z)
			    : : "cc");
			x = static_cast<T>(y);
			break;
		    case 18:
		    case 19:
			__asm __volatile("teq %0, %1" : "=r" (y), "=r" (z)
			    : : "cc");
			x = static_cast<T>(y);
			break;
		    case 20:
		    case 21:
			__asm __volatile("nop" : "=r" (y));
			x = static_cast<T>(y);
			break;
#endif
		    case 35:
		    case 36:
			if (bogo)
				unpossible<State3, 0>();
			// fall through
		    default:
			if ((State2 >> 16) % 4 == 0) {
				constexpr T v = pick_hi<T>(State4);
				kthxbai_impl<State5, T, Flags, 0>(x, v);
			} else
				__asm __volatile("" : "=g" (x));
		}
	}
	innocent_pear_always_inline
	omg()
	{
		T x;
		omg(x, false);
	}
};

template<rand_state_t State, class T, ops_flags_t Flags, unsigned Levels>
class
#ifdef __ELF__
__attribute__((visibility("hidden")))
#endif
omg
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
	    State12 = update_inner(State11),
	    NewState = update_outer(State, Levels),
	    NewState2 = update_outer(NewState, Levels),
	    NewState3 = update_outer(NewState2, Levels),
	    NewState4 = update_outer(NewState3, Levels),
	    NewState5 = update_outer(NewState4, Levels),
	    NewState6 = update_outer(NewState5, Levels);
	static constexpr unsigned char
	    Frob0 = pick_hi<unsigned char>(State2  ^ State3),
	    Frob1 = pick_hi<unsigned char>(State3  ^ State4),
	    Frob2 = pick_hi<unsigned char>(State4  ^ State5),
	    Frob3 = pick_hi<unsigned char>(State5  ^ State6),
	    Frob4 = pick_hi<unsigned char>(State6  ^ State7),
	    Frob5 = pick_hi<unsigned char>(State7  ^ State8),
	    Frob6 = pick_hi<unsigned char>(State8  ^ State9),
	    Frob7 = pick_hi<unsigned char>(State9  ^ State10),
	    Frob8 = pick_hi<unsigned char>(State10 ^ State11),
	    Frob9 = pick_hi<unsigned char>(State11 ^ State12);
	typedef kthxbai<NewState, unsigned, Flags, Levels - 1> kthxbai1;
	typedef rofl<NewState2, Flags, Levels - 1> rofl2;
	typedef rofl<NewState3, Flags, Levels - 1> rofl3;
	typedef rofl<NewState4, Flags, Levels - 1> rofl4;
#ifdef __amd64__
	innocent_pear_always_inline
	static void coax_nonleaf()
	{
		unpossible<NewState4, Levels - 1>();
		/*
		 * Coax the compiler into not setting up a "red zone" above
		 * the stack pointer, by making it compile a function call.
		 */
		void (*p)();
		__asm __volatile("" : "=g" (p));
		p();
	}
#endif
#if defined innocent_pear_DEBUG || \
    defined innocent_pear_DEBUG_WHEEE
    public:
#endif
	innocent_pear_always_inline
	static bool wheee()
	{
#if defined innocent_pear_DEBUG && innocent_pear_HAVE_ASM_GOTO
		static volatile unsigned long k_ = 0;
		unsigned long k = __atomic_fetch_add(&k_, 1, __ATOMIC_SEQ_CST);
		if (k > 200)
			return true;
		std::fprintf(stderr, "wheee() %#" PRIxLEAST64 " %#x %u "
		    "@%p%s\n", State, (unsigned)Flags, Levels, &&qux,
		    k == 200 ? "..." : "");
	    qux:
#endif
#if (defined __amd64__ || defined __i386__ ) && \
    defined innocent_pear_HAVE_ASM_GOTO
		constexpr bool Flip = (State4 >> 63) % 2 != 0;
#   ifdef __amd64__
		constexpr unsigned Which2 = (State2 >> 40) % 3;
#   else
		constexpr unsigned Which2 = (State2 >> 40) % 5;
#   endif
		constexpr unsigned Which3 = (State3 >> 40) % 15;
		constexpr unsigned Which4 = (State4 >> 40) % 15;
		constexpr unsigned Which5 = (State5 >> 40) % 15;
		constexpr unsigned Which6 = (State6 >> 40) % 15;
		constexpr unsigned Push4 = (State4 >> 48) % 0x1ff;
		constexpr unsigned Push5 = (State5 >> 48) % 0x1ff;
		kthxbai<NewState, void *, Flags, Levels - 1>
		    p(Flip ? &&bar : &&foo, 1);
		void *q, *r = 0;
#   ifdef innocent_pear_DEBUG
		std::fprintf(stderr, "wheee() %#" PRIxLEAST64 ": "
		    "Which2 = %u, Flip = %s, NewState4 = %#" PRIxLEAST64 "\n",
		    State, Which2, Flip ? "true" : "false", NewState4);
#   endif
		if (Flip) {
			if ((bool)tfw<NewState4, T, Flags, Levels - 1>())
				return true;
#   ifdef innocent_pear_DEBUG
			std::fprintf(stderr, "wheee() %#" PRIxLEAST64
			    ": UNPOSSIBLE!!!1 @%p\n", State, &&quux);
	    quux:	std::abort();
#   endif
		} else {
			if (!tfw<NewState4, T, Flags, Levels - 1>()) {
#   ifdef innocent_pear_DEBUG
				std::fprintf(stderr, "wheee() %#" PRIxLEAST64
				    ": UNPOSSIBLE!!!1 @%p\n", State, &&quuux);
	    quuux:		std::abort();
#   endif
				goto bar;
			}
		}
		__asm("movw %%cs, %w0" : "=g" (r));
		q = static_cast<void *>(p);
#   ifdef innocent_pear_DEBUG
		std::fprintf(stderr, "wheee() %#" PRIxLEAST64 ": q = %p\n",
		    State, q);
#   endif
		switch (Which2) {
		    default:
			__asm goto(innocent_pear_X86_BR_PREFIX(1) "jmp%z0 *%0"
			    : /* no outputs */
			    : "r" (q), "n" (Which3)
			    : /* no clobbers */
			    : foo, bar);  break;
#   ifdef __amd64__
		    case 1:
			__asm goto(innocent_pear_X86_PREFIXED_PUSH(1, 2, 0)
				   innocent_pear_X86_BR_PREFIX(3) "retq"
			    : /* no outputs */
			    : "r" (q), "n" (Which4), "n" (Push4), "n" (Which5)
			    : "memory"
			    : foo, bar);
			coax_nonleaf();
			break;
		    case 2:
			__asm goto(innocent_pear_X86_PREFIXED_PUSH(2, 3, 1)
				   innocent_pear_X86_PREFIXED_PUSH(4, 5, 0)
				   innocent_pear_X86_BR_PREFIX(6) "lretq"
			    : /* no outputs */
			    : "r" (q), "r" (r), "n" (Which4), "n" (Push4),
			      "n" (Which5), "n" (Push5), "n" (Which6)
			    : "memory"
			    : foo, bar);
			coax_nonleaf();
			break;
#   else
		    case 1:
			__asm goto(innocent_pear_X86_PREFIXED_PUSH(2, 3, 0)
				   innocent_pear_X86_BR_PREFIX(1) "retl"
			    : /* no outputs */
			    : "r" (q), "n" (Which3), "n" (Which4), "n" (Push4)
			    : "memory"
			    : foo, bar);  break;
		    case 2:
			__asm goto(innocent_pear_X86_PREFIXED_PUSH(3, 4, 1)
				   innocent_pear_X86_PREFIXED_PUSH(5, 6, 0)
				   innocent_pear_X86_BR_PREFIX(2) "lretl"
			    : /* no outputs */
			    : "r" (q), "r" (r), "n" (Which3), "n" (Which4),
			      "n" (Push4), "n" (Which5), "n" (Push5)
			    : "memory"
			    : foo, bar);  break;
		    case 3:
			__asm goto(innocent_pear_X86_PREFIX(2) "pushfl; "
				   innocent_pear_X86_PREFIXED_PUSH(3, 4, 1)
				   innocent_pear_X86_PREFIXED_PUSH(5, 6, 0)
				   innocent_pear_X86_BR_PREFIX(7) "iretl"
			    : /* no outputs */
			    : "r" (q), "r" (r), "n" (Which3), "n" (Which4),
			      "n" (Push4), "n" (Which5), "n" (Push5),
			      "n" (Which6)
			    : "memory"
			    : foo, bar);  break;
		    case 4:
			{
				struct { void *qq, *rr; } qr = { q, r };
				__asm goto("ljmpl *%0"
				    : /* no outputs */
				    : "m" (qr)
				    : /* no clobbers */
				    : foo, bar);
			}
			break;
#   endif
		}
		{ unpossible<NewState2, Levels - 1>(); }
	    bar:
		{ unpossible<NewState3, Levels - 1>(); }
	    foo:
#   ifdef innocent_pear_DEBUG
		std::fprintf(stderr, "wheee() %#" PRIxLEAST64 ": w00t\n",
		    State);
#   endif
		return true;
#elif (defined __arm__ || defined __thumb__) && \
    defined innocent_pear_HAVE_ASM_GOTO
		constexpr bool Flip = (State4 >> 63) % 2 != 0;
		constexpr unsigned Which2 = (State2 >> 56) % 8;
#   if defined __THUMB_INTERWORK__ && defined __ELF__
		static constexpr unsigned Subsxn =
		    pick_hi<unsigned>(State3 ^ State4) % 4096 + 1u;
#   endif
#   if defined __thumb__
		kthxbai<NewState, void *, Flags, Levels - 1>
		    p((char *)(Flip ? &&bar : &&foo) + 1, 1);
#   else
		kthxbai<NewState, void *, Flags, Levels - 1>
		    p(Flip ? &&bar : &&foo, 1);
#   endif
		void *q = static_cast<void *>(p);
		if (Flip) {
			if ((bool)tfw<NewState4, T, Flags, Levels - 1>())
				return true;
#   ifdef innocent_pear_DEBUG
			std::fprintf(stderr, "wheee() %#" PRIxLEAST64
			    ": UNPOSSIBLE!!!1 @%p\n", State, &&quux);
	    quux:	std::abort();
#   endif
		} else {
			if (!tfw<NewState4, T, Flags, Levels - 1>()) {
#   ifdef innocent_pear_DEBUG
				std::fprintf(stderr, "wheee() %#" PRIxLEAST64
				    ": UNPOSSIBLE!!!1 @%p\n", State, &&quuux);
	    quuux:		std::abort();
#   endif
				goto bar;
			}
		}
		switch (Which2) {
		    default:
			__asm goto("mov pc, %0" : : "r" (q) : : foo, bar);
			break;
#   if defined __thumb2__ || !defined __thumb__
		    case 1:
			__asm goto("ldr pc, %0" : : "m" (q) : : foo, bar);
			break;
#   endif
#   ifdef __THUMB_INTERWORK__
		    case 2:
			__asm goto("bx %0" : : "r" (q) : : foo, bar);  break;
	// blx is supported only from ARMv5T onwards
#	if !defined __ARM_ARCH_4__ && !defined __ARM_ARCH_4T__
		    case 3:
		    case 4:
			__asm goto("blx %0" : : "r" (q) : "lr" : foo, bar);
			break;
#	endif
#	ifdef __ELF__
		    case 5:
		    case 6:
			/*
			 * Mark ip as being clobbered, _in case_ the compiler
			 * one day decides to use a veneer to reach 0f...
			 */
			__asm goto("bl 0f; "
				   ".subsection %a1; "
#	    ifdef __thumb__
				   ".thumb_func; "
#	    endif
				   "0: "
				   "bx %0; "
				   ".previous"
			    : /* no outputs */
			    : "r" (q), "n" (Subsxn)
			    : "ip", "lr"
			    : foo, bar);
			break;
#	    if defined __thumb__ && defined __ARM_ARCH_ISA_ARM
		    case 7:
			__asm goto("blx 0f; "
				   ".subsection %a1; "
				   ".arm; "
				   ".balign 4; "
				   "0: "
				   "bx %0; "
				   ".thumb; "
				   ".previous"
			    : /* no outputs */
			    : "r" (q), "n" (Subsxn)
			    : "ip", "lr"
			    : foo, bar);
			break;
#	    endif
#	endif
#   endif
		}
		{ unpossible<NewState2, Levels - 1>(); }
	    bar:
		{
			unpossible<NewState3, Levels - 1>();
			__asm __volatile(".ltorg");
		}
	    foo:
#   ifdef innocent_pear_DEBUG
		std::fprintf(stderr, "wheee() %#" PRIxLEAST64 ": w00t\n",
		    State);
#   endif
		return true;
#else
		return false;
#endif
	}
    public:
	innocent_pear_always_inline
	static bool special(T& x, bool bogo = false)
	{
		using namespace innocent_pear::ops;
		constexpr unsigned Which2 = (State2 >> 56) % 8;
		pid_t pid;
#ifdef innocent_pear_HAVE_CONST_TCOOFF
		int fd;
#endif
#if defined innocent_pear_HAVE_FUNC_PRCTL && \
    defined innocent_pear_HAVE_CONST_PR_SET_DUMPABLE
		unsigned long zero;
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
				char& cfn0 = teh<char, '/' ^ Frob0>::x;
				char& cfn1 = teh<char, 'd' ^ Frob1>::x;
				char& cfn2 = teh<char, 'e' ^ Frob2>::x;
				char& cfn3 = teh<char, 'v' ^ Frob3>::x;
				char& cfn4 = teh<char, '/' ^ Frob4>::x;
				char& cfn5 = teh<char, 't' ^ Frob5>::x;
				char& cfn6 = teh<char, 't' ^ Frob6>::x;
				char& cfn7 = teh<char, 'y' ^ Frob7>::x;
				char& cfn8 = teh<char,	     Frob8>::x;
				char& cfn9 = teh<char,	     Frob9>::x;
				char fn[9];
				fn[0] = cfn0 ^ Frob0;
				fn[1] = cfn1 ^ Frob1;
				fn[2] = cfn2 ^ Frob2;
				fn[3] = cfn3 ^ Frob3;
				fn[4] = cfn4 ^ Frob4;
				fn[5] = cfn5 ^ Frob5;
				fn[6] = cfn6 ^ Frob6;
				fn[7] = cfn7 ^ Frob7;
				fn[8] = cfn8 ^ Frob8;
				fd = rofl2::open(fn, O_RDONLY);
				fn[0] = fn[1] = fn[2] = fn[3] = fn[4] =
				    fn[5] = fn[6] = fn[7] = fn[8] = cfn9;
			}
			break;
#   endif
#endif
#if defined innocent_pear_HAVE_FUNC_PRCTL && \
    defined innocent_pear_HAVE_CONST_PR_SET_DUMPABLE
		    case 6:
		    case 7:
			zero = (unsigned long)kthxbai1(0);
#endif
		}
		omg<NewState5, T, Flags, Levels - 1> zomg(x, bogo);
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
#if defined innocent_pear_HAVE_FUNC_PRCTL && \
    defined innocent_pear_HAVE_CONST_PR_SET_DUMPABLE
		    case 6:
		    case 7:
			rofl2::prctl(innocent_pear_VAL_CONST_PR_SET_DUMPABLE,
			    zero);
#endif
		}
		return true;
	}
	innocent_pear_always_inline
	static bool special()
	{
		T x;
		return special(x, false);
	}
	innocent_pear_always_inline
	omg(T& x, bool bogo = false)
	{
		using namespace innocent_pear::ops;
		constexpr unsigned Bit = pick_hi<unsigned>(State2 ^ State3)
		    % (sizeof(T) * CHAR_BIT);
		switch ((State2 >> 48) % 25) {
		    case 0:
		    case 1:
		    case 2:
			{
				T y;
				omg<NewState, T, Flags, Levels - 1>
				    zomg(x, bogo);
				omg<NewState2, T, Flags, Levels - 1>
				    zomg2(y, bogo);
				__asm __volatile(""
				    : "=g" (x)
				    : "0" (do_op<pick_hi<unsigned>(NewState3)>
					   (x, y)));
			}
			break;
		    case 3:
		    case 4:
		    case 5:
		    case 6:
			{
				T x1;
				omg<NewState, T, Flags, Levels - 1> zomg1(x1);
				if (bit_set(x1, Bit)) {
					omg<NewState2, T, Flags, Levels - 1>
					    zomg(x);
				} else {
					omg<NewState3, T, Flags, Levels - 1>
					    zomg(x);
				}
			}
			break;
		    case 7:
		    case 8:
			if (!(Flags & allow_signal_safes)) {
				x = static_cast<T>(rofl2::getppid());
				break;
			}
			if (false)
		    case 9:
		    case 10:
			if (!(Flags & allow_signal_safes)) {
				x = static_cast<T>(rofl2::getpid());
				break;
			}
			if (false)
		    case 11:
		    case 12:
			if (!(Flags & allow_signal_safes)) {
				union {
					time_t t;
					uint_least64_t i;
				} u;
				kthxbai<NewState, time_t *, Flags,
				    Levels - 1> p(&u.t);
				x = static_cast<T>(rofl2::time((time_t *)p));
				break;
			}
			if (false)
		    case 13:
			{
				kthxbai_impl<NewState2, T, Flags, Levels - 1>
				    (x, pick_hi<T>(NewState));
			}
			if (false)
		    case 14:
		    case 15:
			if (special(x, bogo))
				return;
			if (false)
		    case 16:
		    case 17:
			if (wheee()) {
				omg<NewState6, T, Flags, Levels - 1>
				    zomg(x, bogo);
				return;
			}
			if (false)
		    case 18:
		    case 19:
			{
				constexpr uintptr_t N = (State3 >> 48) % 256;
				constexpr unsigned WhichOp =
				    (unsigned)(State4 >> 16);
				T w, y, z;
				uintptr_t c;
				{
					kthxbai_impl<NewState, uintptr_t,
					    Flags, Levels - 1>(c, N);
					omg<NewState2, T, Flags, Levels - 1>
					    (y, bogo);
				}
				while (c-- != 0) {
					omg<NewState3, T, Flags, Levels - 1>
					    (z, bogo);
					kthxbai_impl<NewState4, T, Flags, 0>
					    (w, do_inv_op<WhichOp>(y, z));
					y = w;
				}
				kthxbai_impl<NewState5, T, Flags, 0>(x, y);
				break;
			}
			if (false)
		    case 20:
		    case 21:
			if (bogo)
				unpossible<NewState3, Levels - 1>();
			// fall through
		    default:
			{
				T x1;
				lolwut<NewState, T, Flags, Levels-1> p1(&x1);
				lolwut<NewState2, T, Flags, Levels-1> p2(&x1);
				{
					omg<NewState4, T, Flags, Levels - 1>
					    (*p1, bogo);
				}
				kthxbai_impl<NewState5, T, Flags, 0>(x, *p2);
			}

		}
	}
	innocent_pear_always_inline
	omg()
	{
		T x;
		omg(x, false);
	}
};

} // innocent_pear::impl

using impl::omg;

} // innocent_pear

#endif
