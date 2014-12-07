#include "rotation.h"

void rotation(SDL_Surface *img, double angle)
{
        int diagonal, centre_x, centre_y;
        SDL_Surface *new_img;
        diagonal = (sqrt((img->w)*(img->w) + (img->h)*(img->h))) + 1;
        new_img = SDL_CreateRGBSurface(0, diagonal, diagonal, 32,
                        rmask, gmask, bmask, amask);
        for(int x = 0; x <new_img->h ; x++)
        {
                for(int y = 0; y <new_img->w; y++)
                {
                        putpixel(new_img, x, y, 0xffffffff);
                }
        }
        centre_x = ((img->w)/2) + 1;
        centre_y = ((img->h)/2) + 1;
        for(int x = 0; x<img->w; x++)
        {
                for(int y = 0; y<img->h; y++)
                {
                        if(getpixel(img, x, y) == 0/*xffffffff*/)
                                putpixel(new_img, abs(lrint(centre_x + (x - centre_x)*cosf(-angle) - (y - centre_y)*sinf(-angle))), abs(lrint(centre_y + (x - centre_x)*sinf(-angle) + (y - centre_y)*cosf(-angle))),
                                        getpixel(img, x, y));
                }
        }
        //free(img);
        img = new_img;
}
