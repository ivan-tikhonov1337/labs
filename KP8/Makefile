CC ?= gcc
CFLAGS ?= -Werror -pedantic
main: main.o two-sided_list.o
	$(CC) -o main main.o two-sided_list.o

main.o: main.c
	$(CC) $(CFLAGS) -c main.c

two-sided_list.o: two-sided_list.c two-sided_list.h
	$(CC) $(CFLAGS) -c two-sided_list.c

clean:
	rm -rf *.o main
