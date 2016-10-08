#ifndef innocent_pear_H_DOGE_I
#define innocent_pear_H_DOGE_I

#include <innocent-pear/bbq.h>

#ifdef innocent_pear_HAVE_CTOR_PRIORITY
#   define innocent_pear_CTOR  constructor(101)
#else
#   define innocent_pear_CTOR  constructor
#endif
#define innocent_pear_DOGE \
       __attribute__((innocent_pear_CTOR, \
	    section(".text.unlikely." innocent_pear_DOGE_TAG ".t"))) \
       static void
#define innocent_pear_DOGE_MEMSET \
       __attribute__((innocent_pear_CTOR, \
	    section(".text.unlikely." innocent_pear_DOGE_TAG ".t"), \
           optimize("no-reorder-blocks"))) \
       static void
#ifndef __clang__
/*
 * Use a different section name so that g++ will not complain about
 * inconsistent section attributes.  This will ultimately still go into .text.
 */
#   define innocent_pear_HERE_START \
	extern const unsigned char here_start[0] \
	    __asm("_.innocent_pear.text.doge." innocent_pear_DOGE_TAG \
		".start") \
	    __attribute__((section(".text.unlikely." innocent_pear_DOGE_TAG \
		".d"))) = { };
#else
/*
 * A rather messy hack.  clang++ does not honour `-fno-toplevel-reorder'
 * when deciding how to order top-level variables with respect to top-level
 * functions.  So we put a function here instead.
 *
 * If the `naked' attribute is known to be supported, use it so that the
 * compiler generates no code whatsoever for the "function".  Otherwise, we
 * have no choice but to let the compiler generate _something_.
 */
#   ifdef __arm__
#	define innocent_pear_HERE_START \
	extern void here_start() __asm("_.innocent_pear.text.doge." \
	    innocent_pear_DOGE_TAG ".start"); \
	__attribute__((section(".text.unlikely." innocent_pear_DOGE_TAG \
	    ".d"), naked)) \
	void here_start() { }
#   else
#	define innocent_pear_HERE_START \
	extern void here_start() __asm("_.innocent_pear.text.doge." \
	    innocent_pear_DOGE_TAG ".start"); \
	__attribute__((section(".text.unlikely." innocent_pear_DOGE_TAG \
	    ".d"))) \
	void here_start() { }
#   endif
#endif
#define innocent_pear_NEXT \
	extern unsigned char next_start[] \
	    __asm("_.innocent_pear.text.doge." innocent_pear_DOGE_TAG_NEXT \
		  ".start"); \
	extern unsigned char next_end[] \
	    __asm("_.innocent_pear.text.doge." innocent_pear_DOGE_TAG_2_NEXT \
		  ".start");
/*
 * This needs to be a macro so that the `?' will be expanded to a different
 * seed each time.
 */
#define innocent_pear_CHAFF(flags) \
	(innocent_pear::omg?<unsigned, (flags)>::special(), \
	 innocent_pear::omg?<unsigned, (flags)>::special(), \
	 innocent_pear::omg?<unsigned, (flags)>::special(), \
	 innocent_pear::omg?<unsigned, (flags)>::special(), \
	 innocent_pear::omg?<unsigned, (flags)>::special())

/*
 * This is here just to make sure that the preprocessed C++ output contains
 * all the seeds passed from the front-end, to allow the `?<...>' expansion
 * process (omnomnom) to use them.
 */
__attribute__((unused))
static inline innocent_pear::impl::rand_state_t mixology()
{
	return	innocent_pear_DOGE_STATE_0 ^ innocent_pear_DOGE_STATE_1 ^
		innocent_pear_DOGE_STATE_2 ^ innocent_pear_DOGE_STATE_3 ^
		innocent_pear_DOGE_STATE_4 ^ innocent_pear_DOGE_STATE_5 ^
		innocent_pear_DOGE_STATE_6 ^ innocent_pear_DOGE_STATE_7 ^
		innocent_pear_DOGE_STATE_8 ^ innocent_pear_DOGE_STATE_9 ^
		innocent_pear_DOGE_STATE_10;
}

#endif
