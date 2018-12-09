#Compile with some extra warnings
CFLAGS=-c -O3 -Wall -Wextra

#Library flags
LIBFLAGS=-O3 -lm

#Targets
all: rwa

rwa: main.o graph.o
	gcc graph.o main.o $(LIBFLAGS) -o rwa

#aco.o: aco.c
	#gcc $(CFLAGS) aco.c

graph.o: src/graph.c src/graph.h
	gcc $(CFLAGS) src/graph.c

main.o: src/main.c src/graph.h
	gcc $(CFLAGS) src/main.c

run:
clean:
	rm *.o rwa
