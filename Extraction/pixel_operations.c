# include "pixel_operations.h"
#include <math.h>

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
      pixel = SDL_MapRGB(image->format, lum, lum, lum);
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
