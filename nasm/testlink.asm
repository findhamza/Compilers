%include "IOSR.asm"

global _start
section .data
	M	DW	7
section .bss
	X	RESW	1
section .data
	N	DW	8
section .txt

_start:
hello:
	; prompt user for positive number	
	mov eax, sys_write		;Linux print device register conventions
	mov ebx, stdout		; print default output device
	mov ecx, userMsg	; pointer to string
	mov edx, lenUserMsg	; arg1, where to write, screen
	int	80h		; interrupt 80 hex, call kernel
	
	;get responce as a character string
	mov	eax, sys_read	; read
	mov	ebx, stdin	;stdin	 
	mov 	ecx, num	; Address of input buffer
	mov 	edx, 6		; max bytes to read
	int	0x80		; interrupt 80 hex, call kernel
	;push eax 		; system returns # characters read in eax register
	;call ReadData		;

	;print number from character string
	mov edx,eax	; edx has num characters read including <lf> ****
	mov eax, 4	;write
	mov ebx, 1	;print default sys_out
	mov ecx, num	;start address for print
	int 80h

	call fini
