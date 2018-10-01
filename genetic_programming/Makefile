#Compile with some extra warnings
CFLAGS=-c -g -O3 -Wall -Wextra

#Library flags
LIBFLAGS=-lm

#Targets
all: gen

gen: tree.o main.o gen.o
	gcc tree.o gen.o main.o $(LIBFLAGS) -o gen

gen.o: gen.c
	gcc $(CFLAGS) gen.c

tree.o: tree.c
	gcc $(CFLAGS) tree.c

main.o: main.c
	gcc $(CFLAGS) main.c

clean:
	rm *.o gen
