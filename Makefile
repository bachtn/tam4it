CC=clang

 CPPFLAGS=
 CFLAGS= -Wall -Wextra -std=c99 -O3
 LDFLAGS=
 LDLIBS= -lm `pkg-config --libs sdl` -lSDL_image
  
SRC=Pre-traitement/pixel_operations.c Extraction/extract_text_bloc.c Chargement/load.c  Extraction/extract_char.c Extraction/extraction_operations.c Extraction/pixel_operations.c Main-functions/SDl_functions.c main.c 

OBJ= ${SRC:.c=.o}

all: main

main: ${OBJ}

clean:
	rm -f *~ *.o */*.o *.swp */*.swp
	rm -f main
