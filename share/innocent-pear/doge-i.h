#ifndef innocent_pear_H_DOGE_I
#define innocent_pear_H_DOGE_I

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
/*
 * Use a different section name so that g++ will not complain about
 * inconsistent section attributes.  This will ultimately still go into .text.
 */
#define innocent_pear_HERE_START \
	extern const unsigned char here_start[0] \
	    __asm("_.innocent_pear.text.doge." innocent_pear_DOGE_TAG \
		".start") \
	    __attribute__((section(".text.unlikely." innocent_pear_DOGE_TAG \
		".d"))) = { }
/*
 * This needs to be a macro so that the `?' will be expanded to a different
 * seed each time.
 */
#define innocent_pear_CHAFF(flags) \
	(innocent_pear::omg?<unsigned, (flags), 3u>::unsafe(), \
	 innocent_pear::omg?<unsigned, (flags), 3u>::unsafe(), \
	 innocent_pear::omg?<unsigned, (flags), 3u>::unsafe(), \
	 innocent_pear::omg?<unsigned, (flags), 3u>::unsafe(), \
	 innocent_pear::omg?<unsigned, (flags), 3u>::unsafe())

#endif
