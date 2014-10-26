#ifndef STDLIB_STDIO
#define STDLIB_STDIO

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#endif

#ifndef EXTRACT_CHAR
#define EXTRACT_CHAR

typedef struct{
  int x,y;
  int weight,hight;
}TextBloc;

typedef struct{
  int hight, width;
  int x,y;
}Line;

typedef struct charCoordonateNode{
  int x,y;
  int hight, width;
  struct charCoordonateNode *next;
}CharCoordonateNode;

typedef struct
{
  CharCoordonateNode *first;
}CharCoordonate;

CharCoordonate* getCharInCoord (SDL_Surface* img, Line *l);
void drawChar (SDL_Surface* img, CharCoordonate *c);

#endif
