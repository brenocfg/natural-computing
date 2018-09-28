//----------------------------Natural Computing--------------------------------
//----------------Student: Breno Campos Ferreira Guimaraes---------------------

#include "tree.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

struct node **init_pop(uint16_t pop_size, uint16_t num_vars, int seed) {
	struct node **pop;

	pop = malloc(pop_size * sizeof(struct node*));

	srand(seed);

	int i;
	for (i = 0; i < pop_size; i++) {
		pop[i] = build_tree(0, num_vars);
	}

	return pop;
}

double calc_fitness(struct node *node, double *vars, uint16_t num_vars,
														uint16_t num_points) {
	double fit = 0.0, norm = 0.0, avg_out = 0.0;

	int i;
	for (i = 0; i < num_points; i++) {
		double eval = eval_tree(node, (vars+(i*num_vars)));
		double out = vars[i*num_vars+(num_vars-1)];
		fit += (eval-out)*(eval-out);
		avg_out += out;
	}

	avg_out /= num_points;

	for (i = 0; i < num_points; i++) {
		double out = vars[i*num_vars+(num_vars-1)];
		norm += (out-avg_out)*(out-avg_out);
	}

	return (fit/norm);
}

int main(int argc, char *argv[]) {
	double vars[] = {1.0, 1.0, 2.0, 2.0, 2.0, 4.0, 3.0, 3.0, 6.0, 4.0, 5.0, 9.0};
	uint16_t num_vars = 3;
	
	int seed = atoi(argv[1]);
	srand(seed);

	if (argc < 2) {
		fprintf(stderr, "forgot seed\n");
		return 0;
	}

	struct node *p1, *p2;

	p1 = build_tree(0, 2);
	p2 = build_tree(0, 2);
	fprintf(stderr, "p1: ");
	print_tree(p1);
	fprintf(stderr, "\np2: ");
	print_tree(p2);
	fprintf(stderr, "\n\n");

	struct node *p3 = cross_trees(p1, p2);
	fprintf(stderr, "child: ");
	print_tree(p3);
	fprintf(stderr, "\n");

	destroy_tree(p1);
	destroy_tree(p2);
	destroy_tree(p3);

	return 0;
}
