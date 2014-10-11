#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h> 

int isFileExists(const char *path)
{
    FILE *file;
    if (file = fopen(path, "r"))
    {
        fclose(file);
        return 1;
    }
    return 0;
}

SDL_Surface* loadImage (char path[])
{
	SDL_Surface *image = NULL;
	image =IMG_Load(path);
	return image;
}

SDL_Surface* convertToBmp (SDL_Surface *img)
{
	
}

int main(int argc, char *argv[])
{
	loadImage("~//Téléchargement//Test_sdl_image//sapin.png");
	return 0;
}

