; vim: ft=nasm ai

%include "cext.inc"

	GLOBAL  _start
	EXTERNC	sigma0_main

[SECTION .text]
[BITS 32]
_start:
	call sigma0_main
	jmp $
