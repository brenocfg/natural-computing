//----------------------------Natural Computing--------------------------------
//----------------Student: Breno Campos Ferreira Guimaraes---------------------

#pragma once

#include <stdint.h>

struct edge;
struct vertex;
struct graph;

/*Initializes a graph with @num_ver vertices.*/
struct graph *init_graph(uint32_t num_ver);

/*Deallocates all the resources associated with the given graph.*/
void destroy_graph (struct graph *graph);

/*Adds an edge from @v1 to @v2 with weight @w to graph @graph.*/
void add_edge (struct graph *graph, uint32_t v1, uint32_t v2, uint32_t w);

/*Prints the graph to the debugging stream.*/
void print_graph (struct graph *graph);
