CC = gcc
CFLAGS = -I. -lm -g
DEPS = nancy.h ophelia.h ../lexy/syslib.h ../lexy/struct.h ../lexy/lisa.h ../lexy/glarr.h
OBJ = nancy.o ophelia.o ../lexy/lisa.o 

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

nancy: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) -O3 && rm *.o
