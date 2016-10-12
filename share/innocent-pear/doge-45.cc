#include "doge-i.h"

innocent_pear_HERE_START

extern const unsigned char our_text_start[0]
    __asm("_.innocent_pear.text.start")
    __attribute__((section(".text"), innocent_pear_HIDDEN)) = { };
extern const unsigned char our_rodata_start[0]
    __asm("_.innocent_pear.rodata.start")
    __attribute__((section(".rodata"), innocent_pear_HIDDEN)) = { };
extern const unsigned char our_relro_start[0]
    __asm("_.innocent_pear.relro.start")
    __attribute__((section(".data.rel.ro"), innocent_pear_HIDDEN)) = { };
unsigned char our_data_start[0] __asm("_.innocent_pear.data.start")
    __attribute__((section(".data"), innocent_pear_HIDDEN));
