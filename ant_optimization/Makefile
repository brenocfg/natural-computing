#Compile with some extra warnings
CFLAGS=-c -O3 -Wall -Wextra

#Library flags
LIBFLAGS=-O3 -lm

#Targets
all: aco

aco: aco.o main.o graph.o
	gcc graph.o aco.o main.o $(LIBFLAGS) -o aco

aco.o: aco.c
	gcc $(CFLAGS) aco.c

graph.o: graph.c
	gcc $(CFLAGS) graph.c

main.o: main.c
	gcc $(CFLAGS) main.c

clean:
	rm *.o aco
