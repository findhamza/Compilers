CC = gcc
CFLAGS = -I. -lm -g
DEPS = nancy.h ../lexy/syslib.h ../lexy/struct.h ../lexy/lisa.h ../lexy/glarr.h
OBJ = nancy.o ../lexy/lisa.o 

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

nancy: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) -O3 && rm *.o
