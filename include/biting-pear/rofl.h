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
			"addl $3, %%edi; "
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
		    : "=D" (edi), "=c" (ecx) : "0" (s) : "memory", "cc");
#elif defined __amd64__
		void *rdi, *rcx;
		__asm __volatile(
			"addq $7, %%rdi; "
			"andq $-8, %%rdi; "
			"leaq 2f(%%rip), %%rcx; "
			"subq %%rdi, %%rcx; "
			"shrq $3, %%rcx; "
			".balign 8; "
			"2: "
			"rep; stosq; "		// .. 4 bytes
			"stosl"			// .:
		    : "=D" (rdi), "=c" (rcx) : "0" (s) : "memory", "cc");
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
