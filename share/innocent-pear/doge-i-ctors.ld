SECTIONS
{
	.text.doge :
	{
		KEEP(*(.text.unlikely.??.d .text.unlikely.??.t))
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
	/*
	 * Rather nasty hack to ensure that the `-Xinnocent-pear -doge' does
	 * not scramble the contents of the innocent_pear::teh<...> comdat
	 * sections.  See also include/innocent-pear/teh.h .
	 */
	.rodata.doge :
	{
		KEEP(*(.rodata._ZN13innocent_pear4impl8teh_impl*))
	}
	.data.doge :
	{
		KEEP(*(.data._ZN13innocent_pear4impl8teh_impl*))
	}
}
INSERT AFTER .text;
