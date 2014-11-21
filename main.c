#include "Chargement/load.h"
#include "Pre-traitement/pixel_operations.h"
#include "Extraction/extract_text_bloc.h"


void wait_for_keypressed(void)
{
	SDL_Event event;
	for (;;)
	{
		SDL_WaitEvent( &event );
		switch (event.type)
		{
			case SDL_KEYDOWN : return;
			default: break;
		}
	}
}

int main (int argc, char* argv[])
{
	SDL_Surface *img = NULL;
	SDL_Surface *screen = NULL;
  TextBlocList *tb = NULL;

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

	if(SDL_BlitSurface(img, NULL, screen, NULL) < 0)
		return EXIT_FAILURE;

	SDL_UpdateRect(screen, 0, 0, img->w, img->h);

	wait_for_keypressed();
	Greyscale(img);

	if(SDL_BlitSurface(img, NULL, screen, NULL) < 0)
		return EXIT_FAILURE;

	SDL_UpdateRect(screen, 0, 0, img->w, img->h);

  printf("0\n");
  fflush(stdout);
	wait_for_keypressed();
	whiteBlack(img);

  printf("1\n");
  fflush(stdout);

	if(SDL_BlitSurface(img, NULL, screen, NULL) < 0)
		return EXIT_FAILURE;
	SDL_UpdateRect(screen, 0, 0, img->w, img->h);

  printf("2\n");
  fflush(stdout);

	wait_for_keypressed();
  tb = detectTextBlocs(img);
   printf("3\n");
  fflush(stdout);

  showTextBlocs(screen,tb);
   printf("4\n");
  fflush(stdout);

	SDL_UpdateRect(screen, 0, 0, img->w, img->h);

	wait_for_keypressed();
	SDL_Quit();

	return EXIT_SUCCESS;
}
