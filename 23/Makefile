CC ?= gcc
CFLAGS ?= -Werror -pedantic
main: main.o tree.o
	$(CC) -o main main.o tree.o

main.o: main.c
	$(CC) $(CFLAGS) -c main.c

tree.o: tree.c tree.h
	$(CC) $(CFLAGS) -c tree.c

clean:
	rm -rf *.o main
