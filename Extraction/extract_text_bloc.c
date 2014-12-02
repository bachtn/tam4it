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

  for(int i = 0; xmin <0 && i <= radius; i++)
    xmin++;

  for(int i = 0; ymin <0 && i <= radius; i++)
    ymin++;

  for(int i = 0; xmax > img->w && i <= radius; i++)
    xmax--;

  for(int i = 0; ymax > img->h && i <= radius; i++)
    ymax--;

  for(int i = xmin; i <= xmax; i++)
    for(int j = ymin; j <= ymax; j++)
      if(getpixel(img, (unsigned)i, (unsigned)j) > 0)
        count++;

  return count;
}

  static inline
int getRadius( SDL_Surface *img)
{
	int r=0,n=0;
	char c='w';
	
	for(int i = 0; i < img->w; i++)
		for(int j = 0; j < img->h; j++){
			if( c=='b' && getpixel(img,i,j)>0)
				r++;
			else if(c=='w' && getpixel(img,i,j)>0){
				r++;
				n++;
				c = 'b';
			}
			else if(c=='w'&& getpixel(img,i,j)==0)
				c = 'b';
			if( c=='b' && getpixel(img,j,i)>0)
				r++;
			else if(c=='w' && getpixel(img,j,i)>0){
				r++;
				n++;
				c = 'b';
			}
			else if(c=='w'&& getpixel(img,j,i)==0)
				c = 'b';
		}
	return r/n;
}

  static inline
int compareTextBlocPoint(TextBlocList *tb, SDL_Surface *img, int radius)
{
  int xmin,xmax,ymin,ymax;
  int b=0;

  xmin = tb->x - radius; xmax = tb->x + tb->w + radius;
  ymin = tb->y - radius; ymax = tb->y + tb->h + radius;

  for(int i = 0; xmin <0 && i <= radius; i++)
    xmin++;

  for(int i = 0; ymin <0 && i <= radius; i++)
    ymin++;

  for(int i = 0; xmax > img->w && i <= radius; i++)
    xmax--;

  for(int i = 0; ymax > img->h && i <= radius; i++)
    ymax--;

  for(int i = xmin; i <= xmax; i++)
    for(int j = ymin; j <= ymax; j++)
      if(getpixel(img, (unsigned)i, (unsigned)j) > 0){
        if(i < tb->x){
          tb->x = i;
          b++;
        }
        if(j < tb->y){
          tb->y = j;
          b++;
        }
        if(i > tb->x + tb->w){
          tb->w = i - tb->x;
          b++;
        }
        if(j > tb->y + tb->h){
          tb->h = j - tb->y; 
          b++;
        }
      }

  return b;
}

  static inline
TextBlocList* addTextBloc(TextBlocList *t, int x, int y)
{
  TextBlocList *tb;

  tb = malloc(sizeof(TextBlocList));
  tb->x = x;
  tb->y = y;
  tb->w = 0;
  tb->h = 0;
  tb->next = t;

  return tb;
}

  static inline
void delTextBloc(TextBlocList *t, int n)
{
  if(t){
    TextBlocList *tb = t;
    for(int i = 0; tb->next && i < n-1; i++)
      tb = tb->next;

    TextBlocList *tmp = tb->next->next;
    free(tb->next);
    tb->next=tmp;
  }
}


static inline
void showTextBlocList(TextBlocList *tb)
{
  int i = 0;
  while(tb){
    printf("%d->",i);
    tb = tb->next;
    i++;
  }
  printf("NULL\n");
}

TextBlocList* detectTextBlocs(SDL_Surface *img)
{
  if(!img){
    printf("<Error> code 0x40 in %s",__func__);
    return NULL; //call Send_Exception(0x42);
  }

  TextBlocList *tb = NULL;
  int radius;

  tb = addTextBloc(tb,0,0);
   showTextBlocList(tb);
  radius = getRadius(img);

  for(int i = 0; i < img->w; i++)
    for(int j = 0; j < img->h; j++){
      if(!compareTextBlocPoint(tb,img,radius))
        tb=addTextBloc(tb,i+radius,j+radius);
    }

  return tb;
}

inline
void showTextBlocs(SDL_Surface *screen, TextBlocList *tb)
{
  Uint32 pixel = SDL_MapRGB(screen->format,0,255,0);
  
  while(tb){
    for(int i = tb->x; i < tb->x + tb->w; i++){
      putpixel(screen,i,tb->y,pixel);
      putpixel(screen,i,tb->y+tb->h-1,pixel);
    }
    for(int j = tb->y; j < tb->y + tb->h; j++){
      putpixel(screen,tb->x,j,pixel);
      putpixel(screen,tb->x+tb->w-1,j,pixel);
    }
    tb = tb->next;
  }
}

