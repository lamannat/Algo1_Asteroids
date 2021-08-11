#include "asteroide.h"
#include <stdio.h>
#include <math.h>
#include "config.h"
#include "graficador.h"
#include "modulo_asteroids.h"
#include "vectores.h"


static const char *sprites[] = {"ROCK1", "ROCK2", "ROCK3", "ROCK4"};

enum asteroides{
	AST1,
	AST2,
	AST3,
	AST4
};

struct asteroide{
	float x;
	float y;
	float vx;
	float vy;
	float angulo;
	int radio;
	enum asteroides clase;

};

asteroide_t *asteroide_crear(float x, float y, int radio){

	asteroide_t *v = NULL;
	v = malloc(sizeof(asteroide_t));

	if(v == NULL)
		return NULL;

	v->x = x;
	v->y = y;
	v->angulo = generar_random_en_margen(0, 2*PI);
	v->radio = radio;

	float velocidad = generar_random_en_margen((1000/v->radio)-100, (1000/v->radio)+100);
	float angulo = generar_random_en_margen(0, 2*PI);

	v->vx = velocidad * cos(angulo);
	v->vy = velocidad * sin(angulo);

	v->clase = rand() % 4;	

	return v;
}

void asteroide_destruir(void *v){

	free(v);
}

bool asteroide_mover(asteroide_t *x, float dt){

	graficador_ajustar_variables(&(x->x), &(x->y));

	x->x = computar_posicion(x->x, x->vx, dt);
	x->y = computar_posicion(x->y, x->vy, dt); 

	return true;
}


bool asteroide_dibujar(const asteroide_t *x){

	return graficador_dibujar(sprites[x->clase], x->radio, x->x, x->y, x->angulo);
}

static float calcular_distancia(float x1, float x2, float y1, float y2){

	return sqrt((x2-x1)*(x2-x1) + (y2-y1)*(y2-y1));
}

bool asteroide_colisiono(const asteroide_t *ast, float x, float y, float radio){

	float x1 = x, x2 = ast->x, y1 = y, y2 = ast->y;
	
	/*graficador_ajustar_variables(&x1, &y1);
	graficador_ajustar_variables(&x2, &y2);*/

	float distancia = calcular_distancia(x1, x2, y1, y2);

	return distancia < (radio + ast->radio);

}

void asteroide_get_coordenadas(const asteroide_t *v, float *x, float *y){

	*x = v->x;
	*y = v->y;
}

int asteroide_get_radio(const asteroide_t *ast){

	return ast->radio;
}