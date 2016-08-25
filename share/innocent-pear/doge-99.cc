extern const unsigned char startup_text_end[0]
    __asm("_.innocent_pear.text.startup.end")
    __attribute__((section(".text.startup.zzzzzzzzzzzzzzzzzzzzzzzz"))) = { };
extern const unsigned char hot_text_end[0]
    __asm("_.innocent_pear.text.hot.end")
    __attribute__((section(".text.hot.zzzzzzzzzzzzzzzzzzzzzzzz"))) = { };
extern const unsigned char our_text_end[0]
    __asm("_.innocent_pear.text.end")
    __attribute__((section(".gnu.linkonce.t.zzzzzzzzzzzzzzzzzzzzzzzz"))) = { };
extern const unsigned char our_rodata_end[0]
    __asm("_.innocent_pear.rodata.end")
    __attribute__((section(".rodata.zzzzzzzzzzzzzzzzzzzzzzzz"))) = { };
extern const unsigned char our_relro_end[0]
    __asm("_.innocent_pear.relro.end")
    __attribute__((section(".gnu.linkonce.d.rel.ro."
			   "zzzzzzzzzzzzzzzzzzzzzzzz"))) = { };
unsigned char our_data_end[0]
    __asm("_.innocent_pear.data.end")
    __attribute__((section(".data.zzzzzzzzzzzzzzzzzzzzzzzz")));
