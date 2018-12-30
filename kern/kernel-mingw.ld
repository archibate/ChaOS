ENTRY(_start)
OUTPUT_FORMAT(pe32-i386)

KPBEG = 0x8000;
KBASE = 0xc0000000;

/* https://github.com/archibate/jos/blob/master/lab4/partB/kern/kernel.ld */
SECTIONS
{
	. = KPBEG + KBASE;
	
	.phys : /*AT(KPBEG)*/
	{
		*(.phys .phys.*)
	}
	
	.text :
	{
		*(.text .stub .text.* .gnu.linkonce.t.*)
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
