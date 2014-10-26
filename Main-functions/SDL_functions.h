# ifndef SDL_functions_H_
# define SDL_functions_H_

void wait_for_Keypressed(void);
void init_sdl(void);
SDL_Surface* load_image(char *path);
SDL_Surface* display_image(SDL_Surface *img);

# endif
