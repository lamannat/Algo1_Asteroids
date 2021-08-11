#ifndef _LISTA_H_
#define _LISTA_H_

#include <stdbool.h>

struct lista;
typedef struct lista lista_t;

lista_t *lista_crear();
void lista_destruir(lista_t *l, void (*destruir_dato)(void *d));
bool lista_es_vacia(const lista_t *l);
bool lista_insertar_comienzo(lista_t *l, void *d);
bool lista_insertar_final(lista_t *l, void *d);
void *lista_extraer_primero(lista_t *l);
void *lista_buscar(const lista_t *l, const void *d, int (*cmp)(const void *a, const void *b));
void lista_recorrer(const lista_t *l, bool (*visitar)(void *dato, void *extra), void *extra);

//iterador TDA

struct iterador;
typedef struct iterador iterador_t;

iterador_t *iterador_crear(lista_t *l);
void iterador_destruir(iterador_t *ir);
void *iterador_actual(const iterador_t *ir);
bool iterador_siguiente(iterador_t *ir);
bool iterador_termino(const iterador_t *ir);
void *iterador_eliminar_actual(iterador_t *ir);
bool iterador_insertar(iterador_t *ir, void *dato);

#endif
