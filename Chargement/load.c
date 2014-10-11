#include "load.h"

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
	if (isFileExist(path))
	{
	    SDL_Surface *image = NULL;
	    image =IMG_Load(path);
	    return image;
	}
	else
	{
		return NULL;
	}
}

SDL_Surface* convertToBmp (SDL_Surface *img)
{
	
}

int main(int argc, char *argv[])
{
	//loadImage("~//Téléchargement//Test_sdl_image//sapin.png");
	loadImage(argv[0]);
	return 0;
}

