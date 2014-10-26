# ifndef PIXEL_OPERATIONS_H_
# define PIXEL_OPERATIONS_H_
 
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
# endif
