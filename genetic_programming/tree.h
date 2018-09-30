//----------------------------Natural Computing--------------------------------
//----------------Student: Breno Campos Ferreira Guimaraes---------------------

#ifndef TREE_H
#define TREE_H

#include <stdint.h>
#include <stdio.h>

/*Opaque declaration of node.*/
struct node;

/*Copies tree @node, up until reaching node @stop, and appending node @app in
its place. Returns new tree.*/
struct node *copy_tree(struct node *node, struct node *stop, struct node *app,
														uint16_t cur_height);

/*prints a tree/subtree to output stream @stream, for debugging/logging
 purposes*/
void print_tree(struct node *node, FILE *stream);

/*evaluates a given tree/subtree with the given array of variable values and
returns the result of the evaluation*/
double eval_tree(struct node *node, double *vars);

/*builds a valid tree from a root node, which is guaranteed to be an operator
plus a random amount of children and (possibly) subchildren*/
struct node *build_tree(uint8_t cur_height, uint8_t num_vars);

/*destroys a tree, recursively deallocating the resources taken by all of its
children, then deallocating itself*/
void destroy_tree(struct node *node);

/*returns a random node amongst the input node itself or one of its
descendants
NOTE: this avoids returning nodes at height 0 (tree roots) as much as possible,
to favor mutation/crossover at lower levels of the tree*/
struct node *get_random_node(struct node *node, uint16_t cur_height);

/*mutates a given tree, picking a random subtree and generating a new random
one to replace it.*/
struct node *mutate_tree(struct node *node, uint16_t num_vars);

/*Performs crossover of the two given trees, returning a tree that is a cross
of random subtrees of the given parents.*/
struct node *cross_trees(struct node *p1, struct node *p2);

/*Returns a tree's max height (the length of the longest path from root to
leaf*/
uint16_t max_height(struct node *node);

/*Generates a new population based on the old one, using the parameters
provided.*/
struct node **gen_pop(struct node **cur_pop, uint16_t pop_size, double prob,
						uint16_t num_vars, uint16_t num_points, double *vars,
						uint8_t elit, uint8_t tourn_size);

#endif /* TREE_H */
