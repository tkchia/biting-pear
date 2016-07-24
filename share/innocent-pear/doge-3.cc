#include <cinttypes>
#include <cstdlib>
#include <unistd.h>
#include <sys/mman.h>
#include <innocent-pear/orly.h>
#include <innocent-pear/rofl.h>
#ifdef innocent_pear_HAVE_CONST_TCOON
#   include <sys/termios.h>
#endif

extern unsigned char unlikely_text_start[]
    __asm("_.innocent_pear.text.unlikely.start");
extern unsigned char our_text_start[]
    __asm("_.innocent_pear.text.start");
extern unsigned char our_text_end[] __asm("_.innocent_pear.text.end");

__attribute__((
#ifdef innocent_pear_HAVE_CTOR_PRIORITY
    constructor(101),
#else
    constructor,
#endif
    section(".text.unlikely")))
static void unscramble_2()
{
	static constexpr innocent_pear::impl::ops_flags_t flags =
	    innocent_pear::ops::allow_all |
	    innocent_pear::ops::under_munged_terminal;
	using innocent_pear::impl::update_outer;
	using innocent_pear::impl::update_inner;
	unsigned char *uts = unlikely_text_start, *ts = our_text_start,
	    *te = our_text_end;
	innocent_pear::orly<innocent_pear_DOGE_STATE_2,
	    unsigned char, false, false, flags>().wut(ts, te);
	innocent_pear::rofl?<flags>::clear_cache(ts, te);
	innocent_pear::rofl?<flags>::memset(uts);
#ifdef innocent_pear_HAVE_CONST_TCOON
	innocent_pear::rofl?<innocent_pear::ops::allow_all &
			    ~innocent_pear::ops::allow_terminal_unsafes>::
	    tcflow(0, TCOON);
	innocent_pear::rofl?<innocent_pear::ops::allow_all &
			    ~innocent_pear::ops::allow_terminal_unsafes>::
	    tcflow(1, TCOON);
	innocent_pear::rofl?<innocent_pear::ops::allow_all &
			    ~innocent_pear::ops::allow_terminal_unsafes>::
	    tcflow(2, TCOON);
#endif
}
