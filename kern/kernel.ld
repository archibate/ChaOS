#include <mm/kbase.h>

ENTRY(_start)
OUTPUT_FORMAT("elf32-i386")

/*KPBEG = 0x8000;*/
/*KBASE = 0xc0000000;*/

#define PSEC(sec) sec :
#define VSEC(sec) sec : AT(ADDR(sec) - KBASE)

/* https://github.com/archibate/jos/blob/master/lab4/partB/kern/kernel.ld */
SECTIONS
{
	. = KCODBEG;

	PSEC(.phys)
	{
		*(.phys .stub .phys.*)
	}

	. += KBASE;

	VSEC(.text)
	{
		*(.text .text.* .gnu.linkonce.t.*)
	}
	VSEC(.rodata)
	{
		*(.rodata .rodata.* .gnu.linkonce.r.*)
	}
	VSEC(.stab)
	{
		*(.stab)
	}
	VSEC(.stabstr)
	{
		*(.stabstr)
	}
	
	. = ALIGN(4096);
	VSEC(.data)
	{
		*(.data)
		*(.note* .comment*)
		. = ALIGN(4096);
		*(.sigma0.data)
		. = ALIGN(4096);
	}
	
	. = ALIGN(4096);
	VSEC(.bss)
	{
		*(.bss)
		. = ALIGN(4096);
	}
	
	/DISCARD/ :
	{
		*(.eh_frame .note.GNU-stack)
	}
}
