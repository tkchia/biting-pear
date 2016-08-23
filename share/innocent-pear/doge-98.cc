#include <cinttypes>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <sys/mman.h>
#include <innocent-pear/kthxbai.h>
#include <innocent-pear/rofl.h>

extern unsigned char unlikely_text_start[]
    __asm("_.innocent_pear.text.unlikely.start");
extern unsigned char startup_text_start[]
    __asm("_.innocent_pear.text.startup.start");
extern unsigned char our_text_end[] __asm("_.innocent_pear.text.end");
extern unsigned char our_rodata_start[] __asm("_.innocent_pear.rodata.start");
extern unsigned char our_relro_end[] __asm("_.innocent_pear.relro.end");

#ifdef innocent_pear_HAVE_CTOR_PRIORITY
#   define innocent_pear_CTOR_L	constructor(65535)
#else
#   define innocent_pear_CTOR_L	constructor
#endif
#define innocent_pear_DOGE_L \
	__attribute__((innocent_pear_CTOR_L, \
	    section(".text.startup.zzzzzzzzzzzzzzzzzzzzzzzz"))) \
	static void
#define innocent_pear_DOGE_MEMSET_L \
	__attribute__((innocent_pear_CTOR_L, \
	    section(".text.startup.zzzzzzzzzzzzzzzzzzzzzzzz"), \
	    optimize("no-reorder-blocks"))) \
	static void

innocent_pear_DOGE_MEMSET_L scramble_98_1()
{
	using innocent_pear::ops::allow_debugger_unsafes;
	innocent_pear::rofl?<allow_debugger_unsafes>::memset
	    (startup_text_start);
}

innocent_pear_DOGE_L scramble_98_2()
{
	using innocent_pear::ops::allow_debugger_unsafes;
	uintptr_t pg_sz = (uintptr_t)getpagesize();
	unsigned char *prot_start =
	    (unsigned char *)((uintptr_t)unlikely_text_start & -pg_sz);
	unsigned char *prot_end =
	    (unsigned char *)(((uintptr_t)our_text_end + pg_sz - 1) & -pg_sz);
	innocent_pear::kthxbai?<unsigned, allow_debugger_unsafes>
	    prot1(PROT_READ | PROT_EXEC);
	innocent_pear::rofl?<allow_debugger_unsafes>::mprotect
	    (prot_start, (std::size_t)(prot_end - prot_start),
	    (int)(unsigned)prot1);
	prot_start =
	    (unsigned char *)(((uintptr_t)our_rodata_start+pg_sz-1) & -pg_sz);
	if (prot_start < prot_end)
		prot_start = prot_end;
	innocent_pear::kthxbai?<unsigned, allow_debugger_unsafes>
	    prot2(PROT_READ);
	/*
	 * Apply mprotect(...) to one page at a time, since there may be
	 * gaps in the virtual memory mapping between the end of .rodata and
	 * the end of .data.rel.ro .
	 */
	while (prot_start < our_relro_end) {
		innocent_pear::rofl?<allow_debugger_unsafes>::mprotect
		    (prot_start, pg_sz, (int)(unsigned)prot2);
		prot_start += pg_sz;
	}
}
