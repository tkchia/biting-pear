SECTIONS
{
	.text.doge :
	{
		KEEP(*(.text.unlikely.??.t .text.unlikely.??.d))
	}
	. = ALIGN(2);
	.init_array :
	{
		PROVIDE_HIDDEN(__init_array_start = .);
		KEEP(*(SORT_BY_INIT_PRIORITY(.init_array.*)
		       SORT_BY_INIT_PRIORITY(.ctors.*)))
		KEEP(*(.init_array
		     EXCLUDE_FILE(*/crtbegin.o */crtend.o) .ctors))
		PROVIDE_HIDDEN(__init_array_end = .);
	}
}
INSERT AFTER .text;
