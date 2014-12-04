#include "rotation.h"

void rotation(SDL_Surface *img, float angle)
{
        int diagonal, centre_x, centre_y;
        SDL_Surface *new_img;

        diagonal = (sqrt((img->w)(img->w) + (img->h)(img->h))) + 1;
        new_img = SDL_CreateRGBSurface(0, diagonal, diagonal, 32,
                        rmask, gmask, bmask, amask);

        centre_x = ((img->w)/2) + 1;
        centre_y = ((img->h)/2) + 1;


        for(int x = 0; x<img->w; x++)
        {
                for(int y = 0; y<img->h; y++)
                {
                        putpixel(new_img, (x-centre_x)*cosf(angle) + centre_x, 
                                        (y-centre_y)*sinf(angle) + centre_y, 
                                        getpixel(img, x, y));
                }
        }
        free(img);
        img = new_img;
}
