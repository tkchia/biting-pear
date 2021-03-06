#ifndef innocent_pear_H_OMG
#define innocent_pear_H_OMG

#include <cinttypes>
#include <csignal>
#include <cstring>
#include <unistd.h>
#include <innocent-pear/bbq.h>
#include <innocent-pear/dawg.h>
#include <innocent-pear/kthxbai.h>
#include <innocent-pear/nowai.h>
#include <innocent-pear/orly.h>
#include <innocent-pear/rofl.h>
#include <innocent-pear/teh.h>
#include <innocent-pear/tfw.h>
#include <innocent-pear/unpossible.h>
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

template<rand_state_t State, class T, bool Boreal, bool BigBad,
    ops_flags_t Flags, unsigned Levels>
class orly;  // forward

template<impl::rand_state_t State, ops_flags_t Flags, unsigned Levels>
class rofl;  // forward

template<rand_state_t State, class CT, ops_flags_t Flags, unsigned Levels,
    CT... Chs>
class dawg_impl_2;  // forward

template<rand_state_t State, class T, unsigned Levels>
class unpossible;  // forward

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
	omg(T& x)
	{
		using namespace innocent_pear::ops;
		constexpr rand_state_t
		    State2 = update_inner(State),
		    State3 = update_inner(State2),
		    State4 = update_inner(State3),
		    State5 = update_inner(State4);
		constexpr unsigned Which = (State2 >> 16) % 37;
		constexpr unsigned WhichPfx = (State3 >> 32) % 6;
#if defined __amd64__ || defined __i386__ || defined __ia16__ || \
    defined __arm__
			/* Really only used for x86-64/-32/-16. */
		constexpr uint_least8_t WhichJunk = State4 >> 56;
		uintptr_t y, z;
#   ifndef __arm__
#	ifdef __ia16__
		struct { uint_least32_t l, h; } dt;
#	else
		struct { uintptr_t l, h; } dt;
#	endif
		unsigned w;
#   endif
#endif
		switch (Which) {
#if defined __amd64__ || defined __i386__ || defined __ia16__
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
#   if !defined __ia16__ || defined __IA16_ARCH_I80286
		    case 2:
		    case 3:
			__asm(innocent_pear_X86_PREFIX(1) "smsw %0"
			    : "=r" (w) : "n" (WhichPfx));
			x = static_cast<T>(w);
			break;
#	ifndef __ia16__
		    case 4:
		    case 5:
			__asm(innocent_pear_X86_PREFIX(1) "sldt %0"
			    : "=r" (w) : "n" (WhichPfx));
			x = static_cast<T>(w);
			break;
#	endif
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
#   endif
		    case 10:
			__asm __volatile("" : "=a" (z));
			__asm __volatile(innocent_pear_X86_PREFIX(2) "cbtw"
			    : "=a" (y) : "0" (z), "n" (WhichPfx));
			x = static_cast<T>(y);
			break;
		    case 11:
			__asm __volatile(innocent_pear_X86_PREFIX(1) "cwtd"
			    : "=d" (y) : "n" (WhichPfx));
			x = static_cast<T>(y);
			break;
#   ifndef __ia16__
		    case 12:
			__asm __volatile("" : "=a" (z));
			__asm __volatile(innocent_pear_X86_PREFIX(2) "cwtl"
			    : "=a" (y) : "0" (z), "n" (WhichPfx));
			x = static_cast<T>(y);
			break;
		    case 13:
			__asm __volatile(innocent_pear_X86_PREFIX(1) "cltd"
			    : "=d" (y) : "n" (WhichPfx));
			x = static_cast<T>(y);
			break;
#   endif
#   ifdef __amd64__
		    case 14:
			__asm __volatile("" : "=a" (z));
			__asm __volatile(innocent_pear_X86_PREFIX(2) "cltq"
			    : "=a" (y) : "0" (z), "n" (WhichPfx));
			x = static_cast<T>(y);
			break;
		    case 15:
			__asm __volatile(innocent_pear_X86_PREFIX(1) "cqto"
			    : "=d" (y) : "n" (WhichPfx));
			x = static_cast<T>(y);
			break;
#   endif
		    case 16:
			__asm __volatile(innocent_pear_X86_PREFIX(1) "clc"
			    : "=r" (y) : "n" (WhichPfx) : "cc");
			x = static_cast<T>(y);
			break;
		    case 17:
			__asm __volatile(innocent_pear_X86_PREFIX(1) "stc"
			    : "=r" (y) : "n" (WhichPfx) : "cc");
			x = static_cast<T>(y);
			break;
		    case 18:
			__asm __volatile(innocent_pear_X86_PREFIX(1) "cmc"
			    : "=r" (y) : "n" (WhichPfx) : "cc");
			x = static_cast<T>(y);
			break;
		    case 19:
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
		    case 20:
			__asm __volatile(innocent_pear_X86_PREFIX(1) "nop"
			    : "=r" (y) : "n" (WhichPfx));
			x = static_cast<T>(y);
			break;
#   ifndef __ia16__
			/*
			 * These opcodes do exist on the i80286, but they only
			 * really work in protected mode!
			 */
		    case 21:
		    case 22:
			__asm __volatile(innocent_pear_X86_PREFIX(1) "verr %w0"
			    : "=r" (y) : "n" (WhichPfx) : "cc");
			x = static_cast<T>(y);
			break;
		    case 23:
		    case 24:
			__asm __volatile(innocent_pear_X86_PREFIX(1) "verw %w0"
			    : "=r" (y) : "n" (WhichPfx) : "cc");
			x = static_cast<T>(y);
			break;
#   endif
#   ifndef __amd64__	/*
			 * Some x86-64 machines understand `lahf' and `sahf'
			 * -- but apparently not all.  As for `salc', it is
			 * undocumented and does not work on my box anyway...
			 */
		    case 25:
			__asm __volatile(innocent_pear_X86_PREFIX(1) "lahf"
			    : "=a" (y) : "n" (WhichPfx));
			x = static_cast<T>(y);
			break;
		    case 26:
			__asm __volatile(innocent_pear_X86_PREFIX(1) "sahf"
			    : "=r" (y) : "n" (WhichPfx) : "cc");
			x = static_cast<T>(y);
			break;
		    case 27:
		    case 28:
		    case 29:
			__asm __volatile(innocent_pear_X86_PREFIX(1)
					 ".byte 0xd6"	/* salc */
			    : "=a" (y) : "n" (WhichPfx));
			x = static_cast<T>(y);
			break;
#   endif
		    case 30:
		    case 31:
		    case 32:
		    case 33:
			__asm __volatile(innocent_pear_X86_PREFIX(1) "jmp 1f; "
					 ".byte %c2; "
					 "1:"
			    : "=r" (y) : "n" (WhichPfx), "n" (WhichJunk));
			x = static_cast<T>(y);
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
			if ((Flags & under_unpossible) != 0)
				unpossible<State3, T, 0> un(x);
			// fall through
		    default:
			if ((State2 >> 16) % 4 == 0) {
				constexpr T v = pick_hi<T>(State4);
				kthxbai_impl<State5, T, Flags, 0>(x, v);
			} else
				__asm __volatile(""
				    : innocent_pear_ASM_GEN_OUT (x));
		}
	}
	innocent_pear_always_inline
	omg()
	{
		T x;
		omg zomg(x);
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
	    NewState = update_outer(State, Levels),
	    NewState2 = update_outer(NewState, Levels),
	    NewState3 = update_outer(NewState2, Levels),
	    NewState4 = update_outer(NewState3, Levels),
	    NewState5 = update_outer(NewState4, Levels),
	    NewState6 = update_outer(NewState5, Levels);
	static constexpr unsigned long
	    Frob = pick_hi<unsigned long>(State7 ^ State8);
	static constexpr bool Boreal1 = (State8 >> 63) % 2 != 0,
			      Boreal2 = (State8 >> 62) % 2 != 0;
	typedef kthxbai<NewState, unsigned, Flags, Levels - 1> kthxbai1;
	typedef rofl<NewState2, Flags, Levels - 1> rofl2;
	typedef rofl<NewState3, Flags, Levels - 1> rofl3;
	typedef rofl<NewState4, Flags, Levels - 1> rofl4;
#ifdef __amd64__
	innocent_pear_always_inline
	static void coax_no_red()
	{
		/*
		 * Coax the compiler into not setting up a "red zone" above
		 * the stack pointer.
		 *
		 * The `__builtin_alloca(0)' method works well and is
		 * practically a no-op on g++, but produces lots of
		 * instructions on clang++.  The "insert indirect call"
		 * method works on clang++ but causes g++ to weird out and
		 * produce bad code.
		 *
		 * Perhaps in the future the `configure' script can be made
		 * to detect the best method to use.
		 */
#   ifndef __clang__
		void *p = __builtin_alloca(0);
		__asm __volatile("" : : "g" (p) : "memory");
#   else
		void (*p)();
		__asm __volatile("" : "=g" (p));
		p();
#   endif
	}
#endif
#if defined innocent_pear_DEBUG || \
    defined innocent_pear_DEBUG_WHEEE
    public:
#endif
	innocent_pear_always_inline
	static bool wheee()
	{
#if (defined __amd64__ /* || defined __i386__ */) && \
    defined innocent_pear_HAVE_ASM_GOTO
		/* Still flaky on x86-32.  Disabled for now there... */
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
		kthxbai<NewState, void *, Flags, Levels - 1> p(&&foo, 1);
		void *q, *r = 0;
		struct { void *qq, *rr; } qr;
		if (Flip) {
			if (tfw<NewState4, T, Flags, Levels - 1>()())
				return true;
		} else {
			if (!tfw<NewState4, T, Flags, Levels - 1>()())
				goto foo;
		}
		__asm("movw %%cs, %w0" : "=g" (r));
		q = static_cast<void *>(p);
		switch (Which2) {
		    default:
			__asm goto(innocent_pear_X86_BR_PREFIX(1) "jmp%z0 *%0"
			    : /* no outputs */
			    : "r" (q), "n" (Which3)
			    : /* no clobbers */
			    : foo);  break;
#   ifdef __amd64__
		    case 1:
			__asm goto(innocent_pear_X86_PREFIXED_PUSH(1, 2, 0)
				   innocent_pear_X86_BR_PREFIX(3) "retq"
			    : /* no outputs */
			    : "r" (q), "n" (Which4), "n" (Push4), "n" (Which5)
			    : "memory"
			    : foo);
			break;
		    case 2:
			__asm goto(innocent_pear_X86_PREFIXED_PUSH(2, 3, 1)
				   innocent_pear_X86_PREFIXED_PUSH(4, 5, 0)
				   innocent_pear_X86_BR_PREFIX(6) "lretq"
			    : /* no outputs */
			    : "r" (q), "r" (r), "n" (Which4), "n" (Push4),
			      "n" (Which5), "n" (Push5), "n" (Which6)
			    : "memory"
			    : foo);
			break;
#   else
		    case 1:
			__asm goto(innocent_pear_X86_PREFIXED_PUSH(2, 3, 0)
				   innocent_pear_X86_BR_PREFIX(1) "retl"
			    : /* no outputs */
			    : "r" (q), "n" (Which3), "n" (Which4), "n" (Push4)
			    : "memory"
			    : foo);  break;
		    case 2:
			__asm goto(innocent_pear_X86_PREFIXED_PUSH(3, 4, 1)
				   innocent_pear_X86_PREFIXED_PUSH(5, 6, 0)
				   innocent_pear_X86_BR_PREFIX(2) "lretl"
			    : /* no outputs */
			    : "r" (q), "r" (r), "n" (Which3), "n" (Which4),
			      "n" (Push4), "n" (Which5), "n" (Push5)
			    : "memory"
			    : foo);  break;
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
			    : foo);  break;
		    case 4:
			qr.qq = q;
			qr.rr = r;
			__asm goto("ljmpl *%0" : : "m" (qr) : : foo);
			break;
#   endif
		}
		{
#   ifdef innocent_pear_DEBUG
			std::fprintf(stderr, "wheee() %#" PRIxLEAST64
			    ": UNPOSSIBLE!!!1 @%p\n", State, &&qux);
	    qux:	std::abort();
#   endif
			unpossible<NewState2, T, Levels - 1>();
#   ifdef __amd64__
			coax_no_red();
#   endif
		}
	    foo:
		if (Flip) {
#   ifdef innocent_pear_DEBUG
			std::fprintf(stderr, "wheee() %#" PRIxLEAST64
			    ": UNPOSSIBLE!!!2 @%p\n", State, &&foo);
	    		std::abort();
#   endif
			unpossible<NewState3, T, Levels - 1>();
		}
		return true;
#elif 0 /* (defined __arm__ || defined __thumb__) && \
    defined innocent_pear_HAVE_ASM_GOTO */
		/* Still flaky on ARM-32.  Disabled for now there... */
		constexpr bool Flip = (State4 >> 63) % 2 != 0;
		constexpr unsigned Which2 = (State2 >> 56) % 8;
#   if defined __THUMB_INTERWORK__ && defined __ELF__
		static constexpr unsigned Subsxn =
		    pick_hi<unsigned>(State3 ^ State4) % 4096 + 1u;
#   endif
#   if defined __thumb__
		kthxbai<NewState, void *, Flags, Levels - 1>
		    p((char *)&&foo + 1, 1);
#   else
		kthxbai<NewState, void *, Flags, Levels - 1> p(&&foo, 1);
#   endif
		void *q = static_cast<void *>(p);
		if (Flip) {
			if (tfw<NewState4, T, Flags, Levels - 1>()())
				return true;
		} else {
			if (!tfw<NewState4, T, Flags, Levels - 1>()())
				goto foo;
		}
		switch (Which2) {
		    default:
			__asm goto("mov pc, %0" : : "r" (q) : : foo);
			break;
#   if defined __thumb2__ || !defined __thumb__
		    case 1:
			__asm goto("ldr pc, %0" : : "m" (q) : : foo);
			break;
#   endif
#   ifdef __THUMB_INTERWORK__
		    case 2:
			__asm goto("bx %0" : : "r" (q) : : foo);  break;
	// blx is supported only from ARMv5T onwards
#	if !defined __ARM_ARCH_4__ && !defined __ARM_ARCH_4T__
		    case 3:
		    case 4:
			__asm goto("blx %0" : : "r" (q) : "lr" : foo);
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
#	    if defined __thumb__ || defined __THUMB_INTERWORK__
				   "bx %0; "
#	    else
				   "mov pc, %0; "
#	    endif
				   ".previous"
			    : /* no outputs */
			    : "r" (q), "n" (Subsxn)
			    : "ip", "lr"
			    : foo);
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
			    : foo);
			break;
#	    endif
#	endif
#   endif
		}
		{
#   ifdef innocent_pear_DEBUG
			std::fprintf(stderr, "wheee() %#" PRIxLEAST64
			    ": UNPOSSIBLE!!!1 @%p\n", State, &&qux);
	    qux:	std::abort();
#   endif
			unpossible<NewState2, T, Levels - 1>();
			__asm __volatile(".ltorg");
		}
	    foo:
		if (Flip) {
#   ifdef innocent_pear_DEBUG
			std::fprintf(stderr, "wheee() %#" PRIxLEAST64
			    ": UNPOSSIBLE!!!2 @%p\n", State, &&foo);
	    		std::abort();
#   endif
			unpossible<NewState3, T, Levels - 1>();
			__asm __volatile(".ltorg");
		}
		return true;
#else
		return false;
#endif
	}
    public:
	innocent_pear_always_inline
	static bool special(T& x)
	{
		using namespace innocent_pear::ops;
		constexpr unsigned Which2 = (State2 >> 32) % 11;
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
			break;
#   ifdef  __unix__
		    case 5:
		    case 6:
			if (!(Flags & under_munged_terminal) ||
			    !(Flags & allow_resource_unsafes))
				return false;
			break;
#   endif
#endif
			/*
			 * Do not use FS_IOC_GETFLAGS and FS_IOC_GETVERSION
			 * if ptrace(...) is unimplemented.  Ugly hack for
			 * testing under Qemu...
			 */
#if defined innocent_pear_HAVE_CONST_FS_IOC_GETFLAGS && \
    defined innocent_pear_HAVE_IMPLD_FUNC_PTRACE
		    case 7:
			if (!(Flags & allow_resource_unsafes))
				return false;
			break;
#endif
#if defined innocent_pear_HAVE_CONST_FS_IOC_GETVERSION && \
    defined innocent_pear_HAVE_IMPLD_FUNC_PTRACE
		    case 8:
			if (!(Flags & allow_resource_unsafes))
				return false;
			break;
#endif
#if defined innocent_pear_HAVE_FUNC_PRCTL && \
    defined innocent_pear_HAVE_CONST_PR_SET_DUMPABLE
		    case 9:
		    case 10:
			if (!(Flags & allow_debugger_unsafes))
				return false;
			break;
#endif
		}
		switch (Which2) {
		    default:
			pid = rofl2::getppid();
			x = (T)pid;
			break;
		    case 1:
			pid = rofl2::getpid();
			x = (T)pid;
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
		    case 6:
			{
				/*
				 * Make the buffer the same size as the
				 * "/proc/self/exe" buffer (below) so that
				 * the code for clearing it will look similar.
				 */
				char fn[15];
				unsigned char *ufn = (unsigned char *)fn;
				dawg_impl_2<NewState, char, Flags, Levels - 1,
				    '/', 'd', 'e', 'v', '/', 't', 't', 'y', 0>
				    () >> fn;
				fd = rofl2::open(fn, O_RDONLY);
				orly<NewState2, unsigned char, Boreal1, false,
				    Flags, 1u>().zot(ufn, ufn + sizeof fn);
			}
			break;
#   endif
#endif
#if defined innocent_pear_HAVE_CONST_FS_IOC_GETFLAGS && \
    defined innocent_pear_HAVE_CONST_FS_IOC_GETVERSION && \
    defined innocent_pear_HAVE_IMPLD_FUNC_PTRACE
#   ifdef innocent_pear_HAVE_CONST_FS_IOC_GETFLAGS
		    case 7:
#   endif
#   ifdef innocent_pear_HAVE_CONST_FS_IOC_GETVERSION
		    case 8:
#   endif
			{
				char fn[15];
				unsigned char *ufn = (unsigned char *)fn;
				dawg_impl_2<NewState, char, Flags, Levels - 1,
				    '/', 'p', 'r', 'o', 'c',
				    '/', 's', 'e', 'l', 'f',
				    '/', 'e', 'x', 'e', 0>() >> fn;
				fd = rofl2::open(fn, O_RDONLY);
				orly<NewState2, unsigned char, Boreal2, false,
				    Flags, 1u>().zot(ufn, ufn + sizeof fn);
			}
			break;

#endif
#if defined innocent_pear_HAVE_FUNC_PRCTL && \
    defined innocent_pear_HAVE_CONST_PR_SET_DUMPABLE
		    case 9:
		    case 10:
			zero = (unsigned long)kthxbai1(0);
#endif
		}
		omg<NewState5, T, Flags, Levels - 1> zomg(x);
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
		    case 6:
			rofl3::tcflow(fd, innocent_pear_VAL_CONST_TCOOFF);
			rofl4::close(fd);
			break;
#   endif
#endif
#if defined innocent_pear_HAVE_CONST_FS_IOC_GETFLAGS && \
    defined innocent_pear_HAVE_IMPLD_FUNC_PTRACE
		    case 7:
			{
				unsigned long fl = Frob;
				rofl3::ioctl(fd,
				    innocent_pear_VAL_CONST_FS_IOC_GETFLAGS,
				    &fl);
				rofl4::close(fd);
				x = (T)fl;
			}
			break;
#endif
#if defined innocent_pear_HAVE_CONST_FS_IOC_GETVERSION && \
    defined innocent_pear_HAVE_IMPLD_FUNC_PTRACE
		    case 8:
			{
				unsigned long fl = Frob;
				rofl3::ioctl(fd,
				    innocent_pear_VAL_CONST_FS_IOC_GETVERSION,
				    &fl);
				rofl4::close(fd);
				x = (T)fl;
			}
			break;
#endif
#if defined innocent_pear_HAVE_FUNC_PRCTL && \
    defined innocent_pear_HAVE_CONST_PR_SET_DUMPABLE
		    case 9:
		    case 10:
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
		return special(x);
	}
	innocent_pear_always_inline
	omg(T& x)
	{
		using namespace innocent_pear::ops;
		constexpr unsigned Bit = pick_hi<unsigned>(State2 ^ State3)
		    % (sizeof(T) * CHAR_BIT);
		switch ((State2 >> 48) % 27) {
		    case 0:
		    case 1:
		    case 2:
			{
				T y;
				omg<NewState, T, Flags, Levels - 1> zomg(x);
				omg<NewState2, T, Flags, Levels - 1> zomg2(y);
				__asm __volatile(""
				    : innocent_pear_ASM_GEN_OUT (x)
				    : innocent_pear_ASM_GEN_MATCH
					(do_op<pick_hi<unsigned>
					    (NewState3)>(x, y)));
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
#ifdef innocent_pear_HAVE_FUNC_GETPPID
		    case 7:
		    case 8:
			if (!(Flags & allow_signal_safes)) {
				x = static_cast<T>(rofl2::getppid());
				break;
			}
			if (false)
#endif
#ifdef innocent_pear_HAVE_FUNC_GETPID
		    case 9:
		    case 10:
			if (!(Flags & allow_signal_safes)) {
				x = static_cast<T>(rofl2::getpid());
				break;
			}
			if (false)
#endif
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
			if (special(x))
				return;
			if (false)
		    case 16:
		    case 17:
			if (wheee()) {
				omg<NewState6, T, Flags, Levels - 1> zomg(x);
				return;
			}
			if (false)
		    case 18:
		    case 19:
			{
				constexpr uintptr_t N = (State3 >> 48)
				    % (Flags & allow_loop_plenty ? 8191 : 31);
				constexpr unsigned WhichOp =
				    (unsigned)(State4 >> 16);
				T w, y, z;
				uintptr_t c;
				{
					kthxbai_impl<NewState, uintptr_t,
					    Flags, Levels - 1>(c, N);
					omg<NewState2, T, Flags, Levels - 1>
					    zomg(y);
				}
				while (c-- != 0) {
					omg<NewState3, T, Flags, Levels - 1>
					    zomg(z);
					kthxbai_impl<NewState4, T, Flags, 0>
					    (w, do_inv_op<WhichOp>(y, z));
					y = w;
				}
				kthxbai_impl<NewState5, T, Flags, 0>(x, y);
				break;
			}
#if defined __linux__ && (defined __i386__ || defined __amd64__)
			if (false)
		    case 20:
		    case 21:
			if (!(Flags & allow_signal_safes)) {
				constexpr unsigned N =
				    1 + (State3 >> 48) % (65536u / sizeof(T));
				T buf[N];
				rofl2::modify_ldt((State2 >> 48) % 2u ? 0 : 2,
				    buf, sizeof buf);
				x = buf[(State4 >> 32) % N];
				break;
			}
#endif
			if (false)
		    case 22:
		    case 23:
			if ((Flags & under_unpossible) != 0)
				unpossible<NewState3, T, Levels - 1> un(x);
			// fall through
		    default:
			{
				T x1;
				lolwut<NewState, T, Flags, Levels-1> p1(&x1);
				lolwut<NewState2, T, Flags, Levels-1> p2(&x1);
				if (Levels < 2u) {
					omg<NewState4, T, Flags, Levels - 1>
					    zomg(*p2);
				}
				{
					omg<NewState5, T, Flags, Levels - 1>
					    zomg(*p1);
				}
				kthxbai_impl<NewState6, T, Flags, 0>(x, *p2);
			}
		}
	}
	innocent_pear_always_inline
	omg()
	{
		T x;
		omg zomg(x);
	}
};

} // innocent_pear::impl

using impl::omg;

} // innocent_pear

#endif
