#include "Chargement/load.h"
#include "Extraction/extract_text_bloc.h"

int main (int argc, char* argv[])
{
	SDL_Surface *img = NULL;
	SDL_Surface *screen = NULL;

	Pixel_Matrix **image_matrix = NULL;

	if(argc == 2)
		img = loadImage(argv[1]);
	else
		return EXIT_FAILURE;

	if( SDL_Init(SDL_INIT_VIDEO)==-1 ) 
		return EXIT_FAILURE;

	
	screen = SDL_SetVideoMode(img->w, img->h, 0, SDL_SWSURFACE|SDL_ANYFORMAT);
	if ( screen == NULL )
	{
		return EXIT_FAILURE;
	}

	image_matrix = detectTextBlock(img);
	
	showTextBlock(screen, image_matrix);

	return EXIT_SUCCESS;
}
