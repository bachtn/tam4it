#include "extraction_operations.h"
#include "pixel_operations.h"

int *nbLignesZero(SDL_Surface *image)
{
  int *p_array = (int*)malloc(sizeof(int)*image->h);
  int nbPixel;
  Uint8 r;
  for (int j = 0; j < image->h; ++j)
  {
    nbPixel = 0;
    for (int i = 0; i < image->w; ++i)
    {
      r = convert(getpixel(image,i,j),image);
      if (r == 0)
      {
        ++nbPixel;
      }
    }
    p_array[j] = nbPixel;
  }
  return p_array;
}

int nbLignesOne(SDL_Surface *image)
{
  int nbLignes = 0;
  int *array = (int*)malloc(sizeof(int)*image->h);
  array = nbLignesZero(image);
  for (int i = 0; i < image->h; ++i)
  {
    if (array[i] == 0 && i < (image->h - 1) && array[i + 1] != 0)
    {
      ++nbLignes;
    }
  }
  return nbLignes;
}

struct linesInfo *lignesInfoArray(SDL_Surface *image)
{
  struct linesInfo *arrayStruct = malloc(sizeof(struct linesInfo)*nbLignesOne(image));
  int *array = malloc(sizeof(int)*image->h);
  array = nbLignesZero(image);
  int linesLength, i = 0, lineYcordinate;
  for (int k = 0; k < nbLignesOne(image); ++k)
  {
    struct linesInfo *l = malloc(sizeof(struct linesInfo));

    while (i < image->h && array[i] == 0)
    {
      ++i;
    }

    linesLength = 0;
    
    if (i < image->h && array[i] != 0)
    {
      lineYcordinate = i;
    }
    
    while(i < image->h && array[i] != 0)
    {
      ++linesLength;
      ++i;
    }
    
    if (i < image-> h)
    {
      linesLength = i - lineYcordinate;
    }
    l->length = linesLength;
    l->y = lineYcordinate;
    l->x = LineStartXcordinate(image, linesLength, lineYcordinate, 0);
    arrayStruct[k] = *l;
  }
  return arrayStruct;
}

int LineStartXcordinate(SDL_Surface *image, int lineHeight, int lineYcordinate, int lineXcounterStart)
{
  //Variables Declaration
  int *array = malloc(lineHeight * sizeof(int));
  Uint32 pixel;
  int k, min;

  //Instructions
  for (int i = 0; i < lineHeight; ++i)
  {
    array[i] = 0;
  }
  
  for (int j = lineYcordinate; j < lineYcordinate + lineHeight; ++j)
  {
    k = lineXcounterStart;
    pixel = getpixel(image, k, j);
    while (convert(pixel, image) != 0)
    {
      ++k;
      pixel = getpixel(image, k, j);
    }
    array[j - lineYcordinate] = k;
  }

  min = array[0];
  for (int j = 0; j < lineHeight; ++j)
  {
    if (array[j] < min)
      min = array[j];
  }
  return min;
}

void SegmentLign(SDL_Surface *image)
{
  int *array = (int*)malloc(sizeof(int)*image->h);
  array = nbLignesZero(image);
  Uint32 pixel;
  Uint8 r,g,b;
  for (int j = 0; j < image->h; ++j)
  {
    if (array[j] == 0 && j < (image->h - 1) && array[j + 1] > 0)
    {
      for (int i = 0; i < image->w; ++i)
      {
        r = 255;
        g = 0;
        b = 0;
        pixel = SDL_MapRGB(image->format, r, g, b);
        putpixel(image, i, j, pixel);
      }
    }

    if (array[j] != 0 && j < (image->h - 1) && array[j + 1] == 0)
    {
      for (int i = 0; i < image->w; ++i)
      {
        r = 255;
        g = 0;
        b = 0;
        pixel = SDL_MapRGB(image->format, r, g, b);
        putpixel(image, i, j + 1, pixel);
      }
    }
  }
}

void SegmentChar(SDL_Surface *image)
{
  Uint32 pixel;
  Uint8 r, g, b;
  for (int i = 0; i < image->h; ++i)
  {
    r = 255;
    g = 0;
    b = 0;
    pixel = SDL_MapRGB(image->format, r, g, b);
    putpixel(image, 63, i, pixel);
  }
}
