#include "extraction_operations.h"

int *nbLinesZero(SDL_Surface *img, struct bloc B) {
  int sx = B.startX, sy = B.startY, ex = B.endX, ey = B.endY;
  int bHeight = ey - sy;
  int *p_array = malloc(bHeight * sizeof(int));

  for (int j = sy; j < ey; ++j) {
    int i = sx;
    while (i < ex && convert(getpixel(img,i,j),img) !=0)
      ++i;
    if (i < ex && convert(getpixel(img,i,j),img) == 0)
      p_array[j] = 1;
    else
      p_array[j] = 0;
  }
  return p_array;
}

int nbLinesOne(SDL_Surface *img, struct bloc B) {
  int sy = B.startY, ey = B.endY;
  int bHeight = ey  - sy, nbLines = 0;
  int *array  = nbLinesZero(img, B);
  for (int i  = 0;  i < bHeight;  ++i)  {
    if  (array[i] ==  0 &&  i < (bHeight  - 1)   &&  array[i  + 1]  !=  0)
      ++nbLines;
  }
  return nbLines;
}

int EndLine(SDL_Surface *img, struct  bloc  B,  int lineStartY, int lineHeight) {
  int *p_array  = malloc(lineHeight * sizeof(int));
  int endLine;
  //Remplir p_array
  for (int i  = lineStartY; i < lineStartY  + lineHeight; ++i)  {
    endLine = B.endY  - 1;
    while (convert(getpixel(img,endLine,i), img)  !=  0 &&  endLine > 0)
      --endLine;
    p_array[i - lineStartY] = endLine;
  }
  //déterminer la valeur max de p_array
  endLine = p_array[0];
  for (int  i = 0;  i < lineHeight; ++i)  {
    if  (p_array[i] > endLine)
      endLine = p_array[i];
  }
  return  endLine;
}

int nbChar(SDL_Surface  *img, int lineStartX, int lineStartY, int lineEndX, int lineHeight) {
  int charStartX, charEndX, nbChar  = 0;
  while (lineStartX  < lineEndX) {
    charStartX  = CharStartX(img, lineStartX, lineHeight, lineStartY, lineEndX);
    charEndX  = CharEndX(img,  charStartX, lineStartY, lineHeight, lineEndX);
    ++nbChar;
    lineStartX  = charEndX  + 1;
  }
  return nbChar;
}

int CharStartX(SDL_Surface  *img, int charCounterX,  int lineHeight, int lineStartY, int  endLine) {
  int *array  = malloc(lineHeight * sizeof(int));
  int k,  min;
  for (int  i = 0;  i < lineHeight; ++i)
        array[i]  = 0;
  for (int  i = lineStartY; i < lineStartY  + lineHeight; ++i)  {
        k = charCounterX;
        while (k  < endLine &&  convert(getpixel(img,k,i), img)  !=  0)
              ++k;
        array[i - lineStartY] = k;
  }
  min = array[0];
  for (int  i = 0;  i < lineHeight; ++i)
        if  (array[i] < min)
              min = array[i];
  return  min;
}

int CharEndX(SDL_Surface  *img, int charStartX,  int lineStartY, int lineHeight, int endLine) {
      int i = charStartX  - 1,  nbPixelWhite = 0;
      while (i  < endLine &&  nbPixelWhite !=  lineHeight) {
            ++i;
            nbPixelWhite  = 0;
            for (int  j = lineStartY; j < lineStartY  + lineHeight; ++j)  {
              if (convert(getpixel(img, i,  j), img)  ==  255)
                    ++nbPixelWhite;
            }
      }
      return  i - 1;
}

struct  point CharStartEndY(SDL_Surface  *img, int charStartX, int charEndX, int lineStartY, int lineHeight)  {
      int *array  = malloc(lineHeight * sizeof(int));
      int k,  min = 0,  max = 0;
      for (int  i = 0;  i < lineHeight; ++i)
          array[i]  = 0;
      for (int  i = lineStartY; i < lineStartY  + lineHeight; ++i)  {
          int nbBlackPixel  = 0;
          k = charStartX;
          while (k  < charEndX) {
                if (convert(getpixel(img,k,i),img)  ==  0)
                      ++nbBlackPixel;
                ++k;
          }
          array[i - lineStartY] = nbBlackPixel;
      }
      int i = 0;
      while (i  < lineHeight  &&  array[i] ==  0)
          ++i;
      if (i < lineHeight)
          min = i + lineStartY;

      i = lineHeight  - 1;
      while (i  >=  0 &&  array[i]  ==  0)
          --i;
      if (i >=  0)
          max = i + lineStartY;
      struct point *point = malloc(sizeof(struct  point));
      point->startY = min;
      point->endY = max;
      return *point;
}                      

struct  charInfo  *CharInfoArray(SDL_Surface  *img, int lineStartX, int lineStartY, int lineEndX, int lineHeight) {
  int nmbChar  = nbChar(img, lineStartX, lineStartY, lineEndX, lineHeight);
  struct  charInfo  *array  = malloc(nmbChar * sizeof(struct charInfo));
  int endX, startX =  lineStartX, numChar = 0;
  while (startX  < lineEndX) {
    struct  charInfo *l = malloc(sizeof(struct  charInfo));
    startX  = CharStartX(img, startX, lineHeight, lineStartY, lineEndX);
    l->startX = startX;
    endX  = CharEndX(img,  startX, lineStartY, lineHeight, lineEndX);
    l->endX = endX;
    struct  point point  = CharStartEndY(img,  startX, endX, lineStartY, lineHeight);
    l->startY = point.startY;
    l->endY = point.endY;
    array[numChar]  = *l;
    startX  = endX  + 1;
    ++numChar;
  }
  return array;
}

