#ifndef TSOPORTE_H_
#define TSOPORTE_H_

#include "tFicha.h"

const int MaxFichas = 50;
const int NumJugadores = 2;

typedef tFicha tArrayFicha[MaxFichas];

struct tSoporte {
	tArrayFicha a;
	int cont;
};

typedef tSoporte tManos[NumJugadores]; //tManos es tSoportes, pero como tSoportes se podia confundir con tSoporte hemos decidido cambiarle el nombre a tManos

void ordenarPorNum(tSoporte& soporte);
void ordenarPorColor(tSoporte& soporte);
void mostrar(const tSoporte& soporte);
void eliminaFicha(tSoporte& soporte, tFicha const& ficha);
int sumar(tSoporte const& soporte);

#endif
