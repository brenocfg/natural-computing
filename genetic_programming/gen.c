//----------------------------Natural Computing--------------------------------
//----------------Student: Breno Campos Ferreira Guimaraes---------------------

#include "tree.h"
#include "gen.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <float.h>
#include <string.h>

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
		fprintf(stream,"\nHeight: %u, Fit: %.8f\n",max_height(pop[i]),fits[i]);
		print_tree(pop[i], stream);
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

int cmpfunc (const void * a, const void * b) {
   return ( *(uint16_t*)a < *(uint16_t*)b );
}

struct node *tournament(struct node **pop,uint16_t pop_size,uint16_t tourn_size,
	 															double *fits) {
	if (pop_size < tourn_size) {
		tourn_size = pop_size;
	}

	uint8_t flags[pop_size+1];
	memset(flags, 0, sizeof(flags));
	flags[pop_size] = 1;

	uint16_t best_index = pop_size;
	double best_fit = DBL_MAX;
	uint16_t indices[tourn_size];
	int i;
	for (i = 0; i < tourn_size; i++) {
		uint16_t index = pop_size;
		while (flags[index]) {
			index = (uint16_t) (rand()%pop_size);
		}
		flags[index] = 1;
		indices[i] = index;
		if (fits[index] < best_fit) {
			best_index = index;
		}
	}

	struct node *ret = pop[best_index];

	qsort(indices, tourn_size, sizeof(uint16_t), cmpfunc);
	for (i = 0; i < tourn_size; i++) {
		struct node *tmp;
		double dtmp;
		tmp = pop[indices[i]];
		pop[indices[i]] = pop[(pop_size-i)-1];
		pop[(pop_size-i)-1] = tmp;

		dtmp = fits[indices[i]];
		fits[indices[i]] = fits[(pop_size-i)-1];
		fits[(pop_size-i)-1] = dtmp;
	}

	return ret;
}

double *eval_pop(struct node **pop, uint16_t pop_size, uint16_t num_vars,
						uint16_t num_points, double *vars, uint16_t gen_num) {
	double *fits;
	double best_fit, avg_fit, worst_fit;

	best_fit = DBL_MAX;
	worst_fit = 0.0;
	avg_fit = 0.0;

	fits = malloc(pop_size*sizeof(double));

	int i;
	for (i = 0; i < pop_size; i++) {
		fits[i] = calc_fitness(pop[i], vars, num_vars, num_points);
		if (fits[i] < best_fit) {
			best_fit = fits[i];
		}
		if (fits[i] > worst_fit) {
			worst_fit = fits[i];
		}
		avg_fit += fits[i];
	}

	avg_fit /= pop_size;

	fprintf(stdout, "%u,%.6f,%.6f,%.6f\n", gen_num,best_fit,avg_fit,worst_fit);

	return fits;
}

struct node **gen_pop(struct node **cur_pop, uint16_t pop_size, double prob,
						uint16_t num_vars, uint16_t num_points, double *vars,
						uint8_t elit, uint8_t tourn_size, double *fits) {
	struct node **new_pop;
	uint16_t npop_size;

	new_pop = malloc(pop_size*sizeof(struct node*));

	uint16_t stop = pop_size/tourn_size;
	for (npop_size = 0; npop_size < stop; npop_size++, pop_size-=tourn_size) {
		struct node *winner = tournament(cur_pop, pop_size, tourn_size, fits);
		new_pop[npop_size] = copy_tree(winner, NULL, NULL, 0);
	}

	destroy_pop(cur_pop, stop*tourn_size);
	free(cur_pop);

	uint8_t iprob = 100 * prob;
	uint16_t ori_size = npop_size;
	for (npop_size = stop; npop_size < stop*tourn_size; npop_size++) {
		struct node *rand1 = new_pop[rand()%ori_size];

		/*mutation*/
		uint16_t rand_val = rand()%100;
		if (rand_val > iprob) {
			struct node *child = mutate_tree(rand1, num_vars);
			double parfit = calc_fitness(rand1, vars, num_vars, num_points);
			double chifit = calc_fitness(child, vars, num_vars, num_points);
			if (max_height(child) > 7) {
				chifit = DBL_MAX;
			}
			if (max_height(rand1) > 7) {
				parfit = DBL_MAX;
			}

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

			if (max_height(child) > 7) {
				chifit = DBL_MAX;
			}
			if (max_height(rand1) > 7) {
				par1fit = DBL_MAX;
			}
			if (max_height(rand2) > 7) {
				par2fit = DBL_MAX;
			}

			/*elitist operator takes best between parent and child*/
			if ((chifit > par1fit) && (chifit > par2fit) && elit == 0) {
				new_pop[npop_size] = child;
			}

			else if ((chifit < par1fit) && (chifit < par2fit)) {
				new_pop[npop_size] = child;
			}
			/*non-elitism always takes child*/
			else {
				struct node *par = (par1fit < par2fit) ? rand1 : rand2;
				new_pop[npop_size] = copy_tree(par, NULL, NULL, 0);
				destroy_tree(child);
			}
		}
	}

	return new_pop;
}
