#ifndef TJUGADA_H_
#define TJUGADA_H_

#include <iostream>
#include <iomanip>

#include "tBolsa.h"

const int MaxJugadas = NumFichas * 2;

typedef tFicha tArrayFicha2[NumFichas];

struct tJugada {
	tArrayFicha2 a;
	int cont;
};

typedef tJugada tArrayJugada[MaxJugadas];

struct tTablero {
	tArrayJugada a;
	int cont;
};

enum tCombinacion {serie, escalera, erronea};

int buscar(const tJugada& jugada, const tFicha& ficha);
void eliminaFichas(tSoporte& soporte, tJugada const& jugada);
bool nuevaJugada(tSoporte& soporte, tJugada& jugada);
bool ponerFicha(tJugada& jugada, tFicha& ficha);
tCombinacion tipoJugada(const tJugada jugada);
void desplazarJugada(tJugada& jugada);
bool jugar(tTablero& tablero, tSoporte& soporte);
bool comprobar(const tJugada& jugada,const tFicha& ficha);
void addFicha(tJugada& jugada, tFicha& ficha);
bool completarJugadas(tTablero& tablero, tJugada& jugada);
bool ponerJugada(tTablero& tablero, tJugada& jugada);
bool colorRepetido(const tJugada& jugada, const tColor& color);
void mostrar(const tJugada& jugada);
void mostrar(const tTablero& tablero);
void mostrarSeries(const tSoporte& soporte);
void mostrarEscalera(const tSoporte& soporte);
void mostrarNumeros(int n);
#endif
