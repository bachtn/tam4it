#include "pixel_operations.h"
#include "pretraitement.h"

void Greyscale(SDL_Surface *image)
{
  Uint32 pixel;
  Uint8 r, g, b;
  float lum;
  for (int i = 0; i < image->w; i++)
  {
    for (int j = 0; j < image->h; j++)
    {
      pixel = getpixel(image, i, j);
      SDL_GetRGB(pixel, image->format, &r, &g, &b);
      lum = (r * 0.3 + g * 0.59 + b * 0.11);
      pixel = SDL_MapRGB(image->format, lum, lum, lum);
      putpixel(image, i, j, pixel);
    }
  }
}
int otsu_th(SDL_Surface *image)   
{
  int hist[256];
  double prob[256], omega[256]; /* prob of graylevels */
  double myu[256];   /* mean value for separation */
  double max_sigma, sigma[256]; /* inter-class variance */
  int i, x, y; /* Loop variable */
  int threshold; /* threshold for binarization */         
               
  /* Histogram generation */
   for (i = 0; i < 256; i++)
    hist[i] = 0;
  for (y = 0; y < image->h; y++)
    for (x = 0; x < image->w; x++)
    {
      hist[convert(getpixel(image,x,y),image)]++;
    }
  /* calculation of probability density */
  for ( i = 0; i < 256; i ++ )
  {
    prob[i] = (double)hist[i] / (image->w * image->h);
  }
   
  /* omega & myu generation */
  omega[0] = prob[0];
  myu[0] = 0.0;       /* 0.0 times prob[0] equals zero */
  for (i = 1; i < 256; i++)
  {
    omega[i] = omega[i-1] + prob[i];
    myu[i] = myu[i-1] + i*prob[i];
  }
  
  /* sigma maximization
     sigma stands for inter-class variance 
     and determines optimal threshold value */
  threshold = 0;
  max_sigma = 0.0;
  for (i = 0; i < 256-1; i++)
  { 
    if (omega[i] != 0.0 && omega[i] != 1.0)
      sigma[i] = pow(myu[256-1]*omega[i] - myu[i], 2) / (omega[i]*(1.0 - omega[i]));
    else
      sigma[i] = 0.0;
    if (sigma[i] > max_sigma)
    {
      max_sigma = sigma[i];
      threshold = i;
    }
  }
  return threshold;
}

void whiteBlack(SDL_Surface *image)
{
  Uint32 pixel;
  Uint8 r, g, b, a;
  int seuil = otsu_th(image);
  for (int i = 0; i < image->w; i++)
  {
    for (int j = 0; j < image->h; j++)
    {
      pixel = getpixel(image, i, j);
      SDL_GetRGBA(pixel, image->format, &r, &g, &b, &a);
      if (r < seuil)
          r = 0;
      else
          r = 255;
      pixel = SDL_MapRGB(image->format, r, r, r);
      putpixel(image, i, j, pixel);
    }
  }
}

const char  mask_fuzzy[]  = {
  1, 1, 1,
  1, 1, 1,
  1, 1, 1
};

void Fuzzy(SDL_Surface *img, SDL_Surface *imgnv, const char  mask[])  {
    Uint32  pixel;
    for (int j  = 1;  j < img->h  - 1; ++j)
        for (int  i = 1;  i < img->w  - 1; ++i) {
            int sum = 0;
            for (int  dy  = j - 1;  dy  <=  j + 1;  ++dy)
                for (int  dx  = i - 1;  dx  <=  i + 1;  ++dx)
                      sum = sum + convert(getpixel(img,dx,dy),img)  * mask[dx - i + 1 + (dy - j + 1) * (dx - i + 1)];
            sum = sum / 9;
            pixel = SDL_MapRGB(img->format, sum, sum, sum);
            putpixel(imgnv,i,j,pixel);
        }
}

int Median_tmp(int  *tab, int tabLength) {
    int x = 0,  min,  counter = 0;
    while (x <  tabLength)  {
        min = tab[x];
        for (int  i = x;  i < tabLength;  ++i)  {
              if  (tab[i] < min)  {
                    min = tab[i];
                    counter = i;
              }
        }
        if (min != tab[x])  {
        int c = tab[x];
        tab[x]  = tab[counter];
        tab[counter]  = c;
        }
        ++x;
    }
    return tab[tabLength/2];
}
       

void Median(SDL_Surface *img, SDL_Surface *imgnv) {
    Uint32  pixel;
    int *tab =  malloc(9  * sizeof(int));
    for ( int j = 1;  j < img->h  - 1;  ++j)
        for (int  i = 1;  i < img->w  - 1;  ++i)  {
            int z = 0;
            for (int  dy  = j - 1;  dy  <=  j + 1;  ++dy)
                for (int  dx  = i - 1;  dx  <=  i + 1;  ++dx) {
                        tab[z]  = convert(getpixel(img,dx,dy),img);
                        ++z;
                    }
            int r = Median_tmp(tab,z);
            pixel = SDL_MapRGB(imgnv->format, r,r,r);
            putpixel(imgnv,i,j,pixel);
        }
}
                        
