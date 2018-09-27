//----------------------------Natural Computing--------------------------------
//----------------Student: Breno Campos Ferreira Guimaraes---------------------

#ifndef TREE_H
#define TREE_H

#include <stdint.h>

/*initializes a node and returns a pointer to the newly allocated node*/
struct node *init_node(uint8_t op, double value, uint8_t height, uint8_t var);

/*prints a tree/subtree, for debugging purposes*/
void print_tree(struct node *node);

/*evaluates a given tree/subtree with the given array of variable values and
returns the result of the evaluation*/
double eval_tree(struct node *node, double *vars);

/*randomly generates a subtree, either finishing at the current height or
recursively generating more levels in the tree*/
struct node *rand_subtree(uint8_t cur_height, uint8_t num_vars);

/*builds a valid tree from a root node, which is guaranteed to be an operator
plus a random amount of children and (possibly) subchildren*/
struct node *build_tree(uint8_t cur_height, uint8_t num_vars);

/*destroys a tree, recursively deallocating the resources taken by all of its
children, then deallocating itself*/
void destroy_tree(struct node *node);

#endif /* TREE_H */
