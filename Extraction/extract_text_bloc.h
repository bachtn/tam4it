#ifndef STDLIB_TDIO
#define STDLIB_STDIO

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#endif

#ifndef EXTRACT_TBLOCK
#define EXRACT_TBLOCK

#define MATRIX_ACCURACY 10
#define SIZE_MATRIX 3

typedef struct{
	int x;
	int y;
}Point;

typedef struct{
	int pixel_average;
	Point origine;
	int **mcase;
}Pixel_Matrix;


void detectTextBlock(SDL_Surface *img);

#endif
