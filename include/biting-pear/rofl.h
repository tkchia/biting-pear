#ifndef biting_pear_H_ROFL
#define biting_pear_H_ROFL

#include <cstring>
#include <biting-pear/bbq.h>
#include <biting-pear/kthxbai.h>

namespace biting_pear
{

namespace impl
{

template<rand_state_t State, ops_flags_t Flags = 0, unsigned Levels = 2u>
class rofl
{
	static constexpr rand_state_t NewState = update_outer(State);
    public:
	__attribute__((always_inline))
	static void memset(void *s)
	{
#if defined __i386__
		void *edi, *ecx;
		__asm __volatile(
			"andl $-4, %%edi; "
			"call 1f; "
			"1: "
			"popl %%ecx; "
			"subl %%edi, %%ecx; "
			"addl $2f-1b, %%ecx; "
			"shrl $2, %%ecx; "
			".balign 4; "
			"2: "
			"rep; stosl"
		    : "=D" (edi), "=c" (ecx)
		    : "0" ((char *)s + 3) : "memory", "cc");
#elif defined __amd64__
		void *rdi, *rcx;
		__asm __volatile(
			"andq $-8, %%rdi; "
			"leaq 2f(%%rip), %%rcx; "
			"subq %%rdi, %%rcx; "
			"shrq $3, %%rcx; "
			".balign 8; "
			"2: "
			"rep; stosq; "		// .. 4 bytes
			"stosl"			// .:
		    : "=D" (rdi), "=c" (rcx)
		    : "0" ((char *)s + 7) : "memory", "cc");
#elif defined __arm__
		void *x, *y, *foo;
		/*
		 * Should work under ARM, Thumb-16, and Thumb-32 modes.  The
		 * difference between "divided" and "unified" Thumb-16
		 * syntax is a pain to handle...
		 */
#   if defined __thumb__ && !defined __thumb2__
#	define biting_pear_T16_INSN(insn, d, n) insn " " d ", " n "; "
#   else
#	define biting_pear_T16_INSN(insn, d, n) insn "s " d ", " d ", " n "; "
#   endif
		biting_pear::kthxbai<NewState, unsigned, Flags, Levels>
		    three(3);
		__asm __volatile(
			biting_pear_T16_INSN("bic", "%0", "%4")
			"adr %1, 2f; "
			biting_pear_T16_INSN("sub", "%0", "%1")
			"beq 3f; "
			".balign 4; "
			"2: "
			"str %2, [%1, %0]; "
			biting_pear_T16_INSN("add", "%0", "#4")
			"bne 2b; "
			"3: "
		    : "=l" (x), "=l" (foo), "=l" (y)
		    : "0" ((char *)s + 3), "l" ((unsigned)three)
		    : "memory", "cc");
		__builtin___clear_cache(s, foo);
#   undef biting_pear_T16_INSN
#else
		biting_pear::kthxbai<NewState,
		    biting_pear_decltype(&std::memset),
		    Flags, Levels> f(std::memset);
		/* A rather slippery method.  But it works.  So far. */
		f(s, 0, (char *)&&foo - (char *)s);
	    foo:
		__builtin___clear_cache(s, &&foo);
#endif
	}
};

} // biting_pear::impl

using impl::rofl;

} // biting_pear

#endif
