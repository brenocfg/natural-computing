//----------------------------Natural Computing--------------------------------
//----------------Student: Breno Campos Ferreira Guimaraes---------------------

#pragma once

#include <stdint.h>

/*Struct that represents an edge in the graph. Edges contain the ID of the
vertex they point to, their weight, and the amount of pheromones they contain*/
struct edge {
	uint32_t id;
	uint32_t weight;
	double pher;
};

/*Struct that represents a vertex in the graph. Vertices simply have an ID and
an array of edges that represents their neighbourhood in the graph.*/
struct vertex {
	uint32_t num_neigh;
	struct edge *neighs;
};

/*Struct that represents a graph. Graphs store the number of vertices they
contain, and an array of vertices storing the data for each vertex.*/
struct graph {
	uint32_t num_v;
	struct vertex *vers;
};

/*Initializes a graph with @num_ver vertices.*/
struct graph *init_graph(uint32_t num_ver);

/*Deallocates all the resources associated with the given graph.*/
void destroy_graph (struct graph *graph);

/*Adds an edge from @v1 to @v2 with weight @w to graph @graph.*/
void add_edge (struct graph *graph, uint32_t v1, uint32_t v2, uint32_t w);

/*Prints the graph to the debugging stream.*/
void print_graph (struct graph *graph);
