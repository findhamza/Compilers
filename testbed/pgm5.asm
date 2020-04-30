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

	call fini
