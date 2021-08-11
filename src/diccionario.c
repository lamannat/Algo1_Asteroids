#include "diccionario.h"

typedef const int (*matrices_t)[2];

typedef struct letras{

	char caracter;
	int n;
	matrices_t matriz;
	
}caracteres_t;


static caracteres_t vector[] = {{'A', 7, caracter_a}, {'B', 12, caracter_b}, {'C', 4, caracter_c}, {'D', 7, caracter_d},{'E', 7, caracter_e},
						{'F', 6, caracter_f}, {'G', 7, caracter_g}, {'H', 6, caracter_h}, {'I', 6, caracter_i}, {'J', 4, caracter_j},
						{'K', 6, caracter_k}, {'L', 3, caracter_l}, {'M', 5, caracter_m}, {'N', 4, caracter_n}, {'O', 5, caracter_o},
						{'P', 5, caracter_p}, {'Q', 9, caracter_q}, {'R', 7, caracter_r}, {'S', 6, caracter_s}, {'T', 4, caracter_t},
						{'U', 4, caracter_u}, {'V', 3, caracter_v}, {'W', 5, caracter_w}, {'X', 5, caracter_x}, {'Y', 5, caracter_y},
						{'Z', 4, caracter_z}, {'0', 5, caracter_0}, {'1', 2, caracter_1}, {'2', 6, caracter_2}, {'3', 7, caracter_3},
						{'4', 5, caracter_4}, {'5', 6, caracter_5}, {'6', 5, caracter_6}, {'7', 3, caracter_7}, {'8', 7, caracter_8},
						{'9', 5, caracter_9}, {'<', 5, caracter_derecha}, {'>', 5, caracter_izquierda}, {'^', 5, caracter_arriba},
						{'v', 5, caracter_abajo},	{' ', 1, caracter_espacio}};

static size_t largo_vector = sizeof(vector)/sizeof(vector[0]);

static size_t buscar_caracter(char caracter){

	for (size_t j=0; j<largo_vector; j++){
			if (caracter==vector[j].caracter)
				return j;
	}
	return 40;
}

static void dibujar_caracter(const matrices_t vec, size_t n, int x, int y, float escala, SDL_Renderer *renderer){

 for(size_t j = 0; j < (n-1); j++)
			SDL_RenderDrawLine(
				renderer,
				vec[j][0]*escala+x,
				vec[j][1]*-escala+VENTANA_ALTO-y,
				vec[j+1][0]*escala+x,
				vec[j+1][1]*-escala+VENTANA_ALTO-y	
			);
}

void dibujar_cadena(const char cadena[], int x, int y, float escala, SDL_Renderer *renderer){

	size_t subindice = 0;
	for (size_t i = 0; cadena[i] != '\0'; i++){
		subindice = buscar_caracter(cadena[i]);
		dibujar_caracter(vector[subindice].matriz, vector[subindice].n, x, y, escala, renderer);
		x+=CARACTER_ANCHO*escala;
	}

}

