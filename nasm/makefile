APP = testlink

$(APP): $(APP).o IOSR.o
	ld -o $(APP) $(APP).o IOSR.o

$(APP).o: $(APP).asm
	nasm -felf64 $(APP).asm

IOSR.o: IOSR.asm
	nasm -felf64 IOSR.asm

