#include "Chargement/load.h"
#include "Extraction/extract_text_bloc.h"

int main (int argc, char* argv[])
{
	SDL_Surface *img = NULL;

 	if(argc == 2)
		img = loadImage(argv[1]);
	else
		return EXIT_FAILURE;

	//FIX ME

	return EXIT_FAILURE;
}
