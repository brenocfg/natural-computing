//----------------------------Natural Computing--------------------------------
//----------------Student: Breno Campos Ferreira Guimaraes---------------------

#pragma once

#include <stdint.h>

#include "graph.h"

/*Finds a viable solution for the longest simple path in the graph @graph,
by using an Ant Colony Optimization metaheuristic. Parameters:
 @decay - controls the rate of pheromone decay
 @num_ants - number of ants per iteration
 @num_it - total number of iterations */
uint32_t aco_longest (struct graph *graph, double decay, uint32_t num_ants,
															uint32_t num_it);
