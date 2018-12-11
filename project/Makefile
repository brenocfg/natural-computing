#Compile with some extra warnings
CFLAGS=-c -O3 -Wall -Wextra

#Library flags
LIBFLAGS=-O3 -lm

#Targets
all: rwa

rwa: main.o graph.o ind.o gen.o
	gcc graph.o main.o ind.o gen.o $(LIBFLAGS) -o rwa

gen.o: src/gen.c src/ind.h src/graph.h src/gen.h
	gcc $(CFLAGS) src/gen.c

ind.o: src/ind.c src/ind.h src/graph.h
	gcc $(CFLAGS) src/ind.c

graph.o: src/graph.c src/graph.h
	gcc $(CFLAGS) src/graph.c

main.o: src/main.c src/graph.h
	gcc $(CFLAGS) src/main.c

run:
clean:
	rm *.o rwa
