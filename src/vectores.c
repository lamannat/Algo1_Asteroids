#include "vectores.h"
#include <stdio.h>
#include <math.h>
#include "config.h"


float **vector_desde_matriz(float m[][2], size_t n){

	float **v;
	v = crear_vector(n, 2);
	if(v == NULL) return NULL;

	for (int i=0; i<n; i++){
		for (int j=0; j<2; j++)
			v[i][j] =  m[i][j];
	}

	return v;
}

float **crear_vector(size_t filas, size_t columnas){

	float **v;
	v = (float **)malloc(sizeof(float *) * filas);

	if(v == NULL) 
		return NULL;

	for (size_t i=0; i<filas; i++){
		v[i] = (float *)malloc(sizeof(float) * columnas);
		if(v[i]==NULL){
			vector_destruir(v, i, columnas);
			return NULL;
		}
	}

	return v;

}

float **vector_densificar(float **v, size_t nv, size_t nn, float margen){

	float yaux;
	float xaux;
	float** vd;

	vd = crear_vector(nn, 2);
	if (vd == NULL) return NULL;

	for (int i=0; i<nn; i++){
		for(int j=0; i<nv && j<2; j++)
			vd[i][j]=v[i][j];
		
	}

	for (int i=nv; i<nn; i++){
		
		xaux = generar_random_en_margen(v[0][0], v[nv-1][0]);
		vd[i][0] = xaux;
		yaux = generar_y(xaux, v, nv);
		vd[i][1] = generar_random_en_margen(yaux-margen, yaux+margen);
	}

	ordenar_vector(vd, nn);

	return vd;
}

float generar_random_en_margen(float a, float b){

	float rango = b-a;

	return (((float)rand()/RAND_MAX) * rango + (a));
}

void ordenar_vector(float **v, size_t n){
	
	int i, j, k;
	
    for (i = 0; i < n - 1; i++){
    
        for (k = i, j = i + 1; j < n; j++){
            if (v[j][0] < v[k][0])
                k = j;
        }
        if (k != i){
        	swap(&v[i], &v[k]);
		}    
    }	
}

float generar_y(float x, float **v, size_t n){

	float xmax = v[n-1][0], xmin = v[0][0];
	float ymax = v[n-1][1], ymin = v[0][1];
	float yaux;
	float pendiente;
	
	for (int i=0; i<n-1; i++){
		if (v[i+1][0]>=x){
			xmin=v[i][0];
			ymin=v[i][1];
			xmax=v[i+1][0];
			ymax=v[i+1][1];
			break;
		} 
	}

	pendiente = (ymax-ymin)/(xmax-xmin);
	yaux = pendiente*x+((-1)*(pendiente)*xmin+ymin);

	return yaux;

	//return generar_random_en_margen(yaux-margen, yaux+margen);
	
}

void vector_destruir(float ** v, size_t n, size_t m){

	for (int i=0; i<n; i++){
		free(v[i]);
	}	

	free(v);	
}

void swap(float **a, float **b) {

	float *c;
	c = *a;
	*a = *b;
	*b = c;
}

void imprimir_coordenadas(float **coordenadas, int n, char mensaje[]){

	printf("%s \n\n", mensaje);
	for (int i=0; i<n; i++)
		printf("%f;%f\n",coordenadas[i][0],coordenadas[i][1]);
	printf("\n\n");
}

bool vector_esta_arriba(float **v, size_t n, float x, float y){
	float xmax = v[n-1][0], xmin = v[0][0];
	float ymax = v[n-1][1], ymin = v[0][1];

	for (int i=0; i<n-1; i++){
		if (v[i+1][0]>=x){
			xmin=v[i][0];
			ymin=v[i][1];
			xmax=v[i+1][0];
			ymax=v[i+1][1];
			break;
		} 
	}
	return y>(ymax-ymin)/(xmax-xmin)*x+((-1)*((ymax-ymin)/(xmax-xmin))*xmin+ymin);
}

void vector_trasladar(float **v, size_t n, float dx, float dy){

	for (size_t i=0; i<n; i++){
		v[i][0]+=dx;
		v[i][1]+=dy;
	}
}


void vector_rotar(float **v, size_t n, double rad){

	float cosx=cos(rad), sinx=sin(rad);
	float xo=0;
	for (size_t i=0; i<n; i++){
		xo=v[i][0];
		v[i][0]=xo*cosx-v[i][1]*sinx;
		v[i][1]=xo*sinx+v[i][1]*cosx;
	}	
}

void redimensionar_vector(float **v, size_t n, float x){

	for(int i=0; i<n; i++){
		for(int j=0; j<2; j++)
			v[i][j]*=x;
	}
}
