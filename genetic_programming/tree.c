//----------------------------Natural Computing--------------------------------
//----------------Student: Breno Campos Ferreira Guimaraes---------------------

#include "tree.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <limits.h>
#include <math.h>

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

struct node *init_node(uint8_t op, double value, uint8_t height, uint8_t var) {
	struct node *new_node;

	new_node = malloc(sizeof(struct node));

	/*operator node*/
	if (op) {
		new_node->type = OP_TYPE;
		new_node->data.op = op;
	}

	/*variable node*/
	else if (var) {
		new_node->type = VAR_TYPE;
		new_node->data.var = var;
	}

	/*make values the else case to avoid float comparison*/
	else {
		new_node->type = VAL_TYPE;
		new_node->data.value = value;
	}

	new_node->height = height;

	/*leave children initialization up to the tree building function*/
	new_node->left = NULL;
	new_node->right = NULL;

	return new_node;
}

struct node *copy_tree(struct node *node, struct node *stop, struct node *app,
														uint16_t cur_height) {
	struct node *new_node;

	new_node = malloc(sizeof(struct node));

	/*copy over current node's attributes and set new height*/
	new_node->height = cur_height;
	new_node->type = node->type;

	switch (new_node->type) {
		case OP_TYPE: {
			new_node->data.op = node->data.op;
			break;
		}

		case VAR_TYPE: {
			new_node->data.var = node->data.var;
			break;
		}

		case VAL_TYPE: {
			new_node->data.value = node->data.value;
			break;
		}

		default: {
			fprintf(stderr, "Invalid node type when copying!\n");
			break;
		}
	}

	/*check if old node had a left child first*/
	if (node->left != NULL) {
		/*if reached stopping point append other tree*/
		if (node->left == stop) {
			new_node->left = copy_tree(app, NULL, NULL, cur_height+1);
		}
		/*else keep copying recursively*/
		else {
			new_node->left = copy_tree(node->left, stop, app, cur_height+1);
		}
	}

	else {
		new_node->left = NULL;
	}

	/*same behavior for right subtree*/
	if (node->right != NULL) {
		if (node->right == stop) {
			new_node->right = copy_tree(app, NULL, NULL, cur_height+1);
		}
		else {
			new_node->right = copy_tree(node->right, stop, app, cur_height+1);
		}
	}

	else {
		new_node->right = NULL;
	}

	return new_node;
}

struct node *cross_trees(struct node *p1, struct node *p2) {
	struct node *cross1, *cross2, *child;

	/*get crossing nodes for both trees*/
	cross1 = get_random_node(p1, 0);
	cross2 = get_random_node(p2, 0);

	/*copy first tree and append crosspoint 2 to crosspoint 1*/
	child = copy_tree(p1, cross1, cross2, 0);

	return child;
}

void destroy_tree(struct node *node) {
	/*destroy left subtree*/
	if (node->left) {
		destroy_tree(node->left);
	}

	/*destroy right subtree*/
	if (node->right) {
		destroy_tree(node->right);
	}

	/*destroy root*/
	free(node);
}

double eval_tree(struct node *node, double *vars) {
	/*treat simple value/var type cases first*/
	switch(node->type) {
		case VAL_TYPE: {
			return node->data.value;
		}

		case VAR_TYPE: {
			return vars[(node->data.var)-1];
		}

		/*this is terrible practice, but we let op types break into the rest
		of the function to let the function code be a bit more organized (less
		indentation*/
		default: {
			break;
		}
	}

	/*all types need to evaluate argument 1 anyway*/
	double val1 = eval_tree(node->left, vars);

	/*treat op types separately (again, not great practice but...)*/
	switch (node->data.op) {
		case ADD: {
			double val2 = eval_tree(node->right, vars);
			return val1 + val2;
		}

		case SUB: {
			double val2 = eval_tree(node->right, vars);
			return val1 - val2;
		}

		case MUL: {
			double val2 = eval_tree(node->right, vars);
			return val1 * val2;
		}

		case DIV: {
			double val2 = eval_tree(node->right, vars);
			if (val2 != 0.0) {
				return val1/val2;
			}
			/*can't divide by 0, return somewhat large number instead*/
			return val1 * 100.0;
		}

		case LOG: {
			/*return a large negative number for negative logarithms*/
			if (val1 <= 0) {
				return -1000.0;
			}
			return log(val1);
		}

		default: {
			break;
		}
	}

	/*if we got here something went horribly wrong*/
	return -1;
}

