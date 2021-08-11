#ifndef _AST_H_
#define _AST_H_

#include "asteroide.h"
#include "lista.h"


bool dividir_asteroide(iterador_t *ir_asteroides);
void computar_puntaje(int radio, int *puntos);
bool centro_esta_libre(lista_t *asteroides, int radio);
double computar_posicion(double pi, double vi, double dt);
double computar_velocidad(double vi, double a, double dt);

#endif 