# include "pixel_operations.h"

static inline
Uint8* pixelref(SDL_Surface *surf, unsigned x, unsigned y)
{
  int bpp = surf->format->BytesPerPixel;
  return (Uint8*)surf->pixels + y * surf->pitch + x * bpp;
}
 
Uint32 getpixel(SDL_Surface *surface, unsigned x, unsigned y)
{
  Uint8 *p = pixelref(surface, x, y);
  switch(surface->format->BytesPerPixel)
  {
    case 1:
      return *p;
    case 2:
      return *(Uint16 *)p;
    case 3:
      if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
        return p[0] << 16 | p[1] << 8 | p[2];
      else
        return p[0] | p[1] << 8 | p[2] << 16;
    case 4:
      return *(Uint32 *)p;
  }
  return 0;
}
 
void putpixel(SDL_Surface *surface, unsigned x, unsigned y, Uint32 pixel)
{
  Uint8 *p = pixelref(surface, x, y);
  switch(surface->format->BytesPerPixel)
  {
    case 1:
      *p = pixel;
      break;
    case 2:
      *(Uint16 *)p = pixel;
      break;
    case 3:
      if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
      {
        p[0] = (pixel >> 16) & 0xff;
        p[1] = (pixel >> 8) & 0xff;
        p[2] = pixel & 0xff;
      }
      else
      {
        p[0] = pixel & 0xff;
        p[1] = (pixel >> 8) & 0xff;
        p[2] = (pixel >> 16) & 0xff;
      }
      break;
    case 4:
      *(Uint32 *)p = pixel;
      break;
  }
}

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
      r = lum;
      g = lum;
      b = lum;
      pixel = SDL_MapRGB(image->format, r, g, b);
      putpixel(image, i, j, pixel);
    }
  }
}
int convert(Uint32 pixel, SDL_Surface *image)
{
  Uint8 r, g, b;
  SDL_GetRGB(pixel, image->format, &r, &g, &b);
  return (int)r;
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
  Uint8 r, g, b;
  int seuil = otsu_th(image);
  for (int i = 0; i < image->w; i++)
  {
    for (int j = 0; j < image->h; j++)
    {
      pixel = getpixel(image, i, j);
      SDL_GetRGB(pixel, image->format, &r, &g, &b);
      if (r < seuil)
      {
        r = 0;
        g = 0;
        b = 0;
      }
      else
      {
        r = 255;
        g = 255;
        b = 255;
      }
      pixel = SDL_MapRGB(image->format, r, g, b);
      putpixel(image, i, j, pixel);
    }
  }
}

int IsValid(SDL_Surface *image, int i, int j)
{
  return ((i >= 0) && (i < image->w) && (j >= 0) && (j < image->h));
}

void cleanup(SDL_Surface *image, SDL_Surface *copy)
{
  int r1, r2, k;
  Uint32 pixel;
  Uint8 r;
  for (int i = 0; i < image->w; i++)
  {
    for (int j = 0; j < image->h; j++)
    {
      r1 = convert(getpixel(copy,i,j),image);
      k = 0;
      for (int l = i - 1; l <= i + 1; l++)
      {
        for (int m = j - 1; m <= j + 1; m++)
        {
          if (IsValid(image, l, m))
          {
            r2 = convert(getpixel(copy,l,m),copy);
            if (r2 != r1)
            {
              k++;
            }
          }
        }
      }

      //Tester si le nombre des pixels (au tour du pixel étudier) qui sont different du pixel etudier est >= 7
      if (k == 8)
      {
        pixel = getpixel(image, i, j);
        r = r2;
        pixel = SDL_MapRGB(image->format,r,r,r);
        putpixel(image, i, j, pixel);   
      }
    }
  }
}
