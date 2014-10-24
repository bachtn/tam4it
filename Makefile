CC=clang
 
 CPPFLAGS= `pkg-config --cflags sdl`
 CFLAGS= -Wall -Wextra -std=c99 -O3
 LDFLAGS=
 LDLIBS= -lm `pkg-config --libs sdl` -lSDL_image
  
SRC= Extraction/extract_char.c main.c 
OBJ= ${SRC:.c=.o}
	 
all: main
	 
main: ${OBJ}
	 
clean:
	rm -f *~ *.o
	rm -f main
			 

