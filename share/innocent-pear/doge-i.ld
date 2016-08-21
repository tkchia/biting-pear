SECTIONS
{
	.data.rel :
	{
		/*
		 * These likely contain references to _ZTIi ("typeinfo for
		 * int"), __gxx_personality_v0, etc. which -- if we are
		 * using dynamic linking -- cannot resolved at static link
		 * time.
		 */
		*(.data.rel .data.DW.ref.*)
	}
}
INSERT AFTER .data;
