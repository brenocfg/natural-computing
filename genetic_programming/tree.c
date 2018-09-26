//----------------------------Natural Computing--------------------------------
//----------------Student: Breno Campos Ferreira Guimaraes---------------------

#include "tree.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <limits.h>
#include <math.h>

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

void destroy_tree(struct node *node) {
	if (node->left != NULL) {
		destroy_tree(node->left);
	}

	if (node->right != NULL) {
		destroy_tree(node->right);
	}

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

	prob = 100 * pow(0.85, (double)cur_height);

	if ((rand() % 100) < prob) {
		return build_tree(cur_height, num_vars);
	}

	if (rand() % 2) {
		uint8_t var = (rand() % num_vars) + 1;
		return init_node(0, 0.0, cur_height, var);
	}

	else {
		double value = ((double) rand() / (INT_MAX/2)) - 1.0;
		return init_node(0, value, cur_height, 0);
	}
}

struct node *build_tree(uint8_t cur_height, uint8_t num_vars) {
	struct node *root;

	uint8_t op = (rand() % 5) + 1;

	root = init_node(op, 0.0, cur_height, 0);

	root->left = rand_subtree(cur_height+1, num_vars);

	if (op != LOG) {
		root->right = rand_subtree(cur_height+1, num_vars);
	}

	return root;
}

void print_tree(struct node *node) {
	char ops[5] = { '+', '-', '*', '/', 'l' };

	fprintf(stderr, "(");
	if (node->left != NULL) {
		print_tree(node->left);
	}

	switch(node->type) {
		case OP_TYPE: {
			fprintf(stderr, " %c[%d] ", ops[(node->data.op)-1], node->height);
			break;
		}

		case VAR_TYPE: {
			fprintf(stderr, " x%d[%d] ", node->data.var, node->height);
			break;
		}

		case VAL_TYPE: {
			fprintf(stderr, " %f[%d] ", node->data.value, node->height);
			break;
		}

		default: {
			fprintf(stderr, " ERR ");
			break;
		}
	}

	if (node->right != NULL) {
		print_tree(node->right);
	}
	fprintf(stderr, ")");
}
