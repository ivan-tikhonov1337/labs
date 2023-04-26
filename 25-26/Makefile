CC ?= gcc
CFLAGS ?= -Werror -pedantic
main: main.o deque.o
	$(CC) -o main main.o deque.o

main.o: main.c
	$(CC) $(CFLAGS) -c main.c

deque.o: deque.c deque.h
	$(CC) $(CFLAGS) -c deque.c

clean:
	rm -rf *.o main
