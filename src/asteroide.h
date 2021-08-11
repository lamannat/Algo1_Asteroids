#ifndef _ASTEROIDE_H_
#define _ASTEROIDE_H_

#include <stdbool.h>
#include <stdlib.h>

struct asteroide;
typedef struct asteroide asteroide_t;


asteroide_t *asteroide_crear(float x, float y, int radio);

void asteroide_destruir(void *v);

bool asteroide_mover(asteroide_t *x, float dt);

bool asteroide_dibujar(const asteroide_t *x);

bool asteroide_colisiono(const asteroide_t *ast, float x, float y, float radio);

void asteroide_get_coordenadas(const asteroide_t *v, float *x, float *y);

int asteroide_get_radio(const asteroide_t *ast);

#endif