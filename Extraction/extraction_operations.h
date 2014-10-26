#ifndef STDLIB_STDIO
#define STDLIB_STDIO

#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL.h>
#include <math.h>

#endif

#ifndef EXTRACTION_OPERATIONS_H_
#define EXTRACTION_OPERATIONS_H_

struct linesInfo
{
  int length;
  int x;
  int y;
};
int *nbLignesZero(SDL_Surface *image);
int nbLignesOne(SDL_Surface *image);
struct linesInfo *lignesInfoArray(SDL_Surface *image);
int LineStartXcordinate(SDL_Surface *image, int lineLength, int lineYcordinate, int lineXcordinateStart);
void SegmentLign(SDL_Surface *image);
void SegmentChar(SDL_Surface *image);

#endif
