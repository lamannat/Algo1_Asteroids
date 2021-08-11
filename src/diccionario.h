#ifndef _DICCIONARIO_LANDER_H_
#define _DICCIONARIO_LANDER_H_

#include <SDL2/SDL.h>
#include <string.h>
#include "caracteres.h"
#include "config.h"

//Funcion que recibe una cadena de caracteres cadena y grafica por medio de SDL2 dicha cadena en la posicion X e Y con un tamaño escala
void dibujar_cadena(const char cadena[], int x, int y, float escala, SDL_Renderer *renderer);


#endif