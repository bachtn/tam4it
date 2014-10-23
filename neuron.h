#ifndef STDLIB_STDIO
#define STDLIB_STDIO

#include <stdlib.h>
#include <math.h>
#include <stdio.h>

#endif

#ifndef NEURO
#define NEURO

struct vector
{
  double *data;
  int size;
};

double neuron (struct vector value, struct vector poids);
double xorNeuro (double input1, double input2, struct vector poid);
void improve (double input1, double input2, double result);
struct vector get_poid ();

#endif
