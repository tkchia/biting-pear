#include "doge-i.h"

innocent_pear_HERE_START
extern const unsigned char our_text_start[0]
    __asm("_.innocent_pear.text.start")
    __attribute__((section(".text"))) = { };
extern const unsigned char our_rodata_start[0]
    __asm("_.innocent_pear.rodata.start")
    __attribute__((section(".rodata"))) = { };
extern const unsigned char our_relro_start[0]
    __asm("_.innocent_pear.relro.start")
    __attribute__((section(".data.rel.ro"))) = { };
unsigned char our_data_start[0] __asm("_.innocent_pear.data.start")
    __attribute__((section(".data")));
