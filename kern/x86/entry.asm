; vim: ft=nasm ai

%include "cext.inc"

KBASE	equ	0xc0000000

	GLOBAL  _start
	EXTERNC kern_main
	EXTERNC kern_physetup

[SECTION .phys.text]
[BITS 32]

_start:
	call kern_physetup
	push highstart
	ret
	
[SECTION .text]
highstart:
	lea esp, [initial_stktop]
	call kern_main
	
	mov byte [KBASE + 0xb8000], 'O'
	mov byte [KBASE + 0xb8002], 'K'
halt:
	cli
	hlt
	jmp halt
	
initial_stktop equ KBASE + 0x9ff00