SECTIONS
{
	.init :
	{
		KEEP(*(SORT_NONE(.init)))
		. = ALIGN(ALIGNOF(.init_array));
		"_.innocent_pear.dogecoin.start" = .;
		KEEP(*(SORT(.innocent_pear.dogecoin.*)))
		"_.innocent_pear.dogecoin.end" = .;
	}
}
