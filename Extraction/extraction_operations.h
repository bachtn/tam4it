#ifndef STDLIB_STDIO
#define STDLIB_STDIO

#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <math.h>

#endif

#ifndef EXTRACTION_OPERATIONS_H_
#define EXTRACTION_OPERATIONS_H_

struct lineInfo
{
  int height;
  int endLine;
  int length;
  int x;
  int y;
};
//Cette fonction retourne un tableau unidimensionnel d'entier, sa taille
//est le hauteur de l'image. Dans chaque case, on trouve le nombre de pixel
//noir de chaque ligne de pixel
int *nbLinesZero(SDL_Surface *image);
//Cette fonction calcule le nombre de ligne du texte et le retourne
int nbLinesOne(SDL_Surface *image);
//Cette fonction permet de construire un tableau de structure.
//La taille du tableau est le nombre de ligne du texte. 
//Cette fonction calcule la hauteur de chaque ligne du texte et remplie les attribues de la structure lineInfo en utilisant d'autres fonctions.
struct lineInfo *linesInfoArray(SDL_Surface *image);
//Cette fonction retourne la coordonné X du premier pixel noir du caractère.
int CharacterStartXcoordinate(SDL_Surface *image, int lineHeight, int lineYcoordinate, int lineXcounterStart);
//Cette fonction retourne la coordonné du dernier pixel noir d'une ligne
int EndLine(SDL_Surface *image, int lineYcoordinate, int lineHeight, int endBloc);
//Cette fonction trace une ligne rouge au dessus et en dessous de chaque ligne.
void SegmentLines(SDL_Surface *image);
#endif
