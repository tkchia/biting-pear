#include <cinttypes>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <innocent-pear/dawg.h>
#include <innocent-pear/kthxbai.h>
#include <innocent-pear/orly.h>
#include <innocent-pear/rofl.h>
#ifdef innocent_pear_HAVE_FUNC_GETAUXVAL
#   include <sys/auxv.h>
#endif
#include "doge-i.h"

#ifdef innocent_pear_FIX_ELF_IFUNC
typedef innocent_pear::kthxbai<innocent_pear_DOGE_STATE_11,
    const unsigned char *, innocent_pear::ops::allow_minimal, 0u> foo_t;

__attribute__((section(".text.startup"), noinline))
void unscramble_00_1(foo_t) __asm("_.innocent_pear.unscramble_00_1");

__attribute__((section(".text.startup"), noinline))
void unscramble_00_1(foo_t foo)
{
#   ifdef innocent_pear_DEBUG
	static bool called = false;
	if (!called)
		called = true;
	else {
		std::fprintf(stderr, "%s called more than once; "
		    "indirect functions possibly borked\n", __func__);
		std::abort();
	}
#   endif
	typedef uintptr_t (*Resolver)(unsigned long);
#   ifdef innocent_pear_HAVE_FUNC_GETAUXVAL
	unsigned long hwcap = getauxval(AT_HWCAP);
#   else
	unsigned long hwcap = 0;
#   endif
	using innocent_pear::kthxbai;
	using innocent_pear::ops::allow_minimal;
	using innocent_pear::impl::intptr_t;
	kthxbai?<const Elfxx_Rel *, allow_minimal, 0u> p(rel_iplt_start);
	kthxbai?<const Elfxx_Rel *, allow_minimal, 0u> q(rel_iplt_end);
	intptr_t n1 = q - p;
	while (n1-- > 0) {
		if (irel_sane(p->r_info) &&
		    (void *)*p->r_offset < foo) {
			uintptr_t resolved = ((Resolver)*p->r_offset)(hwcap);
			/* Unlikely, but possible... */
			if ((void *)resolved >= foo)
				std::abort();
			*p->r_offset = resolved;
		}
		++p;
	}
	kthxbai?<const Elfxx_Rela *, allow_minimal, 0u> r(rela_iplt_start);
	kthxbai?<const Elfxx_Rela *, allow_minimal, 0u> s(rela_iplt_end);
	intptr_t n2 = s - r;
	while (n2-- > 0) {
		if (irel_sane(r->r_info) &&
		    (void *)r->r_addend < foo)
			*r->r_offset = r->r_addend(hwcap);
		++r;
	}
}
#endif
