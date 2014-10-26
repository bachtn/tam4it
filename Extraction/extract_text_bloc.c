#include "extract_text_bloc.h"

#define MATRIX_ACCURACY 10
#define SIZE_MATRIX 3

typedef struct{
	int x;
	int y;
}Point;

typedef struct{
	int pixel_average;
	Point origine;
}Pixel_Matrix;

void detectTextBlock(SDL_Surface* img)
{
	size_t wx_matrix = img->w/MATRIX_ACCURACY;
	size_t hy_matrix = img->h/MARIX_ACCURACY;
	
	size_t i,j;

	Pixel_Matrix **image_matrix = malloc((MATRIX_ACCURACY + 1) * sizeof (Pixel_Matrix*));
	for (i = 0; i < dim; i++)
		image_matrix[i] = malloc((MATRIX_ACCURACY + 1) * sizeof(Pixel_Matrix));

	for (i = 0; i < MATRIX_ACCURACY + 1; i++){
		for(j = 0; j < MATRIX_ACCURACY + 1; j++){
			image_matrix[i][j]->origine.x = wx_matrix * i;
			image_matrix[i][j]->origine.y = hy_matrix * j;
		}
	}	
	
}
