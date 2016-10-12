SECTIONS
{
	.init :
	{
		KEEP(*(SORT_NONE(.init)))
		. = ALIGN(ALIGNOF(.init_array));
		HIDDEN("_.innocent_pear.dogecoin.start" = .);
		KEEP(*(SORT(.innocent_pear.dogecoin.*)))
		HIDDEN("_.innocent_pear.dogecoin.end" = .);
	}
}
