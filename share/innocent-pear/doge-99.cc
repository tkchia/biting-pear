unsigned char startup_text_end[0]
    __asm("_.innocent_pear.text.startup.end")
    __attribute__((section(".text.startup.zzzzzzzzzzzzzzzzzzzzzzzz")));
unsigned char hot_text_end[0]
    __asm("_.innocent_pear.text.hot.end")
    __attribute__((section(".text.hot.zzzzzzzzzzzzzzzzzzzzzzzz")));
unsigned char our_text_end[0]
    __asm("_.innocent_pear.text.end")
    __attribute__((section(".gnu.linkonce.t.zzzzzzzzzzzzzzzzzzzzzzzz")));
