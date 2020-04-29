CC = gcc
CFLAGS = -I -lm -g
DEPS = ../lexy/syslib.h
OBJ = driver.o ../lexy/lexy.o ../lexy/lisa.o ../paris/paris.o ../paris/marry.o ../nancy/nancy.o ../nancy/ophelia.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

driver: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) -O3 && rm *.o

