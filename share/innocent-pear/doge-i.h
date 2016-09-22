#ifndef innocent_pear_H_DOGE
#define innocent_pear_H_DOGE

#ifdef innocent_pear_HAVE_CTOR_PRIORITY
#   define innocent_pear_CTOR  constructor(101)
#else
#   define innocent_pear_CTOR  constructor
#endif
#define innocent_pear_DOGE(tag) \
       __attribute__((innocent_pear_CTOR, \
	    section(".text.unlikely." tag ".t"))) \
       static void
#define innocent_pear_DOGE_MEMSET(tag) \
       __attribute__((innocent_pear_CTOR, \
	    section(".text.unlikely." tag ".t"), \
           optimize("no-reorder-blocks"))) \
       static void

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
