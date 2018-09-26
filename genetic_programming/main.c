#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "tree.h"

double *read_input(char *filename, uint16_t *num_vars, uint16_t *num_lines) {
	FILE *input = fopen(filename, "r");
	if (input == NULL) {
		fprintf(stderr, "Error reading input file!\n");
	}

	int num_col, num_line;
	fscanf(input, "%d %d\n",(unsigned int*) &num_col,(unsigned int*) &num_line);

	*(num_vars) = num_col;
	*(num_lines) = num_line;

	double *ret = malloc(num_col*num_line*sizeof(double));	
	int i, j;
	for (i = 0; i < num_line; i++) {
		for (j = 0; j < num_col; j++) {
			fscanf(input, "%lf,", &ret[i*num_col + j]);
		}
	}

	fclose(input);

	return ret;
}

int main(int argc, char *argv[]) {
	if (argc < 4) {
		fprintf(stderr, "Not enough input arguments!\n");
		fprintf(stderr, "Usage: ./gen <train_file> <test_file> <seed>\n");
		return 0;
	}

	fprintf(stderr, "train = %s, input = %s\n", argv[1], argv[2]);

	uint16_t num_vars_train, num_vars_test;
	uint16_t num_lines_train, num_lines_test;

	double *train_input = read_input(argv[1], &num_vars_train, &num_lines_train);
	double *test_input = read_input(argv[2], &num_vars_test, &num_lines_test);

	int seed = atoi(argv[3]);
	srand(seed);

	int i;
	struct node *mynode = build_tree(0, num_vars_train-1);
	for (i = 0; i < num_lines_train; i++) {
		fprintf(stderr, "Eval: %lf\n", eval_tree(mynode, &train_input[i]));
	}
	print_tree(mynode);
	destroy_tree(mynode);

	return 0;
}
