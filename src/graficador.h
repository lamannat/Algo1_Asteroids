#ifndef GRAFICADOR_H
#define GRAFICADOR_H

#include <SDL2/SDL.h>
#include <stdbool.h>

#define MAX_COORDENADAS 50

bool graficador_inicializar(const char *fn, SDL_Renderer *r);

bool graficador_dibujar(const char *nombre, float escala, float x, float y, float angulo);

void graficador_finalizar();

void graficador_ajustar_variables(float *x, float *y);

#endif