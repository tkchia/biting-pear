#ifndef innocent_pear_H_DOGE_I
#define innocent_pear_H_DOGE_I

#include <innocent-pear/bbq.h>

#ifdef innocent_pear_HAVE_CTOR_PRIORITY
#   define innocent_pear_CTOR	constructor(101)
#else
#   define innocent_pear_CTOR	constructor
#endif
#ifdef __ELF__
#   define innocent_pear_HIDDEN	visibility("hidden")
#else
#   define innocent_pear_HIDDEN	visibility("default")
#endif
#define innocent_pear_DOGE_HIDDEN __attribute__((innocent_pear_HIDDEN))
#define innocent_pear_DOGE \
	__attribute__((innocent_pear_CTOR, \
	    section(".text.unlikely." innocent_pear_DOGE_TAG ".t"))) \
	static void
#ifndef __clang__
#   define innocent_pear_DOGE_MEMSET \
	__attribute__((innocent_pear_CTOR, \
	    section(".text.unlikely." innocent_pear_DOGE_TAG ".t"), \
	    optimize("no-reorder-blocks"))) \
	static void
/*
 * Use a different section name so that g++ will not complain about
 * inconsistent section attributes.  This will ultimately still go into .text.
 */
#   define innocent_pear_HERE_START \
	extern const unsigned char here_start[0] \
	    __asm("_.innocent_pear.text.doge." innocent_pear_DOGE_TAG \
		".start") \
	    __attribute__((section(".text.unlikely." innocent_pear_DOGE_TAG \
		".d"), innocent_pear_HIDDEN)) = { };
#else
/* clang++ does not understand __attribute__((optimize(.)))... */
#   define innocent_pear_DOGE_MEMSET innocent_pear_DOGE
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
	    ".d"), innocent_pear_HIDDEN, naked)) \
	void here_start() { }
#   else
#	define innocent_pear_HERE_START \
	extern void here_start() __asm("_.innocent_pear.text.doge." \
	    innocent_pear_DOGE_TAG ".start"); \
	__attribute__((section(".text.unlikely." innocent_pear_DOGE_TAG \
	    ".d"), innocent_pear_HIDDEN)) \
	void here_start() { }
#   endif
#endif
#define innocent_pear_NEXT \
	innocent_pear_DOGE_HIDDEN \
	extern unsigned char next_start[] \
	    __asm("_.innocent_pear.text.doge." innocent_pear_DOGE_TAG_NEXT \
		  ".start"); \
	__attribute__((innocent_pear_HIDDEN)) \
	extern unsigned char next_end[] \
	    __asm("_.innocent_pear.text.doge." innocent_pear_DOGE_TAG_2_NEXT \
		  ".start");
#define innocent_pear_FLAGS \
	((innocent_pear::ops_flags_t) \
	    (innocent_pear::ops::allow_for_startup | \
	     innocent_pear::ops::under_munged_terminal | \
	     innocent_pear::ops::under_ptrace))
/*
 * This needs to be a macro so that the `?' will be expanded to a different
 * seed each time.
 */
#define innocent_pear_CHAFF(flags) \
	(innocent_pear::omg?<unsigned, (flags)>::special())

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

#ifdef innocent_pear_FIX_ELF_IFUNC
typedef struct {
	innocent_pear::impl::uintptr_t *r_offset, r_info;
} Elfxx_Rel;

typedef struct {
	innocent_pear::impl::uintptr_t *r_offset, r_info,
	    (*r_addend)(unsigned long);
} Elfxx_Rela;

/*
 * Using __real___rel{, a}_iplt_start for rel{, a}_iplt_start is unreliable
 * -- apparently some slightly older versions of GNU binutils (e.g. 2.24)
 * get confused and give __real___rel{, a}_iplt_start == __wrap___rel{, a}_
 * iplt_start.
 *
 * Instead, use the symbols defined in doge-99.cc, which should fall
 * somewhere inside .rel{, a}.bss and before .rel{, a}.iplt .
 */
innocent_pear_DOGE_HIDDEN extern const Elfxx_Rel
    rel_iplt_start[] __asm("_.innocent_pear.rel.iplt.start"),
    rel_iplt_end[] __asm("__wrap___rel_iplt_start");
innocent_pear_DOGE_HIDDEN extern const Elfxx_Rela
    rela_iplt_start[] __asm("_.innocent_pear.rela.iplt.start"),
    rela_iplt_end[] __asm("__wrap___rela_iplt_start");

/*
 * Function to check the relocation type in an Elfxx_Rel{,a} for sanity.  If
 * we know the correct relocation type for indirect functions, compare against
 * that, otherwise do nothing and assume the best.
 */
static inline bool irel_sane(innocent_pear::impl::uintptr_t info)
{
	innocent_pear::impl::uint_least32_t type __attribute__((unused));
	if (sizeof(info) > sizeof(type))
		type = info & 0xfffffffful;
	else
		type = info & 0xfful;
#   if defined __i386__
	return type == 42;		/* R_386_IRELATIVE */
#   elif defined __amd64__
	return type == 37;		/* R_X86_64_IRELATIVE */
#   elif defined __arm__
	return type == 160;		/* R_ARM_IRELATIVE */
#   else
	return true;
#   endif
}
#endif

#endif
