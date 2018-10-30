//----------------------------Natural Computing--------------------------------
//----------------Student: Breno Campos Ferreira Guimaraes---------------------

#include "aco.h"

#include <stdlib.h>

struct ant {
	uint32_t cost;
	uint32_t length;
	struct edge **sol;
};

struct ant *init_pop (struct graph *graph, uint32_t num_ants) {
	struct ant *pop;

	pop = (struct ant *) malloc(num_ants * sizeof(struct ant));

	uint32_t i, j;
	for (i = 0; i < num_ants; i++) {
		pop[i].cost = 0;
		pop[i].length = 0;
		pop[i].sol=(struct edge**)malloc(graph->num_v * sizeof(struct edge *));
		for (j = 0; j < graph->num_v; j++) {
			pop[i].sol[j] = NULL;
		}
	}

	return pop;
}

void destroy_pop (struct ant *pop, uint32_t num_ants) {
	uint32_t i;
	for (i = 0; i < num_ants; i++) {
		free(pop[i].sol);
	}
	free(pop);
}

uint32_t aco_longest (struct graph *graph, double decay, uint32_t num_ants,
															uint32_t num_it) {
	struct ant *pop;

	pop = init_pop(graph, num_ants);

	destroy_pop(pop, num_ants);

	return 10;
}
