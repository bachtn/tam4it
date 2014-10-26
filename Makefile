CC=clang
 
 CPPFLAGS= `pkg-config --cflags sdl`
 CFLAGS= -Wall -Wextra -std=c99 -O3
 LDFLAGS=
 LDLIBS= -lm `pkg-config --libs sdl` -lSDL_image
  
SRC= Extraction/extract_char.c Extraction/extraction_operations.c Extraction/pixel_operations.c Main-functions/main_functions.c Main-functions/SDl_functions.c main.c 
OBJ= ${SRC:.c=.o}
	 
all: main
	 
main: ${OBJ}
	 
clean:
	rm -f *~ *.o
	rm -f main
			 

