#ifndef innocent_pear_H_DOGE
#define innocent_pear_H_DOGE

/* There should be a better way... */
#if defined __STDC__ || defined __cplusplus
#   define main(...)	__attribute__((section(".text.main"))) \
			main(__VA_ARGS__)
#endif

#endif
