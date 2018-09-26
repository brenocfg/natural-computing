#Compile with some extra warnings
CFLAGS=-c -Wall -Wextra

#Library flags
LIBFLAGS=-lm

#Targets
all: gen

gen: tree.o main.o
	gcc tree.o main.o $(LIBFLAGS) -o gen

tree.o: tree.c
	gcc $(CFLAGS) tree.c

main.o: main.c
	gcc $(CFLAGS) main.c

clean:
	rm *.o gen
