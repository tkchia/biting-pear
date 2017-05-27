SECTIONS
{
	.text :
	{
		. = ALIGN(ALIGNOF(.init_array));
		/*
		 * For our nasty ELF indirect function hack.  These should
		 * have no real effect if the hack is not used.
		 */
		*(.rel.bss)
		*(.rel.iplt)
		PROVIDE_HIDDEN(__rel_iplt_start =
		    DEFINED(__rel_iplt_start) ? __rel_iplt_start : .);
		PROVIDE_HIDDEN(__rel_iplt_end =
		    DEFINED(__rel_iplt_end) ? __rel_iplt_end : .);
		*(.rela.bss)
		*(.rela.iplt)
		PROVIDE_HIDDEN(__rela_iplt_start =
		    DEFINED(__rela_iplt_start) ? __rela_iplt_start : .);
		PROVIDE_HIDDEN(__rela_iplt_end =
		    DEFINED(__rela_iplt_end) ? __rela_iplt_end : .);
		PROVIDE_HIDDEN(__wrap___rel_iplt_start = __rel_iplt_end);
		PROVIDE_HIDDEN(__wrap___rela_iplt_start = __rela_iplt_end);
	}
}
