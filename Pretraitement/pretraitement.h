# ifndef STDLIB_STDIO
# define STDLIB_STDIO

# include <stdlib.h>
# include <stdio.h>
# include <SDL/SDL.h>
# include <SDL/SDL_image.h>
# include <math.h>
# include <gtk/gtk.h>

# endif

# ifndef PRETRAITEMENT_H_
# define PRETRAITEMENT_H_
 
void Greyscale(SDL_Surface *image);
void Fuzzy(SDL_Surface  *img, SDL_Surface *imgnv,  const char  mask[]);
int otsu_th(SDL_Surface *image);
void whiteBlack(SDL_Surface *image);
void Median(SDL_Surface *img, SDL_Surface *imgnv);
int  Median_tmp(int  *tab, int tabLength);


# endif
