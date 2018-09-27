//----------------------------Natural Computing--------------------------------
//----------------Student: Breno Campos Ferreira Guimaraes---------------------

#ifndef GEN_H
#define GEN_H

#include <stdint.h>

/*Generates an initial population of random trees. Returns array of pointers
to all trees generated.*/
struct node **init_pop(uint16_t pop_size, uint16_t num_vars, int seed);

/*Evaluates a given tree/subtree over the variables provided, and returns its
fitness (square root of residual sum of squares).*/
double calc_fitness(struct node *node, double *vars, uint16_t num_vars);

#endif
