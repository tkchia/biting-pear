#include <cinttypes>
#include <climits>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <sys/mman.h>
#include <innocent-pear/dawg.h>
#include <innocent-pear/orly.h>
#include <innocent-pear/rofl.h>
#ifdef innocent_pear_HAVE_CONST_TCOON
#   include <sys/termios.h>
#endif
#ifdef innocent_pear_HAVE_FUNC_GETAUXVAL
#   include <sys/auxv.h>
#endif
#include "doge-i.h"

using innocent_pear::impl::uintptr_t;

extern unsigned char our_rodata_start[] __asm("_.innocent_pear.rodata.start");
extern unsigned char our_relro_end[] __asm("_.innocent_pear.relro.end");
extern unsigned char our_bss_end[] __asm("_end");

innocent_pear_HERE_START

#ifdef innocent_pear_FIX_ELF_IFUNC
innocent_pear_DOGE_HIDDEN extern unsigned char our_text_start[]
    __asm("_.innocent_pear.text.start");

innocent_pear_DOGE unscramble_07_1()
{
	typedef uintptr_t (*Resolver)(unsigned long);
#   ifdef innocent_pear_HAVE_FUNC_GETAUXVAL
	unsigned long hwcap = getauxval(AT_HWCAP);
#   else
	unsigned long hwcap = 0;
#   endif
	const Elfxx_Rel *p, *q;
	__asm __volatile("" : "=g" (p) : "0" (rel_iplt_start));
	__asm __volatile("" : "=g" (q) : "0" (rel_iplt_end));
	while (p < q) {
		if (irel_sane(p->r_info) &&
		    (void *)*p->r_offset >= our_text_start)
			*p->r_offset = ((Resolver)*p->r_offset)(hwcap);
		++p;
	}
	const Elfxx_Rela *r, *s;
	__asm __volatile("" : "=g" (r) : "0" (rela_iplt_start));
	__asm __volatile("" : "=g" (s) : "0" (rela_iplt_end));
	while (r < s) {
		if (irel_sane(r->r_info) &&
		    (void *)r->r_addend >= our_text_start)
			*r->r_offset = r->r_addend(hwcap);
		++r;
	}
}
#endif

innocent_pear_DOGE unscramble_07_2()
{
	constexpr auto flags = innocent_pear_FLAGS,
	    flags2 = ((innocent_pear::ops_flags_t)(innocent_pear_FLAGS
		& ~innocent_pear::ops::under_munged_terminal));
	uintptr_t pg_sz = (uintptr_t)getpagesize();
	unsigned char *prot_start =
	    (unsigned char *)(((uintptr_t)our_rodata_start+pg_sz-1) & -pg_sz);
	/*
	 * Apply mprotect(...) to one page at a time, since there may be
	 * gaps in the virtual memory mapping between the end of .rodata and
	 * the end of .data.rel.ro .
	 */
	while (prot_start + pg_sz <= our_relro_end) {
		innocent_pear::rofl?<flags, 2u>::mprotect(prot_start, pg_sz,
		    PROT_READ);
		prot_start += pg_sz;
	}
#if 0
	/*
	 * This is only needed if the linker is lumping the .data section
	 * (and friends) along with the .text section into a single rwx
	 * segment.
	 */
	unsigned char *prot_end =
	    (unsigned char *)(((uintptr_t)our_bss_end + pg_sz - 1) & -pg_sz);
	innocent_pear::rofl?<flags, 2u>::mprotect(prot_start,
	    prot_end - prot_start, PROT_READ | PROT_WRITE);
#endif
#ifdef innocent_pear_HAVE_CONST_TCOON
	innocent_pear::rofl?<flags2, 2u>::tcflow(0, TCOON);
	innocent_pear::rofl?<flags2, 2u>::tcflow(1, TCOON);
	innocent_pear::rofl?<flags2, 2u>::tcflow(2, TCOON);
#   ifdef __unix__
	char fn[9];
	$"/dev/tty" >> fn;
	int fd = innocent_pear::rofl?<flags2, 2u>::open(fn, O_RDONLY);
	std::memset(fn, 0, 9);
	innocent_pear::rofl?<flags2, 2u>::tcflow(fd, TCOON);
	innocent_pear::rofl?<flags2, 2u>::close(fd);
#   endif
#endif
}

#if 0
innocent_pear_DOGE_MEMSET unscramble_07_3()
{
	constexpr auto flags2 =
	    ((innocent_pear::ops_flags_t)(innocent_pear_FLAGS
		& ~innocent_pear::ops::under_munged_terminal));
	innocent_pear::rofl?<flags2, 2u>::memset((void *)here_start);
}
#endif
