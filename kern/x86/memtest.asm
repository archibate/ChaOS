; vim: ft=nasm ai

%include "cext.inc"

	GLOBALC memory_test

[SECTION .phys.text]
[BITS 32]

; void memory_test(ulong *p_start, size_t *p_size);
memory_test:
	push ebp
	mov ebp, esp
	push esi
	push edi
	push ebx
	mov ebx, [ebp +  8] ; p_start
	mov edi, [ebp + 12] ; p_size
	mov esi, [ebx]
	mov edx, [edi]
	push edi
	push ebx
	call probeRAM
	pop ebx
	pop edi
	mov [ebx], esi
	mov [edi], ecx
	pop ebx
	pop edi
	pop esi
	leave
	ret

; https://wiki.osdev.org/Detecting_Memory_(x86)#Manual_Probing_in_ASM

;Probe to see if there's RAM at a certain address 
;
; note: "dummy" -> a known good memory address that has nothing important in it
; 
;Input 
; edx   Maximum number of bytes to test 
; esi   Starting address 
; 
;Output 
; ecx   Number of bytes of RAM found 
; esi   Address of RAM 
 
probeRAM: 
    push eax
    push ebx
    push edx
    push ebp 
    mov ebp,esi             ;ebp = starting address
    add esi,0x00000FFF      ;round esi up to block boundary
    and esi, ~0x00000FFF    ;truncate to block boundary
    push esi                ;Save corrected starting address for later
    mov eax, esi            ;eax = corrected starting address
    sub eax, ebp            ;eax = bytes to skip from original starting address, due to rounding
    xor ecx,ecx             ;ecx = number of bytes of RAM found so far (none)
    sub edx,eax             ;edx = number of bytes left to test
    jc .done                ;  all done if nothing left after rounding
    or esi,0x00000FFC       ;esi = address of last uint32_t in first block
    shr edx,12              ;edx = number of blocks to test (rounded down)
    je .done                ; Is there anything left after rounding?
 
.testAddress:
    mov eax,[esi]           ;eax = original value
    mov ebx,eax             ;ebx = original value
    not eax                 ;eax = reversed value
    mov [esi],eax           ;Modify value at address
    mov [dummy],ebx         ;Do dummy write (that's guaranteed to be a different value)
    wbinvd                  ;Flush the cache
    mov ebp,[esi]           ;ebp = new value
    mov [esi],ebx           ;Restore the original value (even if it's not RAM, in case it's a memory mapped device or something)
    cmp ebp,eax             ;Was the value changed?
    jne .done               ; no, definitely not RAM -- exit to avoid damage
                            ; yes, assume we've found some RAM
 
    add ecx,0x00001000      ;ecx = new number of bytes of RAM found
    add esi,0x00001000      ;esi = new address to test
    dec edx                 ;edx = new number of blocks remaining
    jne .testAddress        ;more blocks remaining?
                            ;If not, we're done
 
.done:
    pop esi                 ;esi = corrected starting address (rounded up)
    pop ebp
    pop edx
    pop ebx
    pop eax
    ret
	
[SECTION .phys.data]
dummy:
	dd 0xdeadbeaf