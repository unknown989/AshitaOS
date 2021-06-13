MBALIGN  equ  1 << 0            ; align loaded modules on page boundaries
MEMINFO  equ  1 << 1            ; provide memory map
FLAGS    equ  MBALIGN | MEMINFO ; this is the Multiboot 'flag' field
MAGIC    equ  0x1BADB002        ; 'magic number' lets bootloader find the header
CHECKSUM equ -(MAGIC + FLAGS)   ; checksum of above, to prove we are multiboot
 
section .multiboot
align 4
	dd MAGIC
	dd FLAGS
	dd CHECKSUM
 
section .bss
align 16
stack_bottom:
resb 16384 ; 16 KiB
stack_top:

enter_v86:
	mov ebp,esp ; save stack pointer

	push dword [ebp+4]
	push dword [ebp+8]
	pushfd
	or dword [esp] ,(1 << 17)
	push dword [ebp+12]
	push dword [ebp+16]
	iret

detect_v86:
	smsw ax
	and eax,1
	ret

section .text
global _start:function (_start.end - _start)
_start:
 
	extern kmain
	call kmain
 
	cli
.hang:	hlt
	jmp .hang
.end:
