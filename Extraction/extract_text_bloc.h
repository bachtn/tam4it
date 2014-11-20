#ifndef STDLIB_TDIO
#define STDLIB_STDIO

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#endif

#ifndef EXTRACT_TBLOCK
#define EXRACT_TBLOCK

typedef struct TextBlocList{
  int x,y;
  int w,h;

  TextBlocList *next;
}


int pxCountNeightbours(SDL_Surface *img, int x, int y, int radius); //Get the number of black pixel near the coordinate pixel x,y with a radius



#endif
