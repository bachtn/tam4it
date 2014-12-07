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

//void improveWeight (struct vector *inputs, double result);
char *network (int ***charList, int charNum);
float **get_weight ();
void set_weight (float **weight);

#endif
