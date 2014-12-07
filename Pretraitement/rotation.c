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
                        if(getpixel(img, x, y) == 0)
                                putpixel(new_img, abs(lrint(centre_x + (x - centre_x)*cosf(-angle) - (y - centre_y)*sinf(-angle))), abs(lrint(centre_y + (x - centre_x)*sinf(-angle) + (y - centre_y)*cosf(-angle))),
                                        getpixel(img, x, y));
                }
        }
        //free(img);
        img = new_img;
}

void detection(SDL_Surface *image)
{
        long double mat[image->h], var[15];
        long double  moyenne = 0, variance = 0, angle = 0;
        int max_variance = 0;
        SDL_Surface *img;
        Uint32 pixel;

        for(int x =0; x<image->h; x++) //initialisation de la matrice
                mat[x] = 0;

        for(int a = 0; a<15; a++) //test pour chaque angle
        {
                img  = SDL_ConvertSurface(image, image->format, image->flags);
                rotation(img, M_PI * (a) / 180);
                for(int i =0; i<img->h; i++) //compte le nb de pixel noir
                {
                        for(int j = 0; j <img->w; j++)
                        {
                                pixel = getpixel(img, j, i);
                                if(pixel  != 0xffffffff)
                                        mat[i] = mat[i] + 1;
                        }
                }

                for(int i = 0; i < img->h ; i++) //moyenne pixel noir
                {
                        moyenne = mat[i] + moyenne;
                }
                moyenne = moyenne/img->h;


                for(int i = 0; i< img->h ; i++) //variance
                {
                        variance = variance + (((mat[i] - moyenne)*(mat[i] - moyenne))/img->h);
                }
                var[a] = variance;
                free(img);
        }

        for(int l = 0; l < img->h ; l++) //variance max
        {
                if(var[max_variance] <= var[l])
                        max_variance = l;
        }
        angle = max_variance; //angle correspondant
        rotation(image, M_PI * (angle) / 180); //rotation definitive
}
