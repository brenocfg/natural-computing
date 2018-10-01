//----------------------------Natural Computing--------------------------------
//----------------Student: Breno Campos Ferreira Guimaraes---------------------

#ifndef GEN_H
#define GEN_H

#include <stdint.h>

/*Generates a new population, based on the old populaton and using the
parameters provided.*/
struct node **gen_pop(struct node **cur_pop, uint16_t pop_size, double prob,
						uint16_t num_vars, uint16_t num_points, double *vars,
						uint8_t elit, uint8_t tourn_size, double *fits);

/*Generates an initial population of random trees. Returns array of pointers
to all trees generated.*/
struct node **init_pop(uint16_t pop_size, uint16_t num_vars, int seed);

/*Destroys a population, deallocating all its resources.*/
void destroy_pop(struct node **pop, uint16_t pop_size);

/*Evaluates a given tree/subtree over the variables provided, and returns its
fitness (square root of residual sum of squares).*/
double calc_fitness(struct node *node, double *vars, uint16_t num_vars,
														uint16_t num_points);

/*Prints a given population to output stream @stream. For debugging/logging
purposes.*/
void print_pop(struct node **pop, double *fits, uint16_t pop_size,FILE *stream);

/*Evaluates a given population over the given input, checking the fitness of
all individuals. Returns array of fitness values.*/
double *eval_pop(struct node **pop, uint16_t pop_size, uint16_t num_vars,
						uint16_t num_points, double *vars, uint16_t gen_num);

#endif
