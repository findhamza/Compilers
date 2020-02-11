CC = gcc
CFLAGS = -I. -lm
OBJ = lexy.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

lexy: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) -O3 && rm *.o
