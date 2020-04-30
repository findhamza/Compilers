%include "IOSR.asm"
global _start


section .data


section .bss
	somevar	RESW	1
	othervar	RESW	1
	ans	RESW	1
	temp0	RESW	1
	temp1	RESW	1


section .txt

_start:

	call PrintString
	call GetAnInteger
	mov ax, [ReadInt]
	mov [somevar], ax


	call PrintString
	call GetAnInteger
	mov ax, [ReadInt]
	mov [othervar], ax


	mov ax, [somevar]
	mul word [othervar]
	mov [temp0], ax


	mov ax, [temp0]
	mov [ans], ax


	mov ax, [ans]
	call ConvertIntegerToString
	mov eax, 4
	mov ebx, 1
	mov ecx, Result
	mov edx, ResultEnd
	int 80h


	mov dx, 0
	mov ax, [somevar]
	div word [othervar]
	mov [temp0], ax


	mov ax, [temp0]
	mov [ans], ax


	mov ax, [ans]
	call ConvertIntegerToString
	mov eax, 4
	mov ebx, 1
	mov ecx, Result
	mov edx, ResultEnd
	int 80h


	mov ax, [somevar]
	add ax, [othervar]
	mov [temp0], ax


	mov ax, [temp0]
	mov [ans], ax


	mov ax, [ans]
	call ConvertIntegerToString
	mov eax, 4
	mov ebx, 1
	mov ecx, Result
	mov edx, ResultEnd
	int 80h


	mov ax, [somevar]
	sub ax, [othervar]
	mov [temp0], ax


	mov ax, [temp0]
	mov [ans], ax


	mov ax, [ans]
	call ConvertIntegerToString
	mov eax, 4
	mov ebx, 1
	mov ecx, Result
	mov edx, ResultEnd
	int 80h


	call fini
