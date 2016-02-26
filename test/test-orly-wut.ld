SECTIONS
{
	.data :
	{
		*(.data)
		. = ALIGN(ALIGNOF(.data));
		__doge_start = .;
		*(.biting_pear.test)
		__doge_end = .;
	}
}
