ENTRY(_start)

UBASE = 0x800000;

/* https://github.com/archibate/jos/blob/master/lab4/partB/kern/kernel.ld */
SECTIONS
{
	. = UBASE;
	
	.text :
	{
		*(.text .text.* .gnu.linkonce.t.*)
	}
	.rodata :
	{
		*(.rodata .rodata.* .gnu.linkonce.r.*)
	}
	.stab :
	{
		*(.stab)
	}
	.stabstr :
	{
		*(.stabstr)
	}
	
	. = ALIGN(4096);
	.data :
	{
		*(.data)
	}
	
	. = ALIGN(4096);
	.bss :
	{
		*(.bss)
		. = ALIGN(4096);
	}
	
	/DISCARD/ :
	{
		*(.eh_frame .note.GNU-stack)
	}
}
