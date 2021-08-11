#ifndef _VECTORES_
#define _VECTORES_

#include <stdlib.h>
#include <stdbool.h>

//Recibe una matriz de 2 columnas y n filas y devuelve un puntero a un vector dinamico de n elementos con los mismos datos de tipo float.
//que la matriz entrante
float **vector_desde_matriz(float m[][2], size_t n);

//Recibe un valor de filas y uno de columnas y crea un puntero a un vector dinamico
float **crear_vector(size_t filas, size_t columnas);

//Recibe vector dinamico v de nv coordenadas en R2 y
//devueve un nuevo vector dinamico con nn coordenadas generado con un margen de ±margen con respecto a las rectas definidas por v.
float **vector_densificar(float **v, size_t nv, size_t nn, float margen);

//Funcion que genera un numero real aleatorio entre los valores a y b
float generar_random_en_margen(float a, float b);

//Recibe un puntero v a un vector dinamico de n coordenadas y lo ordena segun coordenada X creciente.
void ordenar_vector(float **v, size_t n);

//Recibe una coordenada X (que debe estar en el intervalo de coordenadas x del vector dinamico v de n coordenadas)
//y devuelve la coordenada Y perteneciente a la recta del vector dinamico v
float generar_y(float x, float **v, size_t n);

//Libera un puntero v a un vector dinamico de n elementos apuntados a m datos de tipo float.
void vector_destruir(float ** v, size_t n, size_t m);

//Recibe las direcciones de memoria de dos vectores dinamicos y cambia su contenido por interfaz
void swap(float **a, float **b);

//Funcion que recibe un valor de coordenada X e Y y devuelve true en caso de que el punto (X,Y) se encuentre por encima de la 
//recta trazada por los punto del vector dinamico V de n coordenadas. Devuelve false en caso contrario.
bool vector_esta_arriba(float **v, size_t n, float x, float y);

//Funcion que rota rad radianes los puntos del vector dinamico v de n coordenadas
void vector_rotar(float **v, size_t n, double rad);

//Funcion que traslada dx puntos en X y dy puntos en Y los puntos del vector dinamico v de n coordenadas
void vector_trasladar(float **v, size_t n, float dx, float dy);

//Funcion que redimensiona a X los puntos del vector dinamico v de n coordenadas
void redimensionar_vector(float **v, size_t n, float x);

#endif