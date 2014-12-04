CC=clang

CPPFLAGS= `pkg-config --cflags sdl gtk+-2.0`
CFLAGS= -Wall -Wextra  -std=c99 -O3
LDFLAGS=
LDLIBS=`pkg-config --libs sdl gtk+-2.0` -lSDL_image -lm

SRC= Chargement/load.c Pretraitement/pixel_operations.c Pretraitement/pretraitement.c Pretraitement/rotation.c Extraction/extract_text_bloc.c Extraction/extraction_operations.c main.c

OBJ= ${SRC:.c=.o}

all: main

main: ${OBJ}

clean:
	  rm -f *~ *.o */*.o .*.swp *.swp */.*.swp */*.swp Result/*
	  rm -f main

#
