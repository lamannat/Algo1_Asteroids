CC := gcc
CFLAGS := -Wall -c -pedantic -std=c99 -g
LFLAGS := -lm

all: asteroids

modulo_asteroids.o: modulo_asteroids.c modulo_asteroids.h lista.h config.h asteroide.h
	$(CC) $(CFLAGS) modulo_asteroids.c

lista.o: lista.c lista.h
	$(CC) $(CFLAGS) lista.c

disparo.o: disparo.c disparo.h graficador.h config.h modulo_asteroids.h vectores.h
	$(CC) $(CFLAGS) disparo.c

asteroide.o: asteroide.c asteroide.h graficador.h modulo_asteroids.h vectores.h
	$(CC) $(CFLAGS) asteroide.c

nave.o: nave.c nave.h config.h modulo_asteroids.h graficador.h
	$(CC) $(CFLAGS) nave.c

caracteres.o: caracteres.c caracteres.h
	$(CC) $(CFLAGS) caracteres.c

graficador.o: graficador.c graficador.h config.h vectores.h
	$(CC) $(CFLAGS) graficador.c

main.o: main.c config.h diccionario.h caracteres.h graficador.h nave.h asteroide.h disparo.h lista.h modulo_asteroids.h
	$(CC) $(CFLAGS) main.c

vectores.o: vectores.c vectores.h config.h
	$(CC) $(CFLAGS) $(LFLAGS) vectores.c

diccionario.o: diccionario.c diccionario.h caracteres.h
	$(CC) $(CFLAGS) diccionario.c

asteroids: main.o caracteres.o vectores.o diccionario.o graficador.o nave.o asteroide.o disparo.o lista.o modulo_asteroids.o
	$(CC) $(LFLAGS) -lSDL2 $^ -o asteroids

clean:
	rm *.o

