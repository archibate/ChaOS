; vim: ft=nasm ai

%include "cext.inc"

KBASE	equ	0xc0000000

	GLOBAL  _start
	EXTERNC kern_main
	EXTERNC memory_test
	EXTERNC meminfo
	EXTERNC init_afterbootvm

[SECTION .phys.text]
[BITS 32]

_start:
	call kern_physetup
	push highstart
	ret

kern_physetup:
	lea eax, [meminfo - KBASE]
	mov ecx, dword [eax + 4]
	sub ecx, dword [eax]
	mov dword [dummy], ecx
	push dummy
	push eax
	call memory_test
	add esp, 8
	mov ecx, dword [dummy]
	add ecx, dword [eax]
	mov dword [eax + 4], ecx

	mov eax, 7
	lea edi, [boot_pt0]
	mov ecx, 1024
.again:
	stosd
	add eax, 4096
	loop .again
	mov eax, boot_pd
	mov edx, boot_pt0 + 7
	mov dword [eax], edx
	mov dword [eax + 4*(KBASE>>22)], edx
	mov cr3, eax
	mov eax, cr0
	or eax, (1<<31)
	mov cr0, eax
	ret

[SECTION .phys.bss]
dummy:
	dd 0
	ALIGNB 4096
boot_pd:
	resd 1024
boot_pt0:
	resd 1024
	
[SECTION .text]
highstart:
	call init_afterbootvm
	mov cr3, eax
	lea esp, [initial_stktop]
	call kern_main
	
	mov byte [KBASE + 0xb8000], 'O'
	mov byte [KBASE + 0xb8002], 'K'
halt:
	cli
	hlt
	jmp halt
	
initial_stktop equ KBASE + 0x9ff00
