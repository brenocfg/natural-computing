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

run:
	./aco input/graph3.txt 0.05 100 1000 111 2>/dev/null
	./aco input/graph3.txt 0.05 100 1000 222 2>/dev/null
	./aco input/graph3.txt 0.05 100 1000 333 2>/dev/null
	./aco input/graph3.txt 0.05 100 1000 444 2>/dev/null
	./aco input/graph3.txt 0.05 100 1000 555 2>/dev/null
	./aco input/graph3.txt 0.05 400 1000 111 2>/dev/null
	./aco input/graph3.txt 0.05 400 1000 222 2>/dev/null
	./aco input/graph3.txt 0.05 400 1000 333 2>/dev/null
	./aco input/graph3.txt 0.05 400 1000 444 2>/dev/null
	./aco input/graph3.txt 0.05 400 1000 555 2>/dev/null
	./aco input/graph3.txt 0.05 700 1000 111 2>/dev/null
	./aco input/graph3.txt 0.05 700 1000 222 2>/dev/null
	./aco input/graph3.txt 0.05 700 1000 333 2>/dev/null
	./aco input/graph3.txt 0.05 700 1000 444 2>/dev/null
	./aco input/graph3.txt 0.05 700 1000 555 2>/dev/null
	./aco input/graph3.txt 0.05 1000 1000 111 2>/dev/null
	./aco input/graph3.txt 0.05 1000 1000 222 2>/dev/null
	./aco input/graph3.txt 0.05 1000 1000 333 2>/dev/null
	./aco input/graph3.txt 0.05 1000 1000 444 2>/dev/null
	./aco input/graph3.txt 0.05 1000 1000 555 2>/dev/null
clean:
	rm *.o aco
