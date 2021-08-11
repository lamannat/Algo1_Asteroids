#include "graficador.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "config.h"
#include "vectores.h"

#define COLUMNAS 2

struct sprite{
	char nombre[10];
	uint16_t n;
	//float **coords;
	float coords[MAX_COORDENADAS][2];
};

typedef struct sprite sprite_t;


typedef struct graficador {
	SDL_Renderer *r;
	sprite_t *sprite;
	size_t n; //cantidad de sprites
}graficador_t;


static graficador_t *g = NULL;


static sprite_t * graficador_cargar(graficador_t *g, FILE *f){

	sprite_t *aux = malloc(sizeof(sprite_t));
	if(aux == NULL)
		return NULL;

	sprite_t *aux2 = NULL;

	size_t j = 0;

	while((fread(aux[j].nombre, sizeof(char), 10, f)) == 10){

		fread(&(aux[j].n), sizeof(uint16_t), 1, f);

		fread(aux[j].coords, 2*sizeof(float), aux[j].n, f);

		j++;

		aux2 = realloc(aux, (j+1)*sizeof(sprite_t)); //va a pedir sizeof(sprite_t) memoria de mas en la ultima lectura

		if(aux2 == NULL){
			free(aux);
			return NULL;
		}

		aux = aux2;
	}
	g -> n = j; //7 sprites, del 0 al 6
	return aux;
}

bool graficador_inicializar(const char *fn, SDL_Renderer *r){

	FILE *f;

	if((f = fopen(fn, "rb")) == NULL)
		return false;

	g = malloc(sizeof(graficador_t));

	if (g == NULL){
		fclose(f);
		return false;
	}

	g->r = r;

	if((g->sprite = graficador_cargar(g, f)) == NULL){
		fclose(f);
		free(g);
		return false;
	}

	fclose(f);

	return true;
}

void graficador_finalizar(){

	free(g->sprite);
	free(g);
	g = NULL;
}


bool graficador_dibujar(const char *nombre, float escala, float x, float y, float angulo){

	graficador_ajustar_variables(&x, &y);

	for(size_t i = 0; i < (g->n); i++){

		if(!strcmp((g -> sprite[i].nombre), nombre)){

			float **v = vector_desde_matriz(g->sprite[i].coords, g -> sprite[i].n);

			if(v == NULL)
				return false;

			vector_rotar(v, g->sprite[i].n, angulo); //no uso trasladar ni redimensionar_vector para evitar las iteraciones que suponen;

			for(size_t j = 0; j < (g -> sprite[i].n)-1; j++){
				SDL_RenderDrawLine(
				g->r,
				v[j][0] * escala + x,
				v[j][1] * escala + VENTANA_ALTO-y,
				v[j+1][0] * escala + x,
				v[j+1][1] * escala + VENTANA_ALTO-y
				);
			}

			vector_destruir(v, g -> sprite[i].n, 2);

			return true;	
		}
	}


	return false;	
}


void graficador_ajustar_variables(float *x, float *y){

	int h;
	int w;

	SDL_GetRendererOutputSize(g -> r, &w, &h);

	while ((*x < 0) || (*x > w)){
		if(*x > w)
			*x -= w;
		else
			*x += w;
	}

	while ((*y < 0) || (*y > h)){
		if(*y > h)
			*y -= h;
		else
			*y += h;
	}
}