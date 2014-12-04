# ifndef STDLIB_STDIO
# define STDLIB_STDIO

# include <stdlib.h>
# include <stdio.h>
# include <SDL/SDL.h>
# include <SDL/SDL_image.h>
# include <math.h>
# include <gtk/gtk.h>

# endif

#ifndef EXTRACTION_OPERATIONS_H_
#define EXTRACTION_OPERATIONS_H_

#include "../Pretraitement/pixel_operations.h"
#include "extract_text_bloc.h"

struct bloc {
  int startX;
  int startY;
  int endX;
  int endY;
};

struct lineInfo {
  int height;
  int endLineX;
  int startX;
  int startY;
  int nbChar;
  struct  charInfo  *charInfoArray;
};

struct charInfo {
  int startX;
  int startY;
  int endX;
  int endY;
};

struct  point {
  int startY;
  int endY;
};

//Cette fonction retourne un pointeur vers un tableau d'une seule dimension
//de taille la hauteur du bloc B et qui contient le nombre de pixel noirs de
//chaque ligne du bloc
int *nbLinesZero(SDL_Surface *img, struct bloc B);

//Cette fonction retourne un entier qui représente le nombre de ligne extistant
//dans le bloc B passé en paramètre
int nbLinesOne(SDL_Surface *img, struct bloc B);

//Cette fonction retourne un entier qui présente la fin de la ligne 
//qui a les coordonnés passé en paramètres dans le bloc B
int EndLine(SDL_Surface *img, struct bloc B, int lineStartY, int lineHeight);

//Cette fonction détermine le nombre de cractères dans une ligne (les infos
//de la ligne sont passés en paramètres)
int nbChar(SDL_Surface  *img, int lineStartX, int lineStartY, int lineEndX, int lineHeight);

//Cette fonction retourne un entier qui représente la coordonnée x
//du premier pixel noir du premier charactère de la ligne
//(coordonnées de la ligne passé en paramètres)
int CharStartX(SDL_Surface  *img, int charCounterX,  int lineHeight, int lineStartY,  int endLine);

//
int CharEndX(SDL_Surface *img, int charStartX, int lineStartY, int lineHeight, int endLine);

//
struct point  CharStartEndY(SDL_Surface *img,  int charStartX, int charEndX, int lineStartY, int lineHeight);

//Cette fonction retourne un pointeur sur un tableau de structure,
//dans chaque case on trouve une structure charInfo qui contient des
//informations sur le caractère de la ligne. 
struct charInfo *CharInfoArray(SDL_Surface  *img, int lineStartX, int lineStartY, int lineEndX, int lineHeight);

//Cette fonction retourne un pointeur sur un tableau d'une dimension.
//La taille de ce tableau est le nombre de ligne du bloc B passé en paramètre
//Il contient à chaque case une structure qui contient des infos des lignes.
struct lineInfo *linesInfoArray(SDL_Surface *img, struct bloc B);

//
//void SegmentVertical(SDL_Surface *img, int lineStartY, int lineHeight, int charStartX);
void SegmentVertical(SDL_Surface  *img, int charX,  int charStartY, int charEndY);

//
void SegmentHorizontal(SDL_Surface  *img, int charY,  int charStartX, int charEndX);

//
//void SegmentChar(SDL_Surface  *img, int charCounterX, int lineEndX, int lineStartY, int lineHeight);

//Cette fonction permet de segmenter les lignes (déssiner une ligne rouge
//au dessus et en dessous de chaque ligne
void SegmentLines(SDL_Surface  *img, TextBlocList *tb );

#endif
