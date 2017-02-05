#include "doge-i.h"

extern const unsigned char startup_text_end[0]
    __asm("_.innocent_pear.text.startup.end")
    __attribute__((section(".text.startup.zzzzzzzzzzzzzzzzzzzzzzzz"),
	innocent_pear_HIDDEN)) = { };
extern const unsigned char hot_text_end[0]
    __asm("_.innocent_pear.text.hot.end")
    __attribute__((section(".text.hot.zzzzzzzzzzzzzzzzzzzzzzzz"),
	innocent_pear_HIDDEN)) = { };
extern const unsigned char our_text_end[0]
    __asm("_.innocent_pear.text.end")
    __attribute__((section(".gnu.linkonce.t.zzzzzzzzzzzzzzzzzzzzzzzz"),
	innocent_pear_HIDDEN)) = { };
extern const unsigned char our_rodata_end[0]
    __asm("_.innocent_pear.rodata.end")
    __attribute__((section(".rodata.zzzzzzzzzzzzzzzzzzzzzzzz"),
	innocent_pear_HIDDEN)) = { };
extern const unsigned char our_relro_end[0]
    __asm("_.innocent_pear.relro.end")
    __attribute__((section(".gnu.linkonce.d.rel.ro."
			   "zzzzzzzzzzzzzzzzzzzzzzzz"),
	innocent_pear_HIDDEN)) = { };
unsigned char our_data_end[0]
    __asm("_.innocent_pear.data.end")
    __attribute__((section(".data.zzzzzzzzzzzzzzzzzzzzzzzz"),
	innocent_pear_HIDDEN));
#ifdef innocent_pear_FIX_ELF_IFUNC
extern const Elfxx_Rel rel_iplt_start[0]
    __asm("_.innocent_pear.rel.iplt.start")
    __attribute__((section(".rel.plt"))) = { };
extern const Elfxx_Rela rela_iplt_start[0]
    __asm("_.innocent_pear.rela.iplt.start")
    __attribute__((section(".rela.plt"))) = { };
#endif
