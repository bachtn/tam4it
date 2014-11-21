#ifndef STDLIB_STDIO
#define STDLIB_STDIO

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#endif

#ifndef EXTRACT_TBLOCK
#define EXTRACT_TBLOCK

typedef struct text_bloc_list{
  int x,y;
  int w,h;

  struct text_bloc_list *next;
}TextBlocList;
//A struct which allow to have an infinity of TextBloc, each TextBlocList will contain the origin point of a text bloc and these weight and hight

int pxCountNeightbours(SDL_Surface *img, int x, int y, int radius); 
//Get the number of black pixel near the coordinate pixel x,y with a radius

TextBlocList* detectTextBlocs(SDL_Surface *img);
//Return a list of TextBloc which are contain in the image

void showTextBlocs(SDL_Surface *screen, TextBlocList *tb);
//Print all TextBloc of the image on the screen in red

#endif
