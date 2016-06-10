unsigned char unlikely_text_start[0]
    __asm("_.innocent_pear.text.unlikely.start")
    __attribute__((section(".text.unlikely")));
unsigned char startup_text_start[0]
    __asm("_.innocent_pear.text.startup.start")
    __attribute__((section(".text.startup")));
