CC = gcc
CFLAGS = -I. -lm
DEPS = lexy.h lisa.h
OBJ = lexy.o lisa.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

lexy: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) -O3 && rm *.o
