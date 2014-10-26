CC=clang

 CPPFLAGS=
 CFLAGS= -Wall -Wextra -std=c99 -O3
 LDFLAGS=
 LDLIBS= -lm `pkg-config --libs sdl` -lSDL_image
<<<<<<< HEAD
  
SRC= Extraction/extract_char.c Extraction/extraction_operations.c Extraction/pixel_operations.c Main-functions/main_functions.c Main-functions/SDl_functions.c main.c 
=======

SRC= Chargement/load.c  Extraction/extract_text_bloc.c Pre-traitement/pixel_operations.c main.c 
>>>>>>> a75289d416dd767538c4ff5030483bcd649f28e2
OBJ= ${SRC:.c=.o}

all: main

main: ${OBJ}

clean:
	rm -f *~ *.o */*.o *.swp */*.swp
	rm -f main