struct  lineInfo  *linesInfoArray(SDL_Surface *img, struct bloc B)  {
  int nbLines = nbLinesOne(img,B);
  int ey = B.endY; 
  struct lineInfo *arrayStruct = malloc(nbLines * sizeof(struct lineInfo));
  int *array = nbLinesZero(img,B);
  int lineHeight, i = 0,  lineStartY;
  for (int k  = 0;  k < nbLines; ++k) {
    struct lineInfo *l  = malloc(sizeof(struct  lineInfo));
    while (i  < ey  &&  array[i]  ==  0)
      ++i;
    lineHeight  = 0;
    if  (i  < ey  &&  array[i]  !=  0)
      lineStartY = i;
    while (i  < ey  &&  array[i]  !=  0)  {
      ++lineHeight;
      ++i;
    }
    l->height = lineHeight;
    l->endLineX  = EndLine(img, B,  lineStartY, lineHeight);
    l->startY  = lineStartY;
    l->startX = CharStartX(img, B.startX, lineHeight, lineStartY, l->endLineX);
    l->nbChar = nbChar(img, l->startX,  lineStartY, l->endLineX,  lineHeight);
    l->charInfoArray  = CharInfoArray(img,  l->startX, lineStartY,  l->endLineX,  lineHeight);
    arrayStruct[k]  = *l;
  }
  return arrayStruct;
}

/*void  SegmentVertical(SDL_Surface *img, int lineStartY, int lineHeight, int charStartX) {
      for (int  j = lineStartY; j < lineStartY  + lineHeight; ++j)
            putpixel(img, charStartX, j,  SDL_MapRGB(img->format,0,250,0));
}*/

void SegmentHorizontal(SDL_Surface  *img, int charY,  int charStartX, int charEndX) {
      for (int  i = charStartX; i <= charEndX;  ++i)
            if  (IsValid(img->w,  img->h, i,  charY)  ==  0)
                  putpixel(img, i,  charY,  SDL_MapRGB(img->format,0,0,250));
}

/*void SegmentChar(SDL_Surface  *img, int charCounterX, int lineEndX, int lineStartY, int lineHeight) {
      int charStartX, charEndX, nbChar  = 0;
      int i = charCounterX;
      while (i  < lineEndX) {
            charStartX  = CharStartX(img, i,  lineHeight, lineStartY, lineEndX);
            SegmentHorizontal(img,  lineStartY, lineHeight, charStartX);
            charEndX  = CharEnd(img,  charStartX, lineStartY, lineHeight, lineEndX);
            SegmentVertical(img,  lineStartY, lineHeight, charEndX);
            ++nbChar;
            i = charEndX  + 1;
      }
}*/

void SegmentVertical(SDL_Surface  *img, int charX,  int charStartY, int charEndY) {
      for (int  i = charStartY; i <=  charEndY; ++i)
            if  (IsValid(img->w,  img->h, charX,  i)  ==  0)
                  putpixel(img, charX,  i,  SDL_MapRGB(img->format,0,250,0));
}

void SegmentLines(SDL_Surface *img, TextBlocList *tb )  {
  
  struct bloc B;
  B.startX = tb->x;
  B.startY = tb->y;
  B.endX = tb->x + tb->w;
  B.endY = tb->y + tb->h;

  int *array  = nbLinesZero(img,B);
  struct  lineInfo  *arrayStruct  = linesInfoArray(img,B);
  //Uint32  pixel;
  int nbLine  = 0,  endLine,  lineStartX, lineStartY, lineHeight;
  for (int  j = B.startY;  j < B.endY;  ++j)  {
        if  (array[j] ==  0 &&  j < (B.endY  - 1) &&  array[j + 1]  > 0)  {
              lineStartX  = arrayStruct[nbLine].startX;
              lineStartY  = arrayStruct[nbLine].startY;
              endLine     = arrayStruct[nbLine].endLineX;
              lineHeight  = arrayStruct[nbLine].height;
              struct  charInfo  *charInfoArray  = CharInfoArray(img,
                  lineStartX, lineStartY, endLine,  lineHeight);
              int nbrChar  = nbChar(img, lineStartX, lineStartY, endLine,
                  lineHeight);
              for (int  z = 0;  z < nbrChar; ++z)  {
                    int charStartX  = charInfoArray[z].startX - 1;
                    int charStartY  = charInfoArray[z].startY - 1;
                    int charEndX    = charInfoArray[z].endX + 1;
                    int charEndY    = charInfoArray[z].endY + 1;
                    SegmentHorizontal(img,  charStartY, charStartX, charEndX);
                    SegmentHorizontal(img,  charEndY, charStartX, charEndX);
                    SegmentVertical(img,  charStartX, charStartY, charEndY);
                    SegmentVertical(img,  charEndX, charStartY, charEndY);
              }
              /*for (int  i = lineStartX; i < endLine;  ++i)  {
                    pixel = SDL_MapRGB(img->format, 255,0,0);
                    putpixel(img,i,j,pixel);
              }*/
              
              //SegmentChar(img, lineStartX, endLine,  lineStartY, lineHeight);
        }
        if  (array[j] !=  0 &&  j < (B.endY  - 1) &&  array[j + 1]  ==  0)  {
              /*for (int  i = lineStartX; i < endLine;  ++i)  {
                pixel = SDL_MapRGB(img->format, 255,0,0);
                putpixel(img,i,j+1,pixel);
              }*/
              ++nbLine;
        }
  }
}
