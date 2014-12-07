# ifndef STDLIB_STDIO
# define STDLIB_STDIO

# include <stdlib.h>
# include <stdio.h>
# include <SDL/SDL.h>
# include <SDL/SDL_image.h>
# include <math.h>
# include <gtk/gtk.h>

# endif

# ifndef ROTATION_H_
# define ROTATION_H_
#include "pixel_operations.h"


void rotation(SDL_Surface **img, double angle);
void detection(SDL_Surface *image);

# endif
