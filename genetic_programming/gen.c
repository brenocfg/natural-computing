//----------------------------Natural Computing--------------------------------
//----------------Student: Breno Campos Ferreira Guimaraes---------------------

#include "tree.h"
#include "gen.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <float.h>

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

void print_pop(struct node **pop, double *fits, uint16_t pop_size,
																FILE *stream) {
	uint16_t i;
	for (i = 0; i < pop_size; i++) {
		fprintf(stream, "\nHeight: %u, Fit: %.8f\n", max_height(pop[i]), fits[i]);
		fprintf(stream, "%p\n", pop[i]);
		//print_tree(pop[i], stream);
	}
}

void destroy_pop(struct node **pop, uint16_t pop_size) {
	uint16_t i;
	for (i = 0; i < pop_size; i++) {
		if (pop[i]) {
			destroy_tree(pop[i]);
		}
	}
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

uint16_t tournament(struct node **pop, uint16_t pop_size, uint16_t tourn_size,
					double *fits) {
	if (pop_size < tourn_size) {
		tourn_size = pop_size;
	}

	uint16_t best_index = pop_size+1;
	double best_fit = DBL_MAX;
	int i, index;
	for (i = 0; i < tourn_size; i++) {
		index = rand()%pop_size;
		if (fits[index] < best_fit) {
			best_index = index;
		}
	}

	return best_index;
}

double *eval_pop(struct node **pop, uint16_t pop_size, uint16_t num_vars,
										uint16_t num_points, double *vars) {
	double *fits;

	fits = malloc(pop_size*sizeof(double));

	int i;
	for (i = 0; i < pop_size; i++) {
		fits[i] = calc_fitness(pop[i], vars, num_vars, num_points);
	}

	return fits;
}

struct node **gen_pop(struct node **cur_pop, uint16_t pop_size, double prob,
						uint16_t num_vars, uint16_t num_points, double *vars,
						uint8_t elit, uint8_t tourn_size) {
	struct node **new_pop;
	uint16_t npop_size;

	new_pop = malloc(pop_size*sizeof(struct node*));

	double *fits = eval_pop(cur_pop, pop_size, num_vars, num_points, vars);

	uint16_t stop = pop_size/tourn_size;
	for (npop_size = 0; npop_size < stop; npop_size++, pop_size--) {
		uint16_t winner_index = tournament(cur_pop, pop_size, tourn_size, fits);
		new_pop[npop_size] = cur_pop[winner_index];
		cur_pop[winner_index] = cur_pop[pop_size-1];
		cur_pop[pop_size-1] = NULL;
	}

	destroy_pop(cur_pop, stop*tourn_size);
	free(cur_pop);

	uint8_t iprob = 100 * prob;
	uint16_t ori_size = npop_size;
	for (npop_size = stop; npop_size < stop*tourn_size; npop_size++) {
		struct node *rand1 = new_pop[rand()%ori_size];

		/*mutation*/
		if (rand()%100 > iprob) {
			struct node *child = mutate_tree(rand1, num_vars);
			double parfit = calc_fitness(rand1, vars, num_vars, num_points);
			double chifit = calc_fitness(child, vars, num_vars, num_points);
			parfit += pow(1.5, max_height(rand1));
			chifit += pow(1.5, max_height(child));

			/*elitist operator takes best between parent and child*/
			if (parfit < chifit && elit) {
				new_pop[npop_size] = copy_tree(rand1, NULL, NULL, 0);
				destroy_tree(child);
			}
			/*non-elitism always takes child*/
			else {
				new_pop[npop_size] = child;
			}
		}

		/*crossover*/
		else {
			struct node *rand2 = rand1;
			while (rand2 == rand1) {
				rand2 = new_pop[rand()%ori_size];
			}

			struct node *child = cross_trees(rand1, rand2);
			double par1fit = calc_fitness(rand1, vars, num_vars, num_points);
			double par2fit = calc_fitness(rand2, vars, num_vars, num_points);
			double chifit = calc_fitness(child, vars, num_vars, num_points);
			par1fit += pow(1.5, max_height(rand1));
			par2fit += pow(1.5, max_height(rand2));
			chifit += pow(1.5, max_height(child));

			/*elitist operator takes best between parent and child*/
			if (chifit > par1fit && chifit > par2fit && !elit) {
				struct node *par = (par1fit < par2fit) ? rand1 : rand2;
				new_pop[npop_size] = copy_tree(par, NULL, NULL, 0);
				destroy_tree(child);
			}
			/*non-elitism always takes child*/
			else {
				new_pop[npop_size] = child;
			}
		}
	}

	free(fits);

	return new_pop;
}

int main(int argc, char *argv[]) {
	double vars[] = {1.0, 1.0, 2.0, 2.0, 2.0, 4.0, 3.0, 3.0, 6.0, 4.0, 5.0, 9.0};
	uint16_t num_vars = 3;

	int seed = atoi(argv[1]);
	srand(seed);
	int pop_size = atoi(argv[2]);
	int num_gen = atoi(argv[3]);

	if (argc < 4) {
		fprintf(stderr, "forgot seed & pop_size & gen_num\n");
		return 0;
	}

	struct node **pop = init_pop(pop_size, 2, seed);
	double *fits = eval_pop(pop, pop_size, num_vars, 4, vars);
	print_pop(pop, fits, pop_size, stderr);

	int i;
	for (i = 0; i < num_gen; i++) {
		free(fits);
		pop = gen_pop(pop, pop_size, 0.9, num_vars, 4, vars, 1, 2);
		fits = eval_pop(pop, pop_size, num_vars, 4, vars);
		fprintf(stderr, "\n\n/---------- Generation %d ----------/\n\n", i+2);
		print_pop(pop, fits, pop_size, stderr);
	}
	fprintf(stderr, "\n");

	destroy_pop(pop, pop_size);
	free(fits);
	free(pop);

	return 0;
}
