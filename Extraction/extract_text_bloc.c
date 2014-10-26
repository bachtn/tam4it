#include "extract_text_bloc.h"
#include "../Pre-traitement/pixel_operations.h"

Pixel_Matrix** initPixelMatrix(size_t w, size_t h)
{
	Pixel_Matrix **matrixs= NULL;

	matrixs = malloc(MATRIX_ACCURACY * sizeof(Pixel_Matrix *));
	for(size_t i = 0; i < w; i++){
		matrixs[i] = malloc(MATRIX_ACCURACY
			       	* sizeof(Pixel_Matrix *));

	for(size_t i = 0; i < w; i++){
		for(size_t j = 0; i < h; j++){
			matrixs[i][j] = malloc(w * sizeof(int*));
			for (size_t x = 0; x < w; x++){
				matrixs[i][j].mcase[x] = malloc(w * sizeof(int));

				matrixs[i][j].w = w;
				matrixs[i][j].h = h;
				matrixs[i][j].pixel_average = -1;

				matrixs[i][j].origine.x = i *w;
				matrixs[i][j].origine.y = j *h;
			}

			for(size_t x = 0; x < w; x++){
				for(size_t y = 0; y < h; y++){
					matrixs[i][j].mcase[x][y] = -1;
				}
			}
		}
	}

	return matrixs;
}

static void detectBlock(SDL_Surface *img, Pixel_Matrix *matrix, size_t i, size_t j)
{
	Uint32 px;
	int average = 0;

	for(size_t x = 0; x < matrix[0][0]->w; x++){
		for(size_t y = 0; y < matrix[0][0]->h; y++){
			px = getpixel(img, x + i * matrix[x][y]->w, y + j * matrix[x][y]->h);
			if(!px)
				average ++;
		}
	}

	average /= matrix[0][0]->w * matrix[0][0]->h;

	


}

static void printImgPixel(SDL_Surface *img)
{
	int x,y,px = 0;
	for(x = 0; x < img->w; x++){
		for(y = 0; y < img->h; y++){
			px ++;
			if(getpixel(img,x,y) > 0)
				printf("0");
			else
				printf("1");
		}
		printf("\n");
	}

	printf("px count : %d\n",px);

}

Pixel_Matrix** detectTextBlock(SDL_Surface *img)
{
	printImgPixel(img);
	
	size_t w = img->w/MATRIX_ACCURACY;
	size_t h = img->h/MATRIX_ACCURACY;

	size_t i,j;

	Pixel_Matrix **matrixs = initPixelMatrix(w, h);

	for(i = 0; i < MATRIX_ACCURACY; i++){
		for(j = 0; j < MATRIX_ACCURACY; j++){
			detectBlock(img, matrixs[i][j], w, h);
		}
	}

	return image_matrixs;
}

static void drawMatrixCase(SDL_Surface *screen, Point origine, size_t w, size_t h, size_t x, size_t y)
{
	SDL_Rect mcase;

	mcase.x = origine.x + x * w;
	mcase.y = origine.y + y * h;
	mcase.w = w;
	mcase.h = h;

	SDL_FillRect(screen, &mcase, SDL_MapRGBA(screen->format,255,0,0,100));
}




void showTextBlock(SDL_Surface *screen, Pixel_Matrix **image_matrix)
{
	size_t i,j,x,y;


	for(i = 0; i < MATRIX_ACCURACY; i++){
		for(j = 0; j < MATRIX_ACCURACY; j++){
			for(x = 0; x < SIZE_MATRIX; x++){
				for(y = 0; y < SIZE_MATRIX; y++){
					if(image_matrix[i][j].mcase[x][y] > 0){
						//printf("[%zu][%zu]:[%zu][%zu]=%d\n",i,j,x,y,image_matrix[i][j].mcase[x][y]); 
						drawMatrixCase(screen, image_matrix[i][j].origine, image_matrix[i][j].w, image_matrix[i][j].h, x, y);
					}
				}
			}
		}
	}	

}
