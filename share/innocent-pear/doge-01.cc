#include <cinttypes>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <innocent-pear/dawg.h>
#include <innocent-pear/kthxbai.h>
#include <innocent-pear/orly.h>
#include <innocent-pear/rofl.h>
#ifdef innocent_pear_HAVE_FUNC_MPROTECT
#   include <sys/mman.h>
#endif
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

typedef innocent_pear::kthxbai<innocent_pear_DOGE_STATE_11,
    const unsigned char *, innocent_pear::ops::allow_minimal, 0u> foo_t;

#ifdef innocent_pear_FIX_ELF_IFUNC
innocent_pear_DOGE_HIDDEN extern const unsigned char our_text_start[0]
    __asm("_.innocent_pear.text.start");
extern "C" void __real___pthread_initialize_minimal();
extern void unscramble_00_1(foo_t) __asm("_.innocent_pear.unscramble_00_1");
#endif

innocent_pear_DOGE unscramble_01_1()
{
	using innocent_pear::kthxbai;
	using innocent_pear::ops::allow_for_startup;
	constexpr auto flags =
	    ((innocent_pear::ops_flags_t)(innocent_pear_FLAGS &
	      ~innocent_pear::ops::under_ptrace)),
	    flags2 = innocent_pear_FLAGS;
	kthxbai?<unsigned char *, allow_for_startup> nxs(next_start);
	kthxbai?<unsigned char *, allow_for_startup> nxe(next_end);
#ifdef innocent_pear_HAVE_FUNC_MPROTECT
	unsigned char *re = our_rodata_end;
#endif
	innocent_pear_CHAFF(allow_for_startup);
#if defined innocent_pear_HAVE_CONST_TCOOFF
	innocent_pear::rofl?<allow_for_startup, 1u>::
	    tcflow((int)((0ull + innocent_pear_DOGE_STATE_0 +
				 innocent_pear_DOGE_STATE_1)
		% 100000001ull % 3ull), TCOOFF);
	innocent_pear_CHAFF(flags);
#endif
#ifdef innocent_pear_HAVE_FUNC_MPROTECT
	uintptr_t pg_sz = innocent_pear::rofl?<flags, 1u>::getpagesize();
	uintptr_t prot_start = (uintptr_t)(unsigned char *)nxs & -pg_sz;
	uintptr_t prot_end = ((uintptr_t)re + pg_sz - 1) & -pg_sz;
	innocent_pear::rofl?<flags, 1u>::mprotect((void *)prot_start,
	    (std::size_t)(prot_end - prot_start),
	    PROT_READ | PROT_WRITE | PROT_EXEC);
	innocent_pear_CHAFF(flags);
#endif
#if defined innocent_pear_HAVE_IMPLD_FUNC_PTRACE && \
    defined innocent_pear_HAVE_CONST_PT_TRACE_ME
	nxs -= (0x80 + innocent_pear_DOGE_STATE_0 % 0xff80ull) *
	    innocent_pear::rofl?<flags>::ptrace(PT_TRACE_ME, 0, 0, 0);
	innocent_pear_CHAFF(flags2);
#endif
	innocent_pear::orly<innocent_pear_DOGE_STATE_0, unsigned char, false,
	    innocent_pear_BIG_BAD, flags2>().wut(nxs, nxe);
	innocent_pear_CHAFF(flags2);
	innocent_pear::rofl?<flags2>::clear_cache(nxs, nxe);
	innocent_pear_CHAFF(flags2);
}

#ifdef innocent_pear_FIX_ELF_IFUNC
extern "C"
__attribute__((section(".text.unlikely." innocent_pear_DOGE_TAG ".t"),
    visibility("hidden"), noinline))
void __wrap___pthread_initialize_minimal()
{
	using innocent_pear::kthxbai;
	using innocent_pear::ops::allow_minimal;
	(kthxbai?<void (*)(foo_t), allow_minimal, 0u>(unscramble_00_1))
	    (foo_t(our_text_start));
	(kthxbai?<void (*)(), allow_minimal, 0u>
	    (__real___pthread_initialize_minimal))();
}
#endif
