CC=clang

 CPPFLAGS= `pkg-config --cflags sdl`
 CFLAGS= -Wall -Wextra -std=c99 -O3
 LDFLAGS=
 LDLIBS= -lm `pkg-config --libs sdl` -lSDL_image

SRC= neuron.c
OBJ= ${SRC:.c=.o}

all: neuron

main: ${OBJ}

clean:
	rm -f *~ *.o
	rm -f neuron 
