ENTRY(_start)
OUTPUT_FORMAT(elf32-i386)

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
		*(.data .data.*)
		*(.note* .comment*)
		. = ALIGN(4096);
	}
	
	. = ALIGN(4096);
	.bss :
	{
		*(.bss .bss.*)
		. = ALIGN(4096);
	}
	
	/DISCARD/ :
	{
		*(.eh_frame .note.GNU-stack)
	}
}
