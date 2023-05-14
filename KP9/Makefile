CC ?= gcc
CFLAGS ?= -Werror -pedantic
main: main.o table.o
	$(CC) -o main main.o table.o

main.o: main.c
	$(CC) $(CFLAGS) -c main.c

table.o: table.c table.h
	$(CC) $(CFLAGS) -c table.c

clean:
	rm -rf *.o main
