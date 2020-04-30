%include "IOSR.asm"
global _start


section .data
	yes	DW	1
	no	DW	0
	two	DW	2
	lit2	DW	2


section .bss
	quotient	RESW	1
	number	RESW	1
	temp0	RESW	1
	temp1	RESW	1
	temp2	RESW	1


section .txt

_start:

	call PrintString
	call GetAnInteger
	mov ax, [ReadInt]
	mov [number], ax


	mov dx, 0
	mov ax, [number]
	div word [two]
	mov [temp0], ax


	mov ax, [temp0]
	mov [quotient], ax


	mov ax, [quotient]
	mul word [lit2]
	mov [temp0], ax


	mov ax, [temp0]
	mov [quotient], ax


	mov ax, [quotient]
	cmp ax, [number]
	je L0
	jne L1

L0:




	mov ax, [yes]
	call ConvertIntegerToString
	mov eax, 4
	mov ebx, 1
	mov ecx, Result
	mov edx, ResultEnd
	int 80h


	jmp L2
L1:	nop

	mov ax, [no]
	call ConvertIntegerToString
	mov eax, 4
	mov ebx, 1
	mov ecx, Result
	mov edx, ResultEnd
	int 80h


L2:	nop

	call fini
