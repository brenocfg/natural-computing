//----------------------------Natural Computing--------------------------------
//----------------Student: Breno Campos Ferreira Guimaraes---------------------

#include <stdlib.h>
#include <stdio.h>

#include "graph.h"

struct graph *init_graph (uint32_t num_ver) {
	struct graph *new_graph;

	new_graph = (struct graph*) malloc(sizeof(struct graph));
	new_graph->num_v = num_ver;
	new_graph->vers = (struct vertex*) malloc(num_ver*sizeof(struct vertex));

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
	free(graph);
}

void add_edge (struct graph *graph, uint32_t v1, uint32_t v2, uint32_t w) {
	graph->vers[v1].num_neigh += 1;

	graph->vers[v1].neighs = realloc(graph->vers[v1].neighs, 
								graph->vers[v1].num_neigh*sizeof(struct edge));
	graph->vers[v1].neighs[graph->vers[v1].num_neigh-1].id = v2;
	graph->vers[v1].neighs[graph->vers[v1].num_neigh-1].weight = w;
	graph->vers[v1].neighs[graph->vers[v1].num_neigh-1].pher = 1;
}	

void print_graph (struct graph *graph) {
	uint32_t i, j;
	for (i = 0; i < graph->num_v; i++) {
		fprintf(stderr, "%u[%u]: ", i, graph->vers[i].num_neigh);
		for (j = 0; j < graph->vers[i].num_neigh; j++) {
			fprintf(stderr, "(%u, %u)\t", graph->vers[i].neighs[j].id,
											graph->vers[i].neighs[j].weight);
		}
		fprintf(stderr, "\n");
	}
}
