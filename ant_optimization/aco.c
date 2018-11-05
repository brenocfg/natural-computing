//----------------------------Natural Computing--------------------------------
//----------------Student: Breno Campos Ferreira Guimaraes---------------------

#include "aco.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define EPSILON 0.00001

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

		uint32_t i;
		double prob = 0.0;
		for (i = 0; i < graph->vers[cur].num_neigh; i++) {
			struct edge e = graph->vers[cur].neighs[i];
			if (visited[e.id]) {
				continue;
			}
			prob += e.weight * e.pher;
		}

		if (prob > -EPSILON && prob < EPSILON) {
			ant->cost = 0;
			ant->length = 1;
			break;
		}

		double r = ((double)rand() / RAND_MAX);

		uint32_t next = cur;
		uint32_t ncost = 0;
		struct edge *e = NULL;
		for (i = 0; i < graph->vers[cur].num_neigh; i++) {
			e = &graph->vers[cur].neighs[i];
			if (visited[e->id]) {
				continue;
			}

			r -= ((e->weight * e->pher) / prob);

			if (r <= EPSILON) {
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

void reset_pher (struct graph *graph) {
	uint32_t i, j;
	for (i = 0; i < graph->num_v; i++) {
		struct vertex *v = &graph->vers[i];
		for (j = 0; j < v->num_neigh; j++) {
			v->neighs[j].pher = 1.0;
		}
	}
}

void update_pher (struct graph *graph, struct ant *pop, double decay,
															uint32_t best) {
	uint32_t i, j;
	struct ant *a = &pop[best];
	for (j = 0; j < a->length; j++) {
		a->sol[j]->pher += (1 - (1 / a->cost));
	}
	
	for (i = 0; i < graph->num_v; i++) {
		struct vertex *v = &graph->vers[i];
		for (j = 0; j < v->num_neigh; j++) {
			struct edge *e = &v->neighs[j];
			e->pher *= decay;
		}
	}
}

uint32_t aco_longest (struct graph *graph, double decay, uint32_t num_ants,
															uint32_t num_it) {
	struct ant *pop;
	uint32_t best;
	uint32_t best_it, avg, worst_it, best_ind = 0;

	best = 0;
	pop = init_pop(graph, num_ants);

	uint32_t i, j;
	for (i = 0; i < num_it; i++) {
		best_it = 0;
		worst_it = ~0;
		avg = 0;
		for (j = 0; j < num_ants; j++) {
			build_solution(graph, &pop[j]);

			if (pop[j].cost > best) {
				best = pop[j].cost;
			}

			if (pop[j].cost > best_it) {
				best_it = pop[j].cost;
				best_ind = j;
			}

			if (pop[j].cost < worst_it) {
				worst_it = pop[j].cost;
			}

			avg += pop[j].cost;
		}
		avg /= num_ants;
		fprintf(stderr, "%u, %u, %u\n", best_it, avg, worst_it);
		update_pher(graph, pop, decay, best_ind);
	}

	destroy_pop(pop, num_ants);
	reset_pher(graph);

	return best;
}
