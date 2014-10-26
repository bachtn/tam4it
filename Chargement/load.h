#ifndef STDLIB_STDIO
#define STDLIB_STDIO

#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <math.h>

#endif

#ifndef LOAD
#define LOAD

int isFileExist(const char *path);

SDL_Surface* loadImage (char path[]);

#endif
