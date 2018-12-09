//----------------------------Natural Computing--------------------------------
//----------------Student: Breno Campos Ferreira Guimaraes---------------------

#include <stdlib.h>
#include <stdio.h>

#include "graph.h"

struct graph *init_graph (uint32_t num_ver, uint32_t num_req) {
	struct graph *new_graph;

	new_graph = (struct graph*) malloc(sizeof(struct graph));

	new_graph->num_v = num_ver;
	new_graph->vers = (struct vertex*) malloc(num_ver*sizeof(struct vertex));

	new_graph->num_r = 0;
	new_graph->reqs = (uint32_t *) malloc(2*num_req*sizeof(uint32_t));

	uint32_t i;
	for (i = 0; i < num_ver; i++) {
		new_graph->vers[i].num_neigh = 0;
		new_graph->vers[i].neighs = NULL;
	}

	return new_graph;
}

void destroy_graph (struct graph *graph) {
	uint32_t i;
	for (i = 0; i < graph->num_v; i++) {
		free(graph->vers[i].neighs);
	}

	free(graph->vers);
	free(graph->reqs);
	free(graph);
}

void add_edge (struct graph *graph, uint32_t v1, uint32_t v2) {
	graph->vers[v1].num_neigh += 1;

	graph->vers[v1].neighs = realloc(graph->vers[v1].neighs,
								graph->vers[v1].num_neigh*sizeof(struct edge));

	graph->vers[v1].neighs[graph->vers[v1].num_neigh-1].id = v2;
}

void add_request (struct graph *graph, uint32_t v1, uint32_t v2) {
	graph->reqs[2*graph->num_r] = v1;
	graph->reqs[(2*graph->num_r)+1] = v2;
	graph->num_r += 1;
}

void print_graph (struct graph *graph) {
	uint32_t i, j;
	for (i = 0; i < graph->num_v; i++) {
		fprintf(stderr, "%u[%u]: ", i, graph->vers[i].num_neigh);
		for (j = 0; j < graph->vers[i].num_neigh; j++) {
			fprintf(stderr, "(%u)\t", graph->vers[i].neighs[j].id);
		}
		fprintf(stderr, "\n");
	}

	fprintf(stderr, "Reqs: ");
	for (i = 0; i < graph->num_r; i++) {
		fprintf(stderr, "[%d -> %d]\t", graph->reqs[2*i], graph->reqs[2*i+1]);
	}
	fprintf(stderr, "\n");
}
