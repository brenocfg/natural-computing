//----------------------------Natural Computing--------------------------------
//----------------Student: Breno Campos Ferreira Guimaraes---------------------

#ifndef TREE_H
#define TREE_H

#include <stdint.h>

/*Opaque declaration of node.*/
struct node;

/*prints a tree/subtree, for debugging purposes*/
void print_tree(struct node *node);

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
void mutate_tree(struct node *node, uint16_t num_vars);

/*Performs crossover of the two given trees, returning a tree that is a cross
of random subtrees of the given parents.*/
struct node *cross_trees(struct node *p1, struct node *p2);

#endif /* TREE_H */
