ENTRY(_start)
OUTPUT_FORMAT("elf32-i386")
KPBEG = 0x8000;
KBASE = 0xc0000000;
SECTIONS
{
 . = KPBEG;
 .phys :
 {
  *(.phys .stub .phys.*)
 }
 . += KBASE;
 .text : AT(ADDR(.text) - KBASE)
 {
  *(.text .text.* .gnu.linkonce.t.*)
 }
 .rodata : AT(ADDR(.rodata) - KBASE)
 {
  *(.rodata .rodata.* .gnu.linkonce.r.*)
 }
 .stab : AT(ADDR(.stab) - KBASE)
 {
  *(.stab)
 }
 .stabstr : AT(ADDR(.stabstr) - KBASE)
 {
  *(.stabstr)
 }
 . = ALIGN(4096);
 .data : AT(ADDR(.data) - KBASE)
 {
  *(.data)
  *(.note* .comment*)
  . = ALIGN(4096);
  *(.sigma0.data)
 }
 . = ALIGN(4096);
 .bss : AT(ADDR(.bss) - KBASE)
 {
  *(.bss)
  . = ALIGN(4096);
 }
 /DISCARD/ :
 {
  *(.eh_frame .note.GNU-stack)
 }
}
