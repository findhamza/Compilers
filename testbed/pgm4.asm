%include "IOSR.asm"
global _start


section .data
	fifteen	DW	15
	one	DW	1
	twelve	DW	12
	four	DW	4
	lit1	DW	1


section .bss
	result	RESW	1
	temp0	RESW	1
	temp1	RESW	1
	temp2	RESW	1
	temp3	RESW	1
	temp4	RESW	1


section .txt

_start:

	mov ax, [lit1]
	mul word [twelve]
	mov [temp0], ax


	mov dx, 0
	mov ax, [temp0]
	div word [four]
	mov [temp1], ax


	mov ax, [temp1]
	add ax, [one]
	mov [temp2], ax


	mov ax, [fifteen]
	sub ax, [temp2]
	mov [temp3], ax


	mov ax, [temp3]
	mov [result], ax


	mov ax, [result]
	call ConvertIntegerToString
	mov eax, 4
	mov ebx, 1
	mov ecx, Result
	mov edx, ResultEnd
	int 80h


	call fini
