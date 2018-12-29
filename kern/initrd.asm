; vim: ft=nasm ai

%include "cext.inc"

	GLOBALC sigma0_beg
	GLOBALC sigma0_end

[SECTION .data]
	alignb 4096
sigma0_beg:
	incbin "../sigma0/sigma0.bin"
	alignb 4096
sigma0_end:
