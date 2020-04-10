CC = gcc
CFLAGS = -I. -lm
DEPS = paris.h
OBJ = paris.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

paris: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) -O3 && rm *.o
