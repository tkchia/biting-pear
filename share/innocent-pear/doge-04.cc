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
    section(".text.unlikely"), optimize("no-reorder-blocks")))
static void unscramble_3()
{
	static constexpr innocent_pear::impl::ops_flags_t flags =
	    innocent_pear::ops::allow_all &
	   ~innocent_pear::ops::allow_terminal_unsafes;
#ifdef innocent_pear_HAVE_CONST_TCOON
	innocent_pear::rofl?<flags>::tcflow(0, TCOON);
	innocent_pear::rofl?<flags>::tcflow(1, TCOON);
	innocent_pear::rofl?<flags>::tcflow(2, TCOON);
#endif
	unsigned char *uts = unlikely_text_start;
	innocent_pear::rofl?<flags>::memset(uts);
}
