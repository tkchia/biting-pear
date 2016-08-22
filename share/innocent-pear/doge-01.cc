#include <cinttypes>
#include <cstdlib>
#include <unistd.h>
#include <sys/mman.h>
#include <innocent-pear/orly.h>
#include <innocent-pear/rofl.h>
#ifdef innocent_pear_HAVE_IMPLD_FUNC_PTRACE
#   include <sys/ptrace.h>
#endif
#if defined innocent_pear_HAVE_CONST_TCOOFF
#   include <sys/termios.h>
#endif

extern unsigned char unlikely_text_start[]
    __asm("_.innocent_pear.text.unlikely.start");
extern unsigned char hot_text_end[]
    __asm("_.innocent_pear.text.hot.end");
extern unsigned char our_text_end[] __asm("_.innocent_pear.text.end");
extern unsigned char our_rodata_start[] __asm("_.innocent_pear.rodata.start");
extern unsigned char our_rodata_end[] __asm("_.innocent_pear.rodata.end");

__attribute__((
#ifdef innocent_pear_HAVE_CTOR_PRIORITY
    constructor(101),
#else
    constructor,
#endif
    section(".text.unlikely")))
static void unscramble_01_1()
{
	static constexpr innocent_pear::impl::ops_flags_t flags =
	    innocent_pear::ops::allow_all |
	    innocent_pear::ops::under_munged_terminal;
	unsigned char *uts = unlikely_text_start, *hte = hot_text_end,
	    *te = our_text_end, *rs = our_rodata_start, *re = our_rodata_end;
#if defined innocent_pear_HAVE_CONST_TCOOFF
	innocent_pear::rofl?<innocent_pear::ops::allow_all &
			    ~innocent_pear::ops::allow_terminal_unsafes, 1u>::
	    tcflow((int)((0ull + innocent_pear_DOGE_STATE +
				 innocent_pear_DOGE_STATE_2)
		% 100000001ull % 3ull), TCOOFF);
#endif
#if defined innocent_pear_HAVE_IMPLD_FUNC_PTRACE && \
    defined innocent_pear_HAVE_CONST_PT_TRACE_ME
	uts -= 0x80 * 
	    innocent_pear::rofl?<flags, 4u>::ptrace(PT_TRACE_ME, 0, 0, 0);
#endif
	uintptr_t pg_sz = (uintptr_t)(innocent_pear::kthxbai?<
	    innocent_pear_decltype(&getpagesize), flags, 3u>(getpagesize))();
	uintptr_t prot_start = (uintptr_t)uts & -pg_sz;
	uintptr_t prot_end = ((uintptr_t)te + pg_sz - 1) & -pg_sz;
	innocent_pear::kthxbai?<unsigned, flags, 4u> prot(PROT_READ |
	    PROT_WRITE | PROT_EXEC);
	innocent_pear::rofl?<flags, 3u>::mprotect((void *)prot_start,
	    (std::size_t)(prot_end - prot_start), prot);
	prot_start = (uintptr_t)rs & -pg_sz;
	if (prot_start < prot_end)
		prot_start = prot_end;
	prot_end = ((uintptr_t)re + pg_sz - 1) & -pg_sz;
	innocent_pear::rofl?<flags, 3u>::mprotect((void *)prot_start,
	    (std::size_t)(prot_end - prot_start), prot);
	innocent_pear::orly<innocent_pear_DOGE_STATE, unsigned char, false,
	    true, flags>().wut(uts, hte);
	innocent_pear::rofl?<flags, 4u>::clear_cache(uts, hte);
}
