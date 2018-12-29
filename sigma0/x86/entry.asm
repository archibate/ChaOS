; vim: ft=nasm ai

%include "cext.inc"

	GLOBAL  _start

[SECTION .text]
[BITS 32]
_start:
	cli
	hlt
	jmp $
