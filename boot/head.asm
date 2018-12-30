; vim: ft=nasm ai

%include	"boot.inc"

	org 0x7e00

[BITS 16]

_start:
	xor ax, ax
	mov ds, ax
	mov es, ax

	mov si, msg_setup
	call print

enable_32:
	cli
	call delay
	mov al, 0xd1
	out 0x64, al
	call delay
	mov al, 0xdf
	out 0x60, al
	call delay

	lgdt [gdtr0]
	lidt [idtr0]
	mov eax, cr0
	or eax, 0x1
	mov cr0, eax
	jmp .flush
.flush:
	mov ax, 0x0010
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov ss, ax
	jmp dword 0x0008:start32
	
delay:
	in al, 0x64
	and al, 0x02
	jnz delay
	ret

print:
	mov ah, 0x0e
	mov bx, 15
.loop:
	lodsb
	test al, al
	jz .done
	int 0x10
	jmp .loop
.done:
	ret
	
	alignb 16
gdt0:
	dw 0x0000, 0x0000, 0x0000, 0x0000
	dw 0xffff, 0x0000, 0x9a00, 0x00cf
	dw 0xffff, 0x0000, 0x9200, 0x00cf
	dw 0xffff, 0x0000, 0xfa00, 0x00cf
	dw 0xffff, 0x0000, 0xf200, 0x00cf
	dw 0x0000, 0x0000, 0x0000, 0x0000
	dw 0x0000, 0x0000, 0x0000, 0x0000
gdtr0:
	dw $-gdt0-1
	dd gdt0
idtr0:
	dw 0
	dd 0

msg_setup:
	db "Seting up kernel...", 0

[BITS 32]
start32:
	lea edi, [kernel + KFSIZ]
	mov ecx, KZSIZ
	xor eax, eax
	rep stosb
	jmp kernel

	times 512-($-$$) db 0
kernel:
