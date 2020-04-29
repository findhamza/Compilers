%include "IOSR.asm"
global _start


section .data
	M	DW	13
	N	DW	56
	lit97	DW	97
	lit18	DW	18


section .bss
	X	RESW	1
	Y	RESW	1
	Z	RESW	1
	temp0	RESW	1
	temp1	RESW	1
	temp2	RESW	1
	temp3	RESW	1


section .txt

_start:

	mov ax, [lit97]
	mov [Y], ax


	mov ax, [M]
	mul word [N]
	mov [temp0], ax


	mov ax, [temp0]
	add ax, [lit18]
	mov [temp1], ax


	mov ax, [temp1]
	sub ax, [Y]
	mov [temp2], ax


	mov ax, [temp2]
	mov [X], ax


	mov ax, [X]
	call ConvertIntegerToString
	mov eax, 4
	mov ebx, 1
	mov ecx, Result
	mov edx, ResultEnd
	int 80h


	call fini
