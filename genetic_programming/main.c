#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "tree.h"
#include "gen.h"

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
	if (argc < 8) {
		fprintf(stderr, "Not enough input arguments!\n");
		fprintf(stderr, "Usage: ./gen <train_file> <test_file> <seed> ");
		fprintf(stderr, "<pop_size> <num_gen> <elit_flag> <cross_prob> ");
		fprintf(stderr, "<tourn_size>\n");
		return 0;
	}

	fprintf(stderr, "train = %s, input = %s\n", argv[1], argv[2]);

	uint16_t num_vars_train, num_vars_test;
	uint16_t num_lines_train, num_lines_test;

	double *train_input = read_input(argv[1], &num_vars_train, &num_lines_train);
	double *test_input = read_input(argv[2], &num_vars_test, &num_lines_test);

	int seed = atoi(argv[3]);
	srand(seed);

	uint16_t pop_size = atoi(argv[4]);
	uint16_t num_gen = atoi(argv[5]);
	uint8_t elit_flag = atoi(argv[6]);
	double cross_prob = atof(argv[7]);
	uint8_t tourn_size = atoi(argv[8]);

	fprintf(stdout, "generation,best_fit,avg_fit,worst_fit\n");
	struct node **pop = init_pop(pop_size, num_vars_train, seed);
	double *fits;
	fits=eval_pop(pop,pop_size,num_vars_train,num_lines_train,train_input,1);
	print_pop(pop, fits, pop_size, stderr);

	int i;
	for (i = 0; i < num_gen; i++) {
		pop = gen_pop(pop, pop_size, cross_prob, num_vars_train,num_lines_train,
						train_input, elit_flag, tourn_size, fits);
		free(fits);
		fits = eval_pop(pop, pop_size, num_vars_train, num_lines_train,
													train_input, i+2);
		fprintf(stderr, "\n\n/---------- Generation %d ----------/\n\n", i+2);
		print_pop(pop, fits, pop_size, stderr);
	}
	fprintf(stderr, "\n");

	fprintf(stdout, "/------- TEST DATASET --------/\n");
	free(fits);
	fits = eval_pop(pop, pop_size, num_vars_test, num_lines_test, test_input,
					999);

	destroy_pop(pop, pop_size);
	free(fits);
	free(pop);
	free(train_input);
	free(test_input);

	return 0;
}
