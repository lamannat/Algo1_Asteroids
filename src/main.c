#include <SDL2/SDL.h>
#include <time.h>
#include <stdio.h>
#include "config.h"
#include "nave.h"
#include "diccionario.h"
#include "graficador.h"
#include "asteroide.h"
#include "disparo.h"
#include "lista.h"
#include "modulo_asteroids.h"

#define STRING_MAX 50

//Crea cantidad_ast asteroides y los inserta en la lista asteroides
bool crear_asteroides(lista_t *asteroides, int cantidad_ast);

//comprueba si la nave fue destruida, en caso afirmativo crea una nueva nave en la posicion inicial en caso de que el centro se encuentre libre de asteroides
bool comprobar_creacion_nave(nave_t **nave, lista_t *asteroides, float dt, int *contador_ciclos, int *inmunidad);

//comprueba si hay asteroides restantes, en caso negativo crea nuevos asteroides agregando 2 mas que la ronda anterior
bool comprobar_creacion_asteroides(lista_t *asteroides, int *cantidad_ast);

void mover_objetos(nave_t *nave, lista_t *asteroides, lista_t *disparos, float dt);

void dibujar_objetos(nave_t *nave, lista_t *asteroides, lista_t *disparos, float dt, int *contador_ciclos, int *inmunidad);

void dibujar_interfaz(int puntos, int high_score, int vidas, SDL_Renderer *renderer);

//verifica si la nave impacto con alguno asteroide
bool verificar_impacto_nave(nave_t **nave, lista_t *asteroides, int *vidas, int *puntos, int inmunidad, float dt);

//verifica si las coordenadas xy se encuentran dentro del radio de algun asteroide
bool verificar_colision(float x, float y, lista_t *asteroides, int *puntos, bool *memcheck, int radio); 

//verifica si algun disparo impacto contra algun asteroide
bool verificar_impacto_disparos(lista_t *disparos, lista_t *asteroides, int *puntos);


int main() {

	srand(time(NULL));

	SDL_Init(SDL_INIT_VIDEO);

	SDL_Window *window;
	SDL_Renderer *renderer;
	SDL_Event event;

	SDL_CreateWindowAndRenderer(VENTANA_ANCHO, VENTANA_ALTO, 0, &window, &renderer);
	SDL_SetWindowTitle(window, "Asteroids");

	int dormir = 0;

	// BEGIN código del alumno

	//nave
	nave_t *nave = NULL;//nave_crear(NAVE_X_INICIAL, NAVE_Y_INICIAL);
	float nx, ny;
	float nang;

	//asteroides
	lista_t *asteroides = NULL;
	int cantidad_ast = CANT_AST_INICIAL;

	//disparos
	disparo_t *disp;
	lista_t *disparos = NULL;

	//variables
	float paso_temporal = 1.0/JUEGO_FPS;
	int vidas;
	int puntos;
	int high_score = 0;
	int contador_ciclos = 0;
	int inmunidad = 0;//cuenta ciclos para calcular el tiempo de inmunidad restante
	bool partida_en_curso = false; //true = quedan vidas restantes, false = no quedan vidas restantes
	bool juego_nuevo = false; //true = comenzar nueva partida, false = partida en curso o no se presiono space

	char string_aux[STRING_MAX];

	graficador_inicializar("sprites.bin", renderer);

	// END código del alumno

	unsigned int ticks = SDL_GetTicks();

	while(1) {

		if(SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT)
				break;
	    		if (event.type == SDL_KEYDOWN) {
				// BEGIN código del alumno
				switch(event.key.keysym.sym) {

					case SDLK_UP:

						if(nave != NULL)
							nave_impulsar(nave);
						break;

					case SDLK_RIGHT:

						if(nave != NULL)
							nave_incrementar_angulo(nave);
						break;

					case SDLK_LEFT:

						if(nave != NULL)
							nave_decrementar_angulo(nave);
						break;

					case SDLK_SPACE:

						if(nave != NULL){

							nave_get_coordenadas(nave, &nx, &ny);
							nave_get_angulo(nave, &nang);
							disp = disparo_crear(nx, ny, nang);
							lista_insertar_final(disparos, disp);
							disp = NULL;
						}

						if(!partida_en_curso)
							juego_nuevo = true;

						break;
				}
				// END código del alumno
			}
			continue;

		}

        SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0x00);


		// BEGIN código del alumno
		if (juego_nuevo){

			vidas = VIDAS;
			nave = nave_crear(NAVE_X_INICIAL, NAVE_Y_INICIAL);
			asteroides = lista_crear();
			crear_asteroides(asteroides, CANT_AST_INICIAL);
			disparos = lista_crear();

			contador_ciclos = 0;
			puntos = 0;

			juego_nuevo = false;
			partida_en_curso = true;
		}

        if(partida_en_curso){

        	comprobar_creacion_nave(&nave, asteroides, paso_temporal, &contador_ciclos, &inmunidad);//no hay nave, quedan vidas
        	comprobar_creacion_asteroides(asteroides, &cantidad_ast);//no hay asteroides, creo nuevos con 2 adicionales a la ronda anterior

        	mover_objetos(nave, asteroides, disparos, paso_temporal);

        	dibujar_objetos(nave, asteroides, disparos, paso_temporal, &contador_ciclos, &inmunidad);
        	dibujar_interfaz(puntos, high_score, vidas, renderer);

        	verificar_impacto_nave(&nave, asteroides, &vidas, &puntos, inmunidad, paso_temporal);
        	verificar_impacto_disparos(disparos, asteroides, &puntos);

        	inmunidad ++;
        }
        else{

        	sprintf(string_aux, "%s", "ASTEROIDS");
   			dibujar_cadena(string_aux, 410, VENTANA_ALTO - 300, 3, renderer);


   			if(contador_ciclos * paso_temporal >= 0.5){
				sprintf(string_aux, "%s", "PRESIONE ESPACIO PARA INICIAR UN NUEVO JUEGO ");
    			dibujar_cadena(string_aux, 100,  VENTANA_ALTO - 400, 3, renderer);
				if(contador_ciclos * paso_temporal >= 1.5)
					contador_ciclos = 0;
			}
			contador_ciclos++;

        }

		if(partida_en_curso && vidas == 0){

			sprintf(string_aux, "%s", "GAME OVER");
   			dibujar_cadena(string_aux, 410, VENTANA_ALTO - 300, 3, renderer);
			sprintf(string_aux, "%s %d", "PUNTUACION", puntos);
   			dibujar_cadena(string_aux, 380, VENTANA_ALTO - 350, 3, renderer);

   			if (puntos > high_score)
   				high_score = puntos;

			
       		lista_destruir(asteroides, asteroide_destruir);
       		asteroides = NULL;
       		lista_destruir(disparos, disparo_destruir);
       		disparos = NULL;
     		
       		partida_en_curso = false;

       		dormir = 2500;
		}
	

		// END código del alumno


        SDL_RenderPresent(renderer);
		ticks = SDL_GetTicks() - ticks;
		if(dormir) {
			SDL_Delay(dormir);
			dormir = 0;
		}
		else if(ticks < 1000 / JUEGO_FPS)
			SDL_Delay(1000 / JUEGO_FPS - ticks);
		ticks = SDL_GetTicks();
	}

	// BEGIN código del alumno
	if(nave != NULL)
		nave_destruir(nave);

	if(asteroides != NULL)
		lista_destruir(asteroides, asteroide_destruir);

	if(disparos != NULL)
		lista_destruir(disparos, disparo_destruir);

	graficador_finalizar();
	
	// END código del alumno

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	SDL_Quit();
	
	return 0;
}

