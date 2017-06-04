#ifndef innocent_pear_H_DOGE
#define innocent_pear_H_DOGE

/* There should be a better way... */
#if defined __STDC__ || defined __cplusplus
#   ifndef __ia16__
#	define main(...) \
		__attribute__((section(".text.main"))) main(__VA_ARGS__)
#   else
#	define main(...) \
		__attribute__((section(".text"))) main(__VA_ARGS__)
#   endif
#endif

#endif
