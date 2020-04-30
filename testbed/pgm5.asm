%include "IOSR.asm"
global _start


section .data
	A	DW	5
	B	DW	3


section .bss
	temp0	RESW	1
	temp1	RESW	1


section .txt

_start:





	mov ax, [A]
	call ConvertIntegerToString
	mov eax, 4
	mov ebx, 1
	mov ecx, Result
	mov edx, ResultEnd
	int 80h




	mov ax, [B]
	call ConvertIntegerToString
	mov eax, 4
	mov ebx, 1
	mov ecx, Result
	mov edx, ResultEnd
	int 80h




	call fini
