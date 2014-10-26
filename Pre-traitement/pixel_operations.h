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
<<<<<<< HEAD:Extraction/pixel_operations.h
 
# include <stdlib.h>
# include <SDL.h>
//Cette fonction retourne le  pixel de coordonné (x,y) dans l'image
Uint32 getpixel(SDL_Surface *surface, unsigned x, unsigned y);
//Cette fonction change le pixel de coordonné (x,y) dans l'image
//par le pixel passé en paramètre
void putpixel(SDL_Surface *surface, unsigned x, unsigned y, Uint32 pixel);
//Cette fonction permet de transformer une image en couleur
//en une image à niveau de gris
void Greyscale(SDL_Surface *surface);
//Cette fonction retourne la composante r du pixel passé en paramètre
int convert(Uint32 pixel, SDL_Surface *image);
=======

Uint32 getpixel(SDL_Surface *surface, unsigned x, unsigned y);

void putpixel(SDL_Surface *surface, unsigned x, unsigned y, Uint32 pixel);

void Greyscale(SDL_Surface *image);

int convert(Uint32 pixel, SDL_Surface *image);

int otsu_th(SDL_Surface *image);

void whiteBlack(SDL_Surface *image);

int IsValid(SDL_Surface *image, int i, int j);

void cleanup(SDL_Surface *image, SDL_Surface *copy);

>>>>>>> a75289d416dd767538c4ff5030483bcd649f28e2:Pre-traitement/pixel_operations.h
# endif
