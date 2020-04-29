%include "IOSR.asm"
global _start


section .data
	A	DW	9
	B	DW	10


section .bss
	C	RESW	1
	D	RESW	1
	E	RESW	1
	temp0	RESW	1


section .txt

_start:

	mov ax, [A]
	mov [C], ax


	mov ax, [C]
	mov [D], ax


	mov ax, [B]
	mov [E], ax


	mov ax, [C]
	call ConvertIntegerToString
	mov eax, 4
	mov ebx, 1
	mov ecx, Result
	mov edx, ResultEnd
	int 80h


	mov ax, [D]
	call ConvertIntegerToString
	mov eax, 4
	mov ebx, 1
	mov ecx, Result
	mov edx, ResultEnd
	int 80h


	mov ax, [E]
	call ConvertIntegerToString
	mov eax, 4
	mov ebx, 1
	mov ecx, Result
	mov edx, ResultEnd
	int 80h


	call fini
