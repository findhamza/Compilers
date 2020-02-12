CC = gcc
CFLAGS = -I. -lm
OBJ = state.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

lexy: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) -O3 && rm *.o
