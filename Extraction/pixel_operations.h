#ifndef STDLIB_STDIO
#define STDLIB_STDIO

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#endif

# ifndef PIXEL_OPERATIONS_H_
# define PIXEL_OPERATIONS_H_

Uint32 getpixel(SDL_Surface *surface, unsigned x, unsigned y);
void putpixel(SDL_Surface *surface, unsigned x, unsigned y, Uint32 pixel);
void Greyscale(SDL_Surface *image);
int convert(Uint32 pixel, SDL_Surface *image);
int otsu_th(SDL_Surface *image);
void whiteBlack(SDL_Surface *image);
int IsValid(SDL_Surface *image, int i, int j);
void cleanup(SDL_Surface *image, SDL_Surface *copy);

# endif
