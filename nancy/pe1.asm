%include "IOSR.asm"
global _start


section .data
	M	DW	7
	N	DW	85
	lit12	DW	12


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

	call PrintString
	call GetAnInteger
	mov ax, [ReadInt]
	mov [Y], ax


	call PrintString
	call GetAnInteger
	mov ax, [ReadInt]
	mov [Z], ax


	mov ax, [Y]
	mul word [Z]
	mov [temp0], ax


	mov ax, [temp0]
	add ax, [lit12]
	mov [temp1], ax


	mov ax, [M]
	add ax, [temp1]
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
