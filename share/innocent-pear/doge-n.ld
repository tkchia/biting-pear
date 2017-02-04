SECTIONS
{
	.init :
	{
		KEEP(*(SORT_NONE(.init)))
		. = ALIGN(ALIGNOF(.init_array));
		HIDDEN("_.innocent_pear.dogecoin.start" = .);
		KEEP(*(SORT(.innocent_pear.dogecoin.*)))
		HIDDEN("_.innocent_pear.dogecoin.end" = .);
		/*
		 * For our nasty ELF indirect function hack.  These should
		 * have no real effect if the hack is not used.
		 */
		PROVIDE_HIDDEN(__rel_iplt_start = .);
		PROVIDE_HIDDEN(__rel_iplt_end = .);
		PROVIDE_HIDDEN(__rela_iplt_start = .);
		PROVIDE_HIDDEN(__rela_iplt_end = .);
		PROVIDE_HIDDEN(__wrap___rel_iplt_start = __rel_iplt_end);
		PROVIDE_HIDDEN(__wrap___rela_iplt_start = __rela_iplt_end);
	}
}
