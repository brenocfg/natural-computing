//----------------------------Natural Computing--------------------------------
//----------------Student: Breno Campos Ferreira Guimaraes---------------------

#include "aco.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

void build_solution (struct graph *graph, struct ant *ant) {
	uint8_t visited[graph->num_v];

	memset(visited, 0, sizeof(visited));
	visited[0] = 1;
	ant->length = 0;
	ant->cost = 0;

	uint32_t cur = 0;
	while (1) {
		if (cur == (graph->num_v - 1)) {
			break;
		}

		uint32_t i, prob = 0;
		for (i = 0; i < graph->vers[cur].num_neigh; i++) {
			struct edge e = graph->vers[cur].neighs[i];
			if (visited[e.id]) {
				continue;
			}
			prob += e.weight * e.pher;
		}

		if (prob == 0) {
			ant->cost = 0;
			ant->length = 1;
			break;
		}

		int32_t r = rand() % prob;

		uint32_t next = cur;
		uint32_t ncost = 0;
		struct edge *e = NULL;
		for (i = 0; i < graph->vers[cur].num_neigh; i++) {
			e = &graph->vers[cur].neighs[i];
			if (visited[e->id]) {
				continue;
			}

			r -= (e->weight * e->pher);

			if (r <= 0) {
				next = e->id;
				ncost = e->weight;
				break;
			}
		}

		visited[next] = 1;
		cur = next;
		ant->sol[ant->length] = e;
		ant->length += 1;
		ant->cost += ncost;
	}
}

void update_pher (struct graph *graph, struct ant *pop, uint32_t num_ants,
															double decay) {
	uint32_t i, j;
	for (i = 0; i < num_ants; i++) {
		struct ant *a = &pop[i];
		for (j = 0; j < a->length; j++) {
			struct edge *e = a->sol[j];
			e->pher += (a->cost / a->length);
		}
	}
	
	for (i = 0; i < graph->num_v; i++) {
		struct vertex *v = &graph->vers[i];
		for (j = 0; j < v->num_neigh; j++) {
			struct edge *e = &v->neighs[j];
			if (e->pher == 1) {
				continue;
			} 
			e->pher *= decay;
		}
	}
}

uint32_t aco_longest (struct graph *graph, double decay, uint32_t num_ants,
															uint32_t num_it) {
	struct ant *pop;
	uint32_t best;

	best = 0;
	pop = init_pop(graph, num_ants);

	uint32_t i, j;
	for (i = 0; i < num_it; i++) {
		for (j = 0; j < num_ants; j++) {
			build_solution(graph, &pop[j]);

			if (pop[j].cost > best) {
				best = pop[j].cost;
			}
		}
		update_pher(graph, pop, num_ants, decay);
	}

	destroy_pop(pop, num_ants);

	return best;
}
