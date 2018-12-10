//----------------------------Natural Computing--------------------------------
//----------------Student: Breno Campos Ferreira Guimaraes---------------------

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "ind.h"

struct path {
	uint32_t ori;
	uint32_t dest;
	uint16_t length;
	uint32_t color;
	struct edge **path;
};

struct ind {
	uint32_t num_paths;
	struct path *paths;
};

void build_path (struct path *path, struct graph *graph) {
	uint32_t ori, dest;
	uint8_t visited[graph->num_v];

	ori = path->ori;
	dest = path->dest;

	memset(visited, 0, sizeof(visited));
	visited[ori] = 1;

	uint32_t cur = ori;
	while (1) {
		if (cur == dest) {
			break;
		}

		struct vertex *cur_v = &graph->vers[cur];
		struct edge *next_edge = &cur_v->neighs[rand()%(cur_v->num_neigh)];

		if (visited[next_edge->id]) {
			path->length = 0;
			return;
		}

		path->path[path->length] = next_edge;
		path->length += 1;
		visited[next_edge->id] = 1;
		cur = next_edge->id;
	}
}

void color_ind (struct ind *ind) {
	uint32_t num_paths = ind->num_paths;

	uint8_t conf_mat[num_paths][num_paths];
	memset(conf_mat, 0, sizeof(conf_mat));

	uint32_t i, j, k, l;
	for (i = 0; i < num_paths; i++) {
		struct path *p = &ind->paths[i];
		p->color = 0;
		for (j = i+1; j < num_paths; j++) {
			struct path *p2 = &ind->paths[j];
			for (k = 0; k < p->length; k++) {
				struct edge *e = p->path[k];
				for (l = 0; l < p2->length; l++) {
					struct edge *e2 = p2->path[l];
					if (e == e2) {
						conf_mat[i][j] = 1;
						conf_mat[j][i] = 1;
					}
				}
			}
		}
	}

	uint8_t ava_col[num_paths];
	for (i = 0; i < num_paths; i++) {
		memset(ava_col, 1, sizeof(ava_col));
		ava_col[0] = 0;
		struct path *p = &ind->paths[i];

		for (j = 0; j < num_paths; j++) {
			if (j == i) {
				continue;
			}

			struct path *p2 = &ind->paths[j];
			if (conf_mat[i][j]) {
				ava_col[p2->color] = 0;
			}
		}

		uint32_t new_col = num_paths;
		for (j = 0; j < num_paths; j++) {
			if (ava_col[j]) {
				new_col = j;
				break;
			}
		}

		p->color = new_col;
	}
}

struct ind *init_ind (struct graph *graph) {
	struct ind *newind;
	uint32_t i;
	
	newind = (struct ind*) malloc(sizeof(struct ind));

	uint32_t num_paths = graph->num_r;

	newind->num_paths = num_paths;

	newind->paths = (struct path *) malloc(num_paths*sizeof(struct path));
	for (i = 0; i < num_paths; i++) {
		struct path *p = &newind->paths[i];
		p->length = 0;
		p->path=(struct edge**) malloc(graph->num_v*sizeof(struct edge*));

		p->ori = graph->reqs[2*i];
		p->dest = graph->reqs[2*i+1];
		while(p->length == 0) {
			build_path(p, graph);
		}
	}

	color_ind(newind);

	return newind;
}

void print_ind (struct ind *ind) {
	uint32_t i;
	int32_t j;

	for (i = 0; i < ind->num_paths; i++) {
		struct path *p = &ind->paths[i];
		fprintf(stderr, "Path[%d] - [%d -> %d]: {", i, p->ori, p->dest);
		for (j = 0; j < (int)(p->length)-1; j++) {
			fprintf(stderr, "%d, ", p->path[j]->id);
		}
		fprintf(stderr, "%d} Color: %d\n", p->path[j]->id, p->color);
	}	
}
