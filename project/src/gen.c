//----------------------------Natural Computing---------------------------------
//----------------Student: Breno Campos Ferreira Guimaraes----------------------

#include "gen.h"

#include <stdlib.h>
#include <stdio.h>

struct ind **init_pop (uint32_t num_inds, struct graph *graph) {
	struct ind **pop;

	pop = (struct ind **) malloc(num_inds * sizeof(struct ind *));

	uint32_t i;
	for (i = 0; i < num_inds; i++) {
		pop[i] = init_ind(graph);
	}

	return pop;
}

struct ind *tournament (struct ind **pop, uint32_t num, uint32_t k) {
	uint32_t index = num+1, rnd, i;

	for (i = 0; i < k; i++) {
		rnd = rand() % num;
		if (rnd < index) {
			index = rnd;
		}
	}

	return pop[index];
}

struct ind **gen_pop (struct ind **cur_pop, uint32_t num_inds, uint32_t k,
														struct graph *graph) {
	struct ind **new_pop;
	uint32_t npop_size;

	new_pop = (struct ind **) malloc(num_inds * sizeof(struct ind *));

	qsort(cur_pop, num_inds, sizeof(struct ind*), &cmpfunc);

	for (npop_size = 0; npop_size < num_inds; npop_size++) {
		struct ind *i1 = tournament(cur_pop, num_inds, k);
		if (rand() % 100 < 80) {
			struct ind *i2 = tournament(cur_pop, num_inds, k);
			while (i1 == i2) {
				i2 = tournament(cur_pop, num_inds, k);
			}
			new_pop[npop_size] = cross_inds(i1, i2, graph);
		}
		else {
			new_pop[npop_size] = mutate_ind(i1, 8, graph);
		}
	}

	destroy_pop(cur_pop, num_inds);

	return new_pop;
}

uint32_t rwa (struct ind **cur_pop, uint32_t num_inds, uint32_t num_gen,
										uint32_t k, struct graph *graph) {
	uint32_t i, j, ret;

	ret = ~0;

	for (i = 0; i < num_inds; i++) {
		if (get_fit(cur_pop[i]) < ret) {
			ret = get_fit(cur_pop[i]);
		}
	}

	for (i = 0; i < num_gen; i++) {
		cur_pop = gen_pop(cur_pop, num_inds, k, graph);
		for (j = 0; j < num_inds; j++) {
			if (get_fit(cur_pop[j]) < ret) {
				ret = get_fit(cur_pop[j]);
			}
		}
		fprintf(stderr, "---------- GENERATION %d ------------\n", i+2);
		print_pop(cur_pop, num_inds, 1);
	}

	destroy_pop(cur_pop, num_inds);

	return ret;
}

void destroy_pop (struct ind **pop, uint32_t num_inds) {
	uint32_t i;
	for (i = 0; i < num_inds; i++) {
		destroy_ind(pop[i]);
	}
	free(pop);
}

void print_pop (struct ind **pop, uint32_t num_inds, uint8_t redux_flag) {
	uint32_t i;

	fprintf(stderr, "--------- Population BEGIN ----------\n");
	for (i = 0; i < num_inds; i++) {
		fprintf(stderr, "-------- Individual NUMBER %d --------\n", i+1);
		print_ind(pop[i], redux_flag);
		fprintf(stderr, "-------------- END ----------------\n");
	}
	fprintf(stderr, "--------- Population END -----------\n");
}
