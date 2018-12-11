//----------------------------Natural Computing---------------------------------
//----------------Student: Breno Campos Ferreira Guimaraes----------------------

#pragma once

#include <stdint.h>

#include "graph.h"

struct ind;

/*Initializes an individual of size proportinal to the graph provided as
parameter.*/
struct ind *init_ind (struct graph *graph);

/*Prints an individual to the standard error output.*/
void print_ind (struct ind *ind, uint8_t redux_flag);

/*Destroys an individual, deallocating all its resources.*/
void destroy_ind (struct ind *ind);

/*Mutates an individual in-place, changing a portion of their paths.*/
struct ind *mutate_ind (struct ind *ind, uint32_t perc, struct graph *graph);

/*Copies an individual and returns the copy.*/
struct ind *copy_ind (struct ind *ind, struct graph *graph);

/*Crosses two individuals to create a mixed child, which is returned.*/
struct ind *cross_inds (struct ind *i1, struct ind *i2, struct graph *graph);

/*Returns an individual's fitness.*/
uint32_t get_fit (struct ind *ind);
