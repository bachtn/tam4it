#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <err.h>
#include "SDL_functions.h"
#include "pixel_operations.h"
#include "extraction_operations.h"

void main_function()
{
  init_sdl();
  SDL_Surface *image = NULL; 
  image = load_image("image.jpg");
  /*struct lineInfo *arrayStruct = malloc(sizeof(struct lineInfo)*nbLinesOne(image));
  arrayStruct = linesInfoArray(image);
  for (int i = 0; i < nbLinesOne(image); ++i)
  {
    printf("line[%d]: length = %d ; endLine = %d ; x = %d ; y = %d\n", i, arrayStruct[i].length, arrayStruct[i].endLine, arrayStruct[i].x, arrayStruct[i].y);
  }*/
  SegmentLines(image);
  display_image(image);
  wait_for_keypressed();
  SDL_FreeSurface(image);
}
