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
	size_t x;
	size_t y;
}Point;

typedef struct{
	size_t w,h;
	int pixel_average;
	Point origine;
	int **mcase;
}Pixel_Matrix;


Pixel_Matrix** detectTextBlock(SDL_Surface *img);

void showTextBlock(SDL_Surface *screen, Pixel_Matrix **image_matrixs);

#endif
