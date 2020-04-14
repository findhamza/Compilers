CC = gcc
CFLAGS = -I. -lm -g
DEPS = paris.h missy.h ../lexy/syslib.h ../lexy/struct.h ../lexy/lisa.h ../lexy/glarr.h
OBJ = paris.o missy.o ../lexy/lisa.o 

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

paris: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) -O3 && rm *.o
