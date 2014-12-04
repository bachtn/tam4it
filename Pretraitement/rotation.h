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

#if SDL_BYTEORDER == SDL_BIG_ENDIAN
   const Uint32 rmask = 0xff000000;
   const Uint32 gmask = 0x00ff0000;
   const Uint32 bmask = 0x0000ff00;
   const Uint32 amask = 0x000000ff;
#else
   const Uint32 rmask = 0x000000ff;
   const Uint32 gmask = 0x0000ff00;
   const Uint32 bmask = 0x00ff0000;
   const Uint32 amask = 0xff000000;
#endif

void rotation(SDL_Surface *img, double angle);

# endif
