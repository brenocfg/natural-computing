//----------------------------Natural Computing--------------------------------
//----------------Student: Breno Campos Ferreira Guimaraes---------------------

#pragma once

#include <stdint.h>

/*Struct that represents an edge in the graph. Edges contain only ID of the
vertex they lead to*/
struct edge {
	uint32_t id;
};

/*Struct that represents a vertex in the graph. Vertices simply have an ID and
an array of edges that represents their neighbourhood in the graph.*/
struct vertex {
	uint32_t num_neigh;
	struct edge *neighs;
};

/*Struct that represents a graph. Graphs store the number of vertices they
contain, and an array of vertices storing the data for each vertex.
They also store an array of vertex pairs, which represents the lightpaths
that must be implemented for a valid solution.*/
struct graph {
	uint32_t num_v;
	struct vertex *vers;
	uint32_t num_r;
	uint32_t *reqs;
};

/*Initializes a graph with @num_ver vertices.*/
struct graph *init_graph(uint32_t num_ver, uint32_t num_req);

/*Deallocates all the resources associated with the given graph.*/
void destroy_graph (struct graph *graph);

/*Adds an edge from @v1 to @v2 to the graph.*/
void add_edge (struct graph *graph, uint32_t v1, uint32_t v2);

/*Prints the graph to the debugging stream.*/
void print_graph (struct graph *graph);

/*Adds a lightpath request between vertices v1 and v2 to the graph*/
void add_request(struct graph *graph, uint32_t v1, uint32_t v2);
