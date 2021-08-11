#include "lista.h"
#include <stdlib.h>

struct nodo {
	struct nodo *sig;
	void *dato;
};

struct lista {
	struct nodo *prim;
	// struct nodo *ult;
};


static struct nodo *nodo_crear(void *d) {
	struct nodo *n = malloc(sizeof(struct nodo));
	if(n == NULL)
		return NULL;

	n->sig = NULL;
	n->dato = d;

	return n;
}

lista_t *lista_crear() {
	lista_t *l = malloc(sizeof(lista_t));
	if(l == NULL)
		return NULL;

	l->prim = NULL;
	return l;
}


void lista_destruir(lista_t *l, void (*destruir_dato)(void *d)) {
	struct nodo *n = l->prim;
	while(n != NULL) {
		struct nodo *sig = n->sig;

		if(destruir_dato != NULL)
			destruir_dato(n->dato);

		free(n);

		n = sig;
	}

	free(l);
}

bool lista_es_vacia(const lista_t *l) {
	return l->prim == NULL;
}

bool lista_insertar_comienzo(lista_t *l, void *d) {
	struct nodo *n = nodo_crear(d);
	if(n == NULL)
		return false;

	n->sig = l->prim;
	l->prim = n;

	return true;
}

bool lista_insertar_final(lista_t *l, void *d) {
	struct nodo *n = nodo_crear(d);
	if(n == NULL) return false;

	// Si está vacía inserto al principio:
	if(l->prim == NULL) {
		l->prim = n;
		return true;
	}

	// La lista no estaba vacía:
	struct nodo *aux = l->prim;
	while(aux->sig != NULL)
		aux = aux->sig;

	aux->sig = n;

	return true;
}

void *lista_extraer_primero(lista_t *l) {
	if(lista_es_vacia(l))
		return NULL;

	struct nodo *n = l->prim;
	void *d = n->dato;

	l->prim = n->sig;
	free(n);

	return d;
}

void *lista_buscar(const lista_t *l, const void *d, int (*cmp)(const void *a, const void *b)) {

	struct nodo *n = l->prim;
	while(n != NULL) {
		if(cmp(n->dato, d) == 0)
			return n->dato;

		n = n->sig;
	}

	return NULL;
}


//iterador TDA

struct iterador{

	lista_t *l;
	struct nodo *nodo;
	struct nodo *anterior;
};

iterador_t *iterador_crear(lista_t *l){

	iterador_t *ir = NULL;
	ir = malloc(sizeof(iterador_t));
	if (ir == NULL)
		return NULL;

	ir->nodo = l->prim;
	ir->anterior = NULL;
	ir->l = l;

	return ir;
}

void iterador_destruir(iterador_t *ir){

	free(ir);
}

void *iterador_actual(const iterador_t *ir){

	if(iterador_termino(ir)){
		return NULL;
	}

	return ir->nodo->dato;
}

bool iterador_siguiente(iterador_t *ir){

	if(ir->nodo == NULL || ir->nodo->sig == NULL){
		ir->nodo = NULL;
		return false;
	}

	ir->anterior = ir->nodo;
	ir->nodo = ir->nodo->sig;
	return true;
}

bool iterador_termino(const iterador_t *ir){

	return ir->nodo == NULL;
}

void *iterador_eliminar_actual(iterador_t *ir){

	struct nodo *n = ir->nodo;
	void *d;

	if(ir->anterior == NULL){
		ir->nodo = n->sig;
		d = lista_extraer_primero(ir->l);
		return d;
	}	

	ir->nodo = n->sig;
	ir->anterior->sig = n->sig;

	d = n->dato;
	free(n);
	return d;
}


bool iterador_insertar(iterador_t *ir, void *dato){

	struct nodo *n = nodo_crear(dato);
	if(n == NULL)
		return false;

	n->sig = ir->nodo->sig;
	ir->nodo->sig = n;

	return true;
}