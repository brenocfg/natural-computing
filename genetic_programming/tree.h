//----------------------------Natural Computing--------------------------------
//----------------Student: Breno Campos Ferreira Guimaraes---------------------

#ifndef TREE_H
#define TREE_H

#include <stdint.h>

/*Domain of possible operators.*/
enum OP_TYPES { ADD = 1, SUB, MUL, DIV, LOG };

/*Nodes can either be operators, scalar values or variables.*/
enum NODE_TYPES { OP_TYPE = 0, VAR_TYPE, VAL_TYPE };

/*Let's save some memory and have mutually exclusive members in an union.
These are:
op    -> which operator the node is (addition, substraction, etc)
var   -> the index of which variable the node refers to (x1, x2, etc)
value -> the constant value the node refers to (real constants such as 0.2)*/
union node_data {
	uint8_t op;
	uint8_t var;
	double value;
};

/*A node in our binary tree contains the following members:
type       -> stores the node type amongst operator/variable/value
height     -> height of the node in its tree
left/right -> pointers to its left/right children
data       -> the semantic data for that node (its value, its operator, etc)*/
struct node {
	uint8_t type;
	uint8_t height;
	struct node *left, *right;

	union node_data data;
};

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
