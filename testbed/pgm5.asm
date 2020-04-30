%include "IOSR.asm"
global _start


section .data


section .bss
	A	RESW	1
	B	RESW	1
	temp0	RESW	1
	temp1	RESW	1


section .txt

_start:

	call PrintString
	call GetAnInteger
	mov ax, [ReadInt]
	mov [A], ax


	call PrintString
	call GetAnInteger
	mov ax, [ReadInt]
	mov [B], ax


	mov ax, [A]
	cmp ax, [B]
	jle L0
	jg L1

L0:




	mov ax, [A]
	call ConvertIntegerToString
	mov eax, 4
	mov ebx, 1
	mov ecx, Result
	mov edx, ResultEnd
	int 80h


	jmp L2
L1:	nop

	mov ax, [B]
	call ConvertIntegerToString
	mov eax, 4
	mov ebx, 1
	mov ecx, Result
	mov edx, ResultEnd
	int 80h


L2:	nop

	mov ax, [A]
	cmp ax, [B]
	jg L3
	jle L4

L3:




	mov ax, [A]
	call ConvertIntegerToString
	mov eax, 4
	mov ebx, 1
	mov ecx, Result
	mov edx, ResultEnd
	int 80h


	jmp L5
L4:	nop

	mov ax, [B]
	call ConvertIntegerToString
	mov eax, 4
	mov ebx, 1
	mov ecx, Result
	mov edx, ResultEnd
	int 80h


L5:	nop

	call fini