bool crear_asteroides(lista_t *asteroides, int cantidad_ast){

	asteroide_t *ast;

	for(size_t i = 0; i < cantidad_ast; i++){

		if(rand()%2){

			ast = asteroide_crear(0, rand()%VENTANA_ALTO, RADIO_ASTEROIDE);

			if(ast == NULL)
				return false;
		}

		else{
			ast = asteroide_crear(rand()%VENTANA_ANCHO, 0, RADIO_ASTEROIDE);

			if(ast == NULL)
				return false;
		}
				
		lista_insertar_final(asteroides, ast);
	}

	return true;
}

bool comprobar_creacion_nave(nave_t **nave, lista_t *asteroides, float dt, int *contador_ciclos, int *inmunidad){

	if((*nave) == NULL){ //choco contra un asteroide pero quedan vidas restantes

        if(((*contador_ciclos)*dt) >= SEGUNDOS_RESPAWN){
        	if(centro_esta_libre(asteroides, RADIO_NAVE)){
        		(*nave) = nave_crear(NAVE_X_INICIAL, NAVE_Y_INICIAL);

        		if (*nave == NULL)
        			return false;

        		(*contador_ciclos) = 0;
        		(*inmunidad) = 0;
        	}
        	else
        		(*contador_ciclos) -= 10; //suma una decima de espera
        }
        (*contador_ciclos)++;
    }

    return true;
}

bool comprobar_creacion_asteroides(lista_t *asteroides, int *cantidad_ast){

	if(lista_es_vacia(asteroides)){

		*cantidad_ast += 2;

		return crear_asteroides(asteroides, *cantidad_ast);
	}

	return true;	
}

