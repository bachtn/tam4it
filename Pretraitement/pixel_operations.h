# ifndef STDLIB_STDIO
# define STDLIB_STDIO

# include <stdlib.h>
# include <stdio.h>
# include <SDL/SDL.h>
# include <SDL/SDL_image.h>
# include <math.h>
# include <gtk/gtk.h>

# endif

# ifndef PIXEL_OPERATIONS_H_
# define PIXEL_OPERATIONS_H_
 
//Cette fonction retourne le  pixel de coordonné (x,y) dans l'image
Uint32 getpixel(SDL_Surface *surface, unsigned x, unsigned y);
//Cette fonction change le pixel de coordonné (x,y) dans l'image
//par le pixel passé en paramètre
void putpixel(SDL_Surface *surface, unsigned x, unsigned y, Uint32 pixel);
//Cette fonction retourne la composante r du pixel passé en paramètre
int convert(Uint32 pixel, SDL_Surface *image);

//
int IsValid(int xMax, int yMax, int x,  int y);

# endif
