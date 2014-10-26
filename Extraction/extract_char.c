#include "extract_char.h"
#include "../Pre-traitement/pixel_operations.h"

CharCoordonate* getCharInCoord (SDL_Surface* img, Line *l)
{
  int i = 0, j, r, begin = -1;
  CharCoordonate *returnValue = malloc (sizeof (CharCoordonate));
  CharCoordonateNode *actualF = returnValue->first, *actual;
  
  while (i < l->width)
    {
      r = 0;
      for (j = 0; i < l->hight; j++)
	r += getpixel(img, i, j);
      if (r == 0)
	{
	  if (begin == -1)
	    begin = i;
	}
      else
	{
	  if (begin != -1)
	    {
	      actual = malloc (sizeof (CharCoordonateNode));
	      actual->x = begin;
	      actual->y = l->y;
	      actual->hight = l->hight;
	      actual->width = j - begin;
	      actual->next = NULL;
	      actualF->next = actual;
	      actualF = actual;
	      begin = -1;
	    }
	}
      i++;
    }
  return returnValue;
}

void drawChar (SDL_Surface* img, CharCoordonate *c)
{
  CharCoordonateNode *actual = c->first;
  while (actual != NULL)
    {
      for (int i = 0; i < actual->hight; i++)
	putpixel (img, actual->x, i, SDL_MapRGB (img->format, 255, 0, 0));
      actual = actual->next;
    }
}
