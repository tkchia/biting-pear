#include <cinttypes>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <sys/mman.h>
#include <innocent-pear/dawg.h>
#include <innocent-pear/kthxbai.h>
#include <innocent-pear/orly.h>
#include <innocent-pear/rofl.h>
#ifdef innocent_pear_HAVE_IMPLD_FUNC_PTRACE
#   include <sys/ptrace.h>
#endif
#ifdef innocent_pear_HAVE_CONST_TCOOFF
#   include <sys/termios.h>
#endif
#ifdef innocent_pear_HAVE_FUNC_GETAUXVAL
#   include <sys/auxv.h>
#endif
#ifdef __unix__
#   include <fcntl.h>
#endif
#include "doge-i.h"

innocent_pear_DOGE_HIDDEN extern unsigned char our_rodata_end[]
    __asm("_.innocent_pear.rodata.end");

innocent_pear_NEXT

#ifdef innocent_pear_FIX_ELF_IFUNC
innocent_pear_DOGE_HIDDEN extern const unsigned char our_text_start[0]
    __asm("_.innocent_pear.text.start");
extern "C" void __real___pthread_initialize_minimal();

extern "C"
__attribute__((section(".text.unlikely." innocent_pear_DOGE_TAG ".t"),
    visibility("hidden")))
void __wrap___pthread_initialize_minimal()
{
#   ifdef innocent_pear_DEBUG
	static bool called = false;
	if (!called)
		called = true;
	else {
		std::fprintf(stderr, "%s called more than once; "
		    "indirect functions possibly borked\n", __func__);
		std::abort();
	}
#   endif
	typedef uintptr_t (*Resolver)(unsigned long);
#   ifdef innocent_pear_HAVE_FUNC_GETAUXVAL
	unsigned long hwcap = getauxval(AT_HWCAP);
#   else
	unsigned long hwcap = 0;
#   endif
	using innocent_pear::kthxbai;
	using innocent_pear::ops::allow_minimal;
	kthxbai?<const Elfxx_Rel *, allow_minimal, 0u> p(rel_iplt_start);
	kthxbai?<const Elfxx_Rel *, allow_minimal, 0u> q(rel_iplt_end);
	std::ptrdiff_t n1 = q - p;
	while (n1-- > 0) {
		if (irel_sane(p->r_info) &&
		    (void *)*p->r_offset < our_text_start) {
			*p->r_offset = ((Resolver)*p->r_offset)(hwcap);
			/* Unlikely, but possible... */
			if ((void *)*p->r_offset >= our_text_start)
				std::abort();
		}
		++p;
	}
	kthxbai?<const Elfxx_Rela *, allow_minimal, 0u> r(rela_iplt_start);
	kthxbai?<const Elfxx_Rela *, allow_minimal, 0u> s(rela_iplt_end);
	std::ptrdiff_t n2 = s - r;
	while (n2-- > 0) {
		if (irel_sane(r->r_info) &&
		    (void *)r->r_addend < our_text_start)
			*r->r_offset = r->r_addend(hwcap);
		++r;
	}
	__real___pthread_initialize_minimal();
}
#endif

innocent_pear_DOGE unscramble_01_1()
{
	using innocent_pear::kthxbai;
	constexpr auto flags =
	    ((innocent_pear::ops_flags_t)(innocent_pear_FLAGS &
	      ~innocent_pear::ops::under_ptrace)),
	    flags2 = innocent_pear_FLAGS;
	kthxbai?<unsigned char *> nxs(next_start);
	kthxbai?<unsigned char *> nxe(next_end);
	unsigned char *re = our_rodata_end;
	innocent_pear_CHAFF(innocent_pear::ops::allow_for_startup);
#if defined innocent_pear_HAVE_CONST_TCOOFF
	innocent_pear::rofl?<innocent_pear::ops::allow_for_startup, 2u>::
	    tcflow((int)((0ull + innocent_pear_DOGE_STATE_0 +
				 innocent_pear_DOGE_STATE_1)
		% 100000001ull % 3ull), TCOOFF);
	innocent_pear_CHAFF(flags);
#endif
	uintptr_t pg_sz = (uintptr_t)(innocent_pear::kthxbai?<
	    innocent_pear_decltype(&getpagesize), flags, 1u>(getpagesize))();
	uintptr_t prot_start = (uintptr_t)(unsigned char *)nxs & -pg_sz;
	uintptr_t prot_end = ((uintptr_t)re + pg_sz - 1) & -pg_sz;
	innocent_pear::rofl?<flags, 1u>::mprotect((void *)prot_start,
	    (std::size_t)(prot_end - prot_start),
	    PROT_READ | PROT_WRITE | PROT_EXEC);
	innocent_pear_CHAFF(flags);
#if defined innocent_pear_HAVE_IMPLD_FUNC_PTRACE && \
    defined innocent_pear_HAVE_CONST_PT_TRACE_ME
	nxs -= (0x80 + innocent_pear_DOGE_STATE_0 % 0xff80ull) *
	    innocent_pear::rofl?<flags>::ptrace(PT_TRACE_ME, 0, 0, 0);
	innocent_pear_CHAFF(flags2);
#endif
	innocent_pear::orly<innocent_pear_DOGE_STATE_0, unsigned char, false,
	    true, flags2>().wut(nxs, nxe);
	innocent_pear_CHAFF(flags2);
	innocent_pear::rofl?<flags2>::clear_cache(nxs, nxe);
	innocent_pear_CHAFF(flags2);
}
