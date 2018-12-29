; vim: ft=nasm ai

%include "cext.inc"

	EXTERNC hwintr
	GLOBALC __intrents
	GLOBALC intreturn

[SECTION .data]
__intrents:

[SECTION .text]
[BITS 32]

introute:
	push ds
	push es
	push fs
	push gs
	pushad
	mov eax, ss
	mov ds, eax
	mov es, eax
	push esp
	call hwintr
	add esp, 4
intreturn:
	popad
	pop gs
	pop fs
	pop es
	pop ds
	add esp, 8
	iretd

%macro NC 1
[SECTION .data]
	dd ent%1
[SECTION .text]
ent%1:
	push 0
	push %1
	jmp introute
%endmacro

%macro EC 1
[SECTION .data]
	dd ent%1
[SECTION .text]
ent%1:
	push %1
	jmp introute
%endmacro

%include "x86/intrents.inc"