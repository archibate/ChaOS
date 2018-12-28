; vim: ft=nasm ai

%include "cext.inc"

	GLOBALC initrd_beg
	GLOBALC initrd_end

[SECTION .data]
initrd_beg:
	incbin "../init/init.bin"
initrd_end:
