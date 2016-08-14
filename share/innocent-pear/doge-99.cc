unsigned char startup_text_end[0]
    __asm("_.innocent_pear.text.startup.end")
    __attribute__((section(".text.startup.zzzzzzzzzzzzzzzzzzzzzzzz")));
unsigned char hot_text_end[0]
    __asm("_.innocent_pear.text.hot.end")
    __attribute__((section(".text.hot.zzzzzzzzzzzzzzzzzzzzzzzz")));
unsigned char our_text_end[0]
    __asm("_.innocent_pear.text.end")
    __attribute__((section(".gnu.linkonce.t.zzzzzzzzzzzzzzzzzzzzzzzz")));
unsigned char our_rodata_end[0]
    __asm("_.innocent_pear.rodata.end")
    __attribute__((section(".rodata.zzzzzzzzzzzzzzzzzzzzzzzz")));
unsigned char our_data_end[0]
    __asm("_.innocent_pear.data.end")
    __attribute__((section(".data.zzzzzzzzzzzzzzzzzzzzzzzz")));