struct node *rand_subtree(uint8_t cur_height, uint8_t num_vars) {
	uint16_t prob;

	/*probability decays proportionally to height*/
	prob = 100 * pow(0.70, (double)cur_height);

	/*keep generating children*/
	if ((rand() % 100) <= prob) {
		return build_tree(cur_height, num_vars);
	}

	/*generate variable terminal*/
	if (rand() % 10 < 6) {
		uint8_t var = (rand() % (num_vars-1)) + 1;
		return init_node(0, 0.0, cur_height, var);
	}

	/*generate value terminal*/
	else {
		double value = ((double) rand() / (INT_MAX/2)) - 1.0;
		return init_node(0, value, cur_height, 0);
	}
}

struct node *build_tree(uint8_t cur_height, uint8_t num_vars) {
	struct node *root;

	/*root must be a random operator*/
	uint8_t op = (rand() % 5) + 1;
	root = init_node(op, 0.0, cur_height, 0);

	/*all trees have at least a randomly-generated left child*/
	root->left = rand_subtree(cur_height+1, num_vars);

	/*non-log operators also have a right child*/
	if (op != LOG) {
		root->right = rand_subtree(cur_height+1, num_vars);
	}

	return root;
}

struct node *get_random_node(struct node *node, uint16_t cur_height) {
	struct node *ret = NULL;


	uint16_t self_prob;
	self_prob = 100 * pow(0.75, (double)cur_height);

	/*return self*/
	if ((rand() % 100) >= self_prob) {
		ret = node;
	}

	/*otherwise return one of either children*/
	else if ((rand() % 2) && node->left != NULL) {
		ret = get_random_node(node->left, cur_height+1);
	}
	else if (node->right != NULL) {
		ret = get_random_node(node->right, cur_height+1);
	}

	/*no children were randomly selected, return current node*/
	if (ret == NULL && (cur_height == 1 || cur_height == 0)) {
		ret = node;
	}

	return ret;
}

struct node *mutate_tree(struct node *node, uint16_t num_vars) {
	struct node *mut_point, *new_tree;

	new_tree = copy_tree(node, NULL, NULL, 0);

	/*get mutation point randomly*/
	mut_point = get_random_node(new_tree, 0);

	/*deallocate current children if necessary*/
	if (mut_point->left != NULL) {
		destroy_tree(mut_point->left);
	}
	if (mut_point->right != NULL) {
		destroy_tree(mut_point->right);
	}

	/*randomly generate new children*/
	mut_point->left = rand_subtree(mut_point->height+1, num_vars);
	mut_point->right = rand_subtree(mut_point->height+1, num_vars);

	return new_tree;
}

uint16_t max_height(struct node *node) {
	if (node == NULL) {
		return 0;
	}

	else {
		return 1 + (max_height(node->left) > max_height(node->right) ?
					max_height(node->left) : max_height(node->right));
	}
}

void print_tree(struct node *node, FILE *stream) {
	char ops[5] = { '+', '-', '*', '/', 'l' };

	fprintf(stream, "(");
	if (node->left != NULL) {
		print_tree(node->left, stream);
	}

	switch(node->type) {
		case OP_TYPE: {
			fprintf(stream, " %c[%d] ", ops[(node->data.op)-1], node->height);
			break;
		}

		case VAR_TYPE: {
			fprintf(stream, " x%d[%d] ", node->data.var, node->height);
			break;
		}

		case VAL_TYPE: {
			fprintf(stream, " %.2f[%d] ", node->data.value, node->height);
			break;
		}

		default: {
			fprintf(stream, " ERR ");
			break;
		}
	}

	if (node->right != NULL) {
		print_tree(node->right, stream);
	}
	fprintf(stream, ")");
}
