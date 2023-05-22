CC ?= gcc
CFLAGS ?= -Werror -pedantic
main: main.o base.o
	$(CC) -o main main.o base.o

main.o: main.c
	$(CC) $(CFLAGS) -c main.c

base.o: base.c base.h
	$(CC) $(CFLAGS) -c base.c

clean:
	rm -rf *.o main
