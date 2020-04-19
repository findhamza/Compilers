CC = gcc
CFLAGS = -I. -lm -g
DEPS = paris.h marry.h ../lexy/syslib.h ../lexy/struct.h ../lexy/lisa.h ../lexy/glarr.h
OBJ = paris.o marry.o ../lexy/lisa.o 

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

paris: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) -O3 && rm *.o
