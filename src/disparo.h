#ifndef _DISPARO_H_
#define _DISPARO_H_

#include <stdbool.h>

#define VELOCIDAD 1000
#define S_DISPARO "SHOT"
#define TIEMPO 0.7

struct disparo;
typedef struct disparo disparo_t;


disparo_t *disparo_crear(float x, float y, float angulo);

void disparo_destruir(void *v);

bool disparo_mover(disparo_t *x, float dt);

bool disparo_dibujar(const disparo_t *x);

bool disparo_queda_tiempo(disparo_t *x);

void disparo_get_coordenadas(const disparo_t *v, float *x, float *y);


#endif