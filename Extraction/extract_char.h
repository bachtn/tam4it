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
	int hight;
	int x,y;
}Line;

typedef struct{
	int x,y;
	CharList *next;

}CharNode;

void getPixelByCollumn( SDL_Surface* img, Line l);

#endif
