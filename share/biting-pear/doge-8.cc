#include <cinttypes>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <sys/mman.h>

extern unsigned char startup_text_start[]
    __asm("_.biting_pear.text.startup.start")
    __attribute__((section(".text.startup")));
extern unsigned char startup_text_end[]
    __asm("_.biting_pear.text.startup.end")
    __attribute__((section(".text.startup.zzzzzzzzzzzzzzzzzzzzzzzz")));

__attribute__((
#ifdef biting_pear_HAVE_CTOR_PRIORITY
    constructor(65535),
#else
    constructor,
#endif
    section(".text.startup.zzzzzzzzzzzzzzzzzzzzzzzz")))
static void scramble()
{
	uintptr_t pg_sz = (uintptr_t)getpagesize();
	uintptr_t prot_start = (uintptr_t)startup_text_start & -pg_sz;
	uintptr_t prot_end = ((uintptr_t)startup_text_end + pg_sz - 1)
	    & -pg_sz;
	/* A rather slippery method.  But it works.  So far. */
	std::memset(startup_text_start, 0,
	    (unsigned char *)&&foo - startup_text_start);
foo:
	__builtin___clear_cache(startup_text_start, startup_text_end);
	mprotect((void *)prot_start, (std::size_t)(prot_end - prot_start),
	    PROT_READ | PROT_EXEC);
}
