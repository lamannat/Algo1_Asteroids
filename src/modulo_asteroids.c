#include "modulo_asteroids.h"
#include "config.h"

bool dividir_asteroide(iterador_t *ir_asteroides){

	float x, y;
	int radio;

	if((radio = asteroide_get_radio(iterador_actual(ir_asteroides))) != RADIO_ASTEROIDE/4){

    	asteroide_get_coordenadas(iterador_actual(ir_asteroides), &x, &y);
    	asteroide_t *ast;

		ast = asteroide_crear(x, y, radio/2); 
		if(ast == NULL)
			return false;  

    	if(!(iterador_insertar(ir_asteroides, ast))){

    		asteroide_destruir(ast);
    		return false;
    	}

    	ast = asteroide_crear(x, y, radio/2);
    	if(ast == NULL)
			return false; 

    	if(!(iterador_insertar(ir_asteroides, ast))){

    		asteroide_destruir(ast);
    		return false;
    	}

    	return true;
	}
	
    else{
    	return true;
    }
}

void computar_puntaje(int radio, int *puntos){

	if(radio == RADIO_ASTEROIDE)
		(*puntos) += PTOS_GRANDE;

	if(radio == RADIO_ASTEROIDE/2)
		(*puntos) += PTOS_MEDIANO;

	if(radio == RADIO_ASTEROIDE/4)
		(*puntos) += PTOS_CHICO;
}

bool centro_esta_libre(lista_t *asteroides, int radio){

	iterador_t *ir = iterador_crear(asteroides);

		for(;!iterador_termino(ir); iterador_siguiente(ir)){

    			if(asteroide_colisiono(iterador_actual(ir), NAVE_X_INICIAL, NAVE_Y_INICIAL, RADIO_NAVE))
    				return false;
    	}
		iterador_destruir(ir);
	return true;
}

double computar_velocidad(double vi, double a, double dt){
	double vi1=vi+a*dt;
	return vi1;
}

double computar_posicion(double pi, double vi, double dt){
	double pi1= pi+vi*dt;
	return pi1;
}