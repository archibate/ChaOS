; vim: ft=nasm ai

CYLS	equ	6

	org 0x7c00

[BITS 16]

_start:
	jmp entry
	nop
	;times 62-($-$$) db 0
bsOEMName	db        "CHAOS   "        ; 启动区的名称（8字节）
bpbBytesPerSec	dw        512                ; 每个扇区（sector）的大小
bpbSecPerClus	db        1                ; 簇（cluster）的大小
bpbRsvdSecs	dw        2                ; FAT的起始位置
bpbNumFATs	db        2                ; FAT的个数
bpbRootEnts	dw        224               ; 根目录的大小
bpbTotSec16	dw        2880            ; 该磁盘的大小
bpbMedia	db        0xf0            ; 磁盘的种类
bpbFATSize16	dw        9                ; FAT的长度
bpbSecPerTrack	dw        18                ; 1个磁道（track）有几个扇区
bpbNumHeads	dw        2                ; 磁头数
bpbHiddSecs	dd        0                ; 不使用分区数
bpbTotSec32	dd        2880            ; 重写一次磁盘大小
bsDrvNum	db        0x00            ; 磁盘在 BIOS 中的代号
bsReserved1	db        0               ; 保留（必须为0）
bsBootSig	db        0x29            ; 启动签名（意义不明）
bsVolNumber	dd        0xffffffff      ; 磁盘的卷号码
bsVolLabel	db        "           "    ; 磁盘的卷标（11字节）
bsFSysType	db        "FAT12   "       ; 磁盘格式名称（8字节）

entry:
	xor ax, ax
	mov ds, ax
	mov es, ax
	mov ss, ax
	mov sp, _start

	mov si, msg_loading
	call print
	
	; bochs seems turning on CD&NW by default...
	mov eax, cr0
	and eax, 0x9fffffff ; ~(CR0_CD | CR0_NW)
	mov cr0, eax

load_setup:
	mov ax, 0x07e0 ; just after us
	mov es, ax
	mov cx, 0x0002 ; cyln 0, sect 2
	movzx dx, byte [bsDrvNum] ; head 0, drvr 0
.loop:	mov si, 5
.retry:	mov ax, 0x0201
	xor bx, bx
	int 0x13
	jnc .next
	dec si
	jz error
	mov ah, 0x00
	mov dl, 0x00
	int 0x13
	mov ax, 0x0e2f
	int 0x10
	jmp .retry
.next:	mov ax, es
	add ax, 0x0020
	mov es, ax
	inc cl
	cmp cl, 18
	jbe .loop
	mov cl, 1
	inc dh
	cmp dh, 2
	jb .loop
	mov ax, 0x0e2e
	int 0x10
	mov dh, 0
	inc ch
	cmp ch, CYLS
	jb .loop

	mov si, msg_done
	call print
	jmp stage2

error:
	mov si, msg_err
	call print
	mov ah, 0x00
	int 0x16
	int 0x19
halt:
	cli
fin:
	hlt
	jmp fin

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

msg_loading:
	db "Loading System", 0
msg_done:
	db "done", 13, 10, 0
msg_err:
	db 13, 10, "ERROR occurred, Press any key to reset", 13, 10, 0

	times 510-($-$$) db 0

	dw 0xaa55
stage2: