#include "extract_text_bloc.h"
#include "../Pre-traitement/pixel_operations.h"

#define DEBUG 1

int pxCountNeightbours( SDL_Surface *img, int x, int y, int radius)
{	
	if(DEBUG)
		printf("%s called",__func__);

	if(!img){
		printf("<Error> code 0x40 in %s",__func__);
		return 0x42; //call Send_Exception(0x42);
	}
	if(x < 0 || y < 0 || radius <= 0){
		printf("<Error> code 0x43 in %s",__func__);
		return 0x43; //call SendException(0x43);
	}

	int xmin,xmax,ymin,ymax,count = 0;

  xmin = x - radius; xmax = x + radius;
  ymin = y - radius; ymax = y + radius;

	for(int i; xmin <0 && i <= radius; i++)
		xmin++;

	for(int i; ymin <0 && i <= radius; i++)
		ymin++;

	for(int i; xmax > img->w && i <= radius; i++)
		xmax--;

	for(int i; ymax > img->h && i <= radius; i++)
		ymax--;

	for(int i = xmin; i <= xmax; i++)
		for(int j = ymin; j <= ymax; j++)
     if(getpixel(img, (unsigned)i, (unsigned)j) > 0)
       count++;

	return count;
}

void compareTextBlocPoint(int *x, int *y,int *v, int *w, int radius)
{
	int xmin,xmax,ymin,ymax;

  xmin = *x - radius; xmax = *x + radius;
  ymin = *v - radius; ymax = *w + radius;

	for(int i; xmin <0 && i <= radius; i++)
		xmin++;

	for(int i; ymin <0 && i <= radius; i++)
		ymin++;

	for(int i; xmax > img->w && i <= radius; i++)
		xmax--;

	for(int i; ymax > img->h && i <= radius; i++)
		ymax--;

  for(int i = xmin; i <= xmax; i++)
		for(int j = ymin; j <= ymax; j++)
      if(getpixel(img, (unsigned)i, (unsigned)j) > 0){
        if(xmin < *x)
          *x = i;
        if(ymin < *y)
          *y = j;
        if(xmax > *v)
         *v = xmax;
        if(ymax > *w)
         *w = ymax; 
      }
}

TextBlocList* detectBlocs(SDL_Surface *img, int detection_radius)
{
 	if(!img){
		printf("<Error> code 0x40 in %s",__func__);
		return 0x42; //call Send_Exception(0x42);
  }

  TextBlocList *tb;

  for(int i = 0; i < img->w; i++)
    for(int j = 0; j < img->h; j++){
      //fix Me

    }
      


  return tb;

}
