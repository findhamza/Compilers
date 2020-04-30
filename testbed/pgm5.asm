%include "IOSR.asm"
global _start


section .data


section .bss
	A	RESW	1
	B	RESW	1


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
	jl L0
	jge L1

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

	mov ax, [A]
	cmp ax, [B]
	jle L6
	jg L7

L6:




	mov ax, [A]
	call ConvertIntegerToString
	mov eax, 4
	mov ebx, 1
	mov ecx, Result
	mov edx, ResultEnd
	int 80h


	jmp L8
L7:	nop

	mov ax, [B]
	call ConvertIntegerToString
	mov eax, 4
	mov ebx, 1
	mov ecx, Result
	mov edx, ResultEnd
	int 80h


L8:	nop

	mov ax, [A]
	cmp ax, [B]
	jge L9
	jl L10

L9:




	mov ax, [A]
	call ConvertIntegerToString
	mov eax, 4
	mov ebx, 1
	mov ecx, Result
	mov edx, ResultEnd
	int 80h


	jmp L11
L10:	nop

	mov ax, [B]
	call ConvertIntegerToString
	mov eax, 4
	mov ebx, 1
	mov ecx, Result
	mov edx, ResultEnd
	int 80h


L11:	nop

	mov ax, [A]
	cmp ax, [B]
	je L12
	jne L13

L12:




	mov ax, [A]
	call ConvertIntegerToString
	mov eax, 4
	mov ebx, 1
	mov ecx, Result
	mov edx, ResultEnd
	int 80h


	jmp L14
L13:	nop

	mov ax, [B]
	call ConvertIntegerToString
	mov eax, 4
	mov ebx, 1
	mov ecx, Result
	mov edx, ResultEnd
	int 80h


L14:	nop

	call fini
