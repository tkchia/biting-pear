SECTIONS
{
	.data :
	{
		*(.data)
		. = ALIGN(ALIGNOF(.data));
		__doge_start = .;
		*(.innocent_pear.test)
		__doge_end = .;
	}
}
