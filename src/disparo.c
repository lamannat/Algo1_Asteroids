#include "disparo.h"
#include "graficador.h"
#include "modulo_asteroids.h"
#include "vectores.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "config.h"


struct disparo{
	float x;
	float y;
	float vx;
	float vy;
	double angulo;
	float tiempo;
};


disparo_t *disparo_crear(float x, float y, float angulo){

	disparo_t *disp = NULL;
	disp = malloc(sizeof(disparo_t));

	disp->x = x;
	disp->y = y;
	disp->angulo = angulo;
	disp->vx = VELOCIDAD * cos(disp->angulo);
	disp->vy = VELOCIDAD * sin(-disp->angulo);
	disp->tiempo = TIEMPO;

	return disp;
}

void disparo_destruir(void *v){

	free(v);
}

bool disparo_mover(disparo_t *x, float dt){

	graficador_ajustar_variables(&(x->x), &(x->y));

	x->tiempo -= dt;

	x->x = computar_posicion(x->x, x->vx, dt);
	x->y = computar_posicion(x->y, x->vy, dt);

	return true;
}


bool disparo_dibujar(const disparo_t *x){

	if(!(graficador_dibujar(S_DISPARO, 10, x->x, x->y, x->angulo)))
		return false;	

	return true;
}	

bool disparo_queda_tiempo(disparo_t *x){

	return x->tiempo > 0;
}

void disparo_get_coordenadas(const disparo_t *v, float *x, float *y){

	*x = v->x;
	*y = v->y;
}