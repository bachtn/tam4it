#ifndef STDLIB_STDIO
#define STDLIB_STDIO

#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#endif

#ifndef NEURO
#define NEURO

#include <math.h>

int neuron (int values[256], float weight[1][257], int idNeur);
//double xorNeuro (double input1, double input2, struct vector *weight);
//void improveWeight (struct vector *inputs, double result);
float **get_weight ();
void set_weight (float **weight);

#endif