void mover_objetos(nave_t *nave, lista_t *asteroides, lista_t *disparos, float dt){

	if (nave != NULL) 
		nave_mover(nave, dt);


	iterador_t *ir_asteroides = iterador_crear(asteroides);
	for(; !iterador_termino(ir_asteroides); iterador_siguiente(ir_asteroides)){

    	asteroide_mover(iterador_actual(ir_asteroides), dt);
	}
	iterador_destruir(ir_asteroides);



	iterador_t *ir_disparos = iterador_crear(disparos);
	for(; !iterador_termino(ir_disparos); iterador_siguiente(ir_disparos)){

    	disparo_mover(iterador_actual(ir_disparos), dt);
    }
	iterador_destruir(ir_disparos);


	ir_disparos = iterador_crear(disparos);
	while(!iterador_termino(ir_disparos)){

		if(!disparo_queda_tiempo(iterador_actual(ir_disparos))){
			disparo_destruir(iterador_eliminar_actual(ir_disparos));
			continue;
		}
		iterador_siguiente(ir_disparos);
	}
	iterador_destruir(ir_disparos);
}

void dibujar_objetos(nave_t *nave, lista_t *asteroides, lista_t *disparos, float dt, int *contador_ciclos, int *inmunidad){

	if(nave != NULL){
		if((*inmunidad) * dt < SEGUNDOS_INMUNIDAD){ //efecto parpadeo inmunidad
			if((*contador_ciclos) * dt >= 0.2){
				nave_dibujar(nave);
				if((*contador_ciclos) * dt >= 0.4)
					*contador_ciclos = 0;
			}
			(*contador_ciclos)++;	
		}

		else
			nave_dibujar(nave);	
	}


	iterador_t *ir_asteroides = iterador_crear(asteroides);
	for(; !iterador_termino(ir_asteroides); iterador_siguiente(ir_asteroides)){

    	asteroide_dibujar(iterador_actual(ir_asteroides));
	}
	iterador_destruir(ir_asteroides);
	ir_asteroides = NULL;


	iterador_t *ir_disparos = iterador_crear(disparos);
	for(; !iterador_termino(ir_disparos); iterador_siguiente(ir_disparos)){

		disparo_dibujar(iterador_actual(ir_disparos));
    }
	iterador_destruir(ir_disparos);
	ir_disparos = NULL;
}

void dibujar_interfaz(int puntos, int high_score, int vidas, SDL_Renderer *renderer){

	char string_aux[STRING_MAX];

	sprintf(string_aux, "%s %05d", "SCORE", puntos);
    dibujar_cadena(string_aux, 50, VENTANA_ALTO - 50, 3, renderer);  //los numeros de las posiciones son "magicos" y estan hardcodeados
        																//pero funcionarian en cualquier tamaño coherente de pantalla
    sprintf(string_aux, "%s %05d", "BEST ", high_score);
    dibujar_cadena(string_aux, 50,  VENTANA_ALTO - 100, 3, renderer);

    for(size_t i = 0; i<(vidas-1); i++){
    	graficador_dibujar(S_VIDAS, 1, 60+i*25, VENTANA_ALTO - 150, -PI/2);
    }
}

bool verificar_impacto_nave(nave_t **nave, lista_t *asteroides, int *vidas, int *puntos, int inmunidad, float dt){


	if((*nave) != NULL && inmunidad*dt > SEGUNDOS_INMUNIDAD){	

		float nx, ny;
		nave_get_coordenadas(*nave, &nx, &ny);

		bool memcheck = false;

		if(verificar_colision(nx, ny, asteroides, puntos, &memcheck, RADIO_NAVE)){
			nave_destruir((*nave));
    		(*nave) = NULL;
    		(*vidas) -= 1;
    	}

    	if(memcheck == true)
    		return false;
    }

    return true;
}

bool verificar_colision(float x, float y, lista_t *asteroides, int *puntos, bool *memcheck, int radio){

	iterador_t *ir_asteroides = iterador_crear(asteroides);

	for(;!iterador_termino(ir_asteroides); iterador_siguiente(ir_asteroides)){

    		if(asteroide_colisiono(iterador_actual(ir_asteroides), x, y, radio)){
    					
    			if(!dividir_asteroide(ir_asteroides))
    				*memcheck = true; //problema de memoria

    			int radio_ast = asteroide_get_radio(iterador_actual(ir_asteroides));
    					
    			computar_puntaje(radio_ast, puntos);

    			asteroide_destruir(iterador_eliminar_actual(ir_asteroides));

    			iterador_destruir(ir_asteroides);

    			return true;
    		}
	}

	iterador_destruir(ir_asteroides);
	return false;
}

bool verificar_impacto_disparos(lista_t *disparos, lista_t *asteroides, int *puntos){
	
    float dx, dy;
    bool memcheck = false;

    iterador_t *ir_disparos = iterador_crear(disparos);
	while(!iterador_termino(ir_disparos)){

    	disparo_get_coordenadas(iterador_actual(ir_disparos), &dx, &dy);

    	if(verificar_colision(dx, dy, asteroides, puntos, &memcheck, 1)){

    		disparo_destruir(iterador_eliminar_actual(ir_disparos));

    		if(memcheck == true){
    			iterador_destruir(ir_disparos);
    			return false;
    		}

    		continue;
    	}
    	iterador_siguiente(ir_disparos);
	}

	iterador_destruir(ir_disparos);

	return true;
}