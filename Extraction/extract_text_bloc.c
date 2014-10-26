#include "extract_text_bloc.h"
#include "pixel_operations.h"

static void initPixelMatrix(Pixel_Matrix **image_matrix, size_t w, size_t h)
{
	size_t i,j,k,x,y;

	image_matrix = malloc((MATRIX_ACCURACY + 1) * sizeof(Pixel_Matrix*));
	for (i = 0; i < SIZE_MATRIX; i++)
		image_matrix[i] = malloc((MATRIX_ACCURACY + 1) * sizeof(Pixel_Matrix));

	for (i = 0; i < MATRIX_ACCURACY + 1; i++){
		for(j = 0; j < MATRIX_ACCURACY + 1; j++){

			image_matrix[i][j].pixel_average = -1;

			image_matrix[i][j].origine.x = w * i;
			image_matrix[i][j].origine.y = h * j;

			image_matrix[i][j].mcase = malloc(SIZE_MATRIX * sizeof(int*));
			for(k = 0; k < SIZE_MATRIX; k++)
				image_matrix[i][j].mcase[k]= malloc(SIZE_MATRIX * sizeof(int));

			for(x = 0; x < SIZE_MATRIX; x++){
				for(y=0; y < SIZE_MATRIX; y++){
					image_matrix[i][j].mcase[x][y] = -1;
				}
			}

		}
	}
}

static void detectBlock(SDL_Surface *img, Pixel_Matrix image_matrix, size_t w, size_t h)
{
	size_t i,j,x,y;

	double average = 0;

	int pxcount = 0;

	Uint32 px;
	Uint8 r,g,b;

	for(i = image_matrix.origine.x; i < w; i++){
		for(j = image_matrix.origine.y; j < h; j++){
			px = getpixel(img, i, j);
			SDL_GetRGB(px, img->format, &r, &g, &b);

			if(r+g+b == 0)
				average++;	
		}
	}

	average /= (w*h);

	for( x = 0; x < SIZE_MATRIX; x++){
		for( y = 0; y < SIZE_MATRIX; y++){
			for( i = x * (w / 3); i < x + x * (w / 3); i++){
				for( j = y * (y / 3); j < y + y * (h/3); j++){
					px = getpixel(img, i, j);
					SDL_GetRGB(px, img->format, &r, &g, &b);
					if(r+g+b == 0)
						pxcount ++;
				}
			}
			if ((double)pxcount >= average)
			       	image_matrix.mcase[x][y] = 1;
			else
				image_matrix.mcase[x][y] = 0;
		}
	}

}

void detectTextBlock(SDL_Surface *img)
{
	size_t wx_matrix = img->w/MATRIX_ACCURACY;
	size_t hy_matrix = img->h/MATRIX_ACCURACY;
	
	size_t i,j;

	Pixel_Matrix **image_matrix = NULL;
	initPixelMatrix(image_matrix, wx_matrix, hy_matrix);
	
	for(i = 0; i <= MATRIX_ACCURACY; i++){
		for(j=0; j <= MATRIX_ACCURACY; i++){
			detectBlock(img, image_matrix[i][j], wx_matrix, hy_matrix);
		}
	}
}

void showTextBlock(SDL_Surface *screen, Pixel_Matrix **image_matrix)
{
	//FIX ME

}
