#include "load.h"

int isFileExist(const char *path)
{
    FILE *file = fopen(path, "r");
    if (file)
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
