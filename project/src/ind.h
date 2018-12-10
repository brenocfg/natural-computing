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
void print_ind (struct ind *ind);
