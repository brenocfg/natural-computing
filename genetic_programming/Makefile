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

run:
	./gen input/concrete/concrete-train.csv input/concrete/concrete-test.csv \
	111 500 250 0 0.8 5 2>/dev/null
	./gen input/concrete/concrete-train.csv input/concrete/concrete-test.csv \
	222 500 250 0 0.8 5 2>/dev/null
	./gen input/concrete/concrete-train.csv input/concrete/concrete-test.csv \
	333 500 250 0 0.8 5 2>/dev/null
	./gen input/concrete/concrete-train.csv input/concrete/concrete-test.csv \
	444 500 250 0 0.8 5 2>/dev/null
	./gen input/concrete/concrete-train.csv input/concrete/concrete-test.csv \
	555 500 250 0 0.8 5 2>/dev/null

clean:
	rm *.o gen
