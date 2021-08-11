#ifndef _NAVE_H_
#define _NAVE_H_

#include <stdbool.h>

#define ESCALA 1
#define SPRITE_NAVE "SHIP"
#define SPRITE_CHORRO "THURST"
#define IMPULSO 1000


struct nave;
typedef struct nave nave_t;

nave_t *nave_crear(float x, float y);

void nave_destruir(nave_t *v);

void nave_decrementar_angulo(nave_t *v);

void nave_incrementar_angulo(nave_t *v);

void nave_mover(nave_t *x, float dt);

bool nave_dibujar(const nave_t *x);

void nave_impulsar(nave_t *v);

void nave_get_coordenadas(const nave_t *v, float *x, float *y);

void nave_get_angulo(const nave_t *v, float *ang);


#endif 
