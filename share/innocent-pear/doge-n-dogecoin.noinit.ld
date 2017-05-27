SECTIONS
{
	.text :
	{
		. = ALIGN(ALIGNOF(.data));
		HIDDEN("_.innocent_pear.dogecoin.start" = .);
		KEEP(*(SORT(.innocent_pear.dogecoin.*)))
		HIDDEN("_.innocent_pear.dogecoin.end" = .);
	}
}
