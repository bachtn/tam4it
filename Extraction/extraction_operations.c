#include "extraction_operations.h"
#include "pixel_operations.h"

int *nbLinesZero(SDL_Surface *image)
{
  int *p_array = malloc(image->h * sizeof(int));
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

int nbLinesOne(SDL_Surface *image)
{
  int nbLines = 0;
  int *array = malloc(sizeof(int)*image->h);
  array = nbLinesZero(image);
  for (int i = 0; i < image->h; ++i)
  {
    if (array[i] == 0 && i < (image->h - 1) && array[i + 1] != 0)
    {
      ++nbLines;
    }
  }
  return nbLines;
}

struct lineInfo *linesInfoArray(SDL_Surface *image)
{
  int nbLines = nbLinesOne(image);
  struct lineInfo *arrayStruct = malloc(nbLines * sizeof(struct lineInfo));
  int *array = malloc(sizeof(int)*image->h);
  array = nbLinesZero(image);
  int lineHeight, i = 0, lineYcoordinate;
  for (int k = 0; k < nbLinesOne(image); ++k)
  {
    struct lineInfo *l = malloc(sizeof(struct lineInfo));

    while (i < image->h && array[i] == 0)
    {
      ++i;
    }

    lineHeight = 0;
    
    if (i < image->h && array[i] != 0)
    {
      lineYcoordinate = i;
    }
    
    while(i < image->h && array[i] != 0)
    {
      ++lineHeight;
      ++i;
    }
    
    if (i < image-> h)
    {
      lineHeight = i - lineYcoordinate;
    }

    int endLine = EndLine(image, lineYcoordinate, lineHeight, image->w);
    l->height = lineHeight;
    l->endLine = endLine;
    l->y = lineYcoordinate;
    l->x = CharacterStartXcoordinate(image, lineHeight, lineYcoordinate, 0);
    l->length = endLine - l->x;
    arrayStruct[k] = *l;
  }
  return arrayStruct;
}

int CharacterStartXcoordinate(SDL_Surface *image, int lineHeight, int lineYcoordinate, int lineXcounterStart)
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
  
  for (int j = lineYcoordinate; j < lineYcoordinate + lineHeight; ++j)
  {
    k = lineXcounterStart;
    pixel = getpixel(image, k, j);
    while (convert(pixel, image) != 0)
    {
      ++k;
      pixel = getpixel(image, k, j);
    }
    array[j - lineYcoordinate] = k;
  }

  min = array[0];
  for (int j = 0; j < lineHeight; ++j)
  {
    if (array[j] < min)
      min = array[j];
  }
  return min;
}

int EndLine(SDL_Surface *image, int lineYcoordinate, int lineHeight, int endBloc)
{
  int *p_array = malloc(lineHeight * sizeof(int));
  int endLine;
  for (int i = lineYcoordinate; i < lineYcoordinate + lineHeight; ++i)
  {
    endLine = endBloc - 1;
    while (convert(getpixel(image, endLine, i), image) != 0 && endLine > 0)
    {
      endLine--;
    }
    p_array[i - lineYcoordinate] = endLine;
  }
  endLine = p_array[0];
  for (int i = 0; i < lineHeight; ++i)
  {
    if (p_array[i] > endLine)
      endLine = p_array[i];
  }
  return endLine;
}

void SegmentLines(SDL_Surface *image)
{
  int *array = malloc(image->h * sizeof(int));
  array = nbLinesZero(image);
  int nbLines = nbLinesOne(image);
  struct lineInfo *arrayStruct = malloc(nbLines * sizeof(struct lineInfo));
  arrayStruct = linesInfoArray(image);
  Uint32 pixel;
  int nbLine = 0, charStartX, endLine, lineHeight, lineY, lineX;
  for (int j = 0; j < image->h; ++j)
  {
    lineHeight = arrayStruct[nbLine].height;
    lineY = arrayStruct[nbLine].y;
    lineX = arrayStruct[nbLine].x;
    charStartX = CharacterStartXcoordinate(image, lineHeight, lineY, lineX);
    endLine = arrayStruct[nbLine].endLine;

    if (array[j] == 0 && j < (image->h - 1) && array[j + 1] > 0)
    {
      for (int i = charStartX; i < endLine; ++i)
      {
        pixel = SDL_MapRGB(image->format, 255, 0, 0);
        putpixel(image, i, j, pixel);
      }
    }
    
    if (array[j] != 0 && j < (image->h - 1) && array[j + 1] == 0)
    {
      for (int i = charStartX; i < endLine; ++i)
      {
        pixel = SDL_MapRGB(image->format, 255, 0, 0);
        putpixel(image, i, j + 1, pixel);
      }
      ++nbLine;
    }
  }
}
