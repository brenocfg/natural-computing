//----------------------------Natural Computing---------------------------------
//----------------Student: Breno Campos Ferreira Guimaraes----------------------

#pragma once

#include <stdint.h>

#include "graph.h"
#include "ind.h"

/*Initiates a population of @num_inds individuals and returns it.*/
struct ind **init_pop (uint32_t num_inds, struct graph *graph);

/*Prints a population to stderr, for debugging purposes.*/
void print_pop (struct ind **pop, uint32_t num_inds, uint8_t redux_flag);

/*Destroys a population, deallocating all its resources.*/
void destroy_pop (struct ind **pop, uint32_t num_inds);

/*Compares two individuals based on fitness.*/
int cmpfunc (const void * a, const void * b);

/*Generates a new population based on a previous one. Essentially, moves the
evolutionary algorithm one iteration forward.*/
struct ind **gen_pop (struct ind **cur_pop, uint32_t num_inds, uint32_t k,
														struct graph *graph);

/*Runs the genetic algorithm for the given amount of generations and returns
best solution found.*/
uint32_t rwa (struct ind **cur_pop, uint32_t num_inds, uint32_t num_gen,
											uint32_t k, struct graph *graph);
