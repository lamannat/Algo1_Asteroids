#include "nave.h"
#include <stdlib.h>
#include <stdio.h>
#include "config.h"
#include "graficador.h"
#include "modulo_asteroids.h"

struct nave{
	float x;
	float y;
	float vx;
	float vy;
	float angulo;
	float potencia;
};


nave_t *nave_crear(float x, float y){

	nave_t *v = NULL;
	v = malloc(sizeof(nave_t));
	if(v == NULL)
		return NULL;

	v->x = x;
	v->y = y;
	v->vx = NAVE_VX_INICIAL;
	v->vy = NAVE_VY_INICIAL;
	v->angulo = NAVE_ANGULO_INICIAL;
	v->potencia = NAVE_POTENCIA_INICIAL;

	return v;
}

void nave_destruir(nave_t *v){

	free(v);
}

void nave_mover(nave_t *x, float dt){

	graficador_ajustar_variables(&(x->x), &(x->y));

	x->potencia *= 0.90; // -10%
	x->vx *= 0.99;// -1%
	x->vy *= 0.99;// -1%

	int aceleracion_x = x->potencia * (cos(x->angulo));
	int aceleracion_y = x->potencia * (sin(-x->angulo));

	x->x = computar_posicion(x->x, x->vx, dt);
	x->y = computar_posicion(x->y, x->vy, dt);

	x->vx = computar_velocidad(x->vx, aceleracion_x, dt);
	x->vy = computar_velocidad(x->vy, aceleracion_y, dt);
}

/*Por cada centésima de segundo
la potencia debe reducirse un 10 % y la velocidad un 1 %, es decir, hay una componente
friccional en el movimiento y tanto potencia como velocidad decaen exponencialmente*/

bool nave_dibujar(const nave_t *x){

	if(!(graficador_dibujar(SPRITE_NAVE, ESCALA, x->x, x->y, x->angulo)))
		return false;

	if(x->potencia > 1 && (int)(x->potencia)%2){
		if(!(graficador_dibujar(SPRITE_CHORRO, ESCALA, x->x, x->y, x->angulo)))
			return false;
	}

	return true;
}

void nave_incrementar_angulo(nave_t *v){

	v->angulo += NAVE_ROTACION_PASO; 
}

void nave_decrementar_angulo(nave_t *v){

	v->angulo -= NAVE_ROTACION_PASO;
}

void nave_impulsar(nave_t *v){

	v->potencia += IMPULSO;
}

void nave_get_coordenadas(const nave_t *v, float *x, float *y){

	*x = v->x;
	*y = v->y;
}

void nave_get_angulo(const nave_t *v, float *ang){

	*ang = v->angulo;
}