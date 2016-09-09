#include <cinttypes>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <sys/mman.h>
#include <innocent-pear/dawg.h>
#include <innocent-pear/orly.h>
#include <innocent-pear/rofl.h>
#ifdef innocent_pear_HAVE_IMPLD_FUNC_PTRACE
#   include <sys/ptrace.h>
#endif
#if defined innocent_pear_HAVE_CONST_TCOOFF
#   include <sys/termios.h>
#endif
#ifdef __unix__
#   include <fcntl.h>
#endif

extern unsigned char unlikely_text_start[]
    __asm("_.innocent_pear.text.unlikely.start");
extern unsigned char hot_text_end[]
    __asm("_.innocent_pear.text.hot.end");
extern unsigned char our_rodata_end[]
    __asm("_.innocent_pear.rodata.end");

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
	    *re = our_rodata_end;
#if defined innocent_pear_HAVE_CONST_TCOOFF
	innocent_pear::rofl?<innocent_pear::ops::allow_all &
			    ~innocent_pear::ops::allow_terminal_unsafes, 3u>::
	    tcflow((int)((0ull + innocent_pear_DOGE_STATE +
				 innocent_pear_DOGE_STATE_2)
		% 100000001ull % 3ull), TCOOFF);
#endif
#if defined innocent_pear_HAVE_IMPLD_FUNC_PTRACE && \
    defined innocent_pear_HAVE_CONST_PT_TRACE_ME
	uts -= (0x80 + innocent_pear_DOGE_STATE % 0xff80ull) *
	    innocent_pear::rofl?<flags, 3u>::ptrace(PT_TRACE_ME, 0, 0, 0);
#endif
#ifdef __unix__
	char fn[9];
	$"/dev/tty" >> fn;
	int fd = innocent_pear::rofl?<flags, 3u>::open(fn, O_RDONLY);
	std::memset(fn, 0, 9);
	innocent_pear::rofl?<flags, 3u>::tcflow(fd, TCOOFF);
	innocent_pear::rofl?<flags, 3u>::close(fd);
#endif
	uintptr_t pg_sz = (uintptr_t)(innocent_pear::kthxbai?<
	    innocent_pear_decltype(&getpagesize), flags, 3u>(getpagesize))();
	uintptr_t prot_start = (uintptr_t)uts & -pg_sz;
	uintptr_t prot_end = ((uintptr_t)re + pg_sz - 1) & -pg_sz;
	innocent_pear::rofl?<flags, 3u>::mprotect((void *)prot_start,
	    (std::size_t)(prot_end - prot_start),
	    PROT_READ | PROT_WRITE | PROT_EXEC);
	innocent_pear::orly<innocent_pear_DOGE_STATE, unsigned char, false,
	    true, flags>().wut(uts, hte);
	innocent_pear::rofl?<flags, 3u>::clear_cache(uts, hte);
}
