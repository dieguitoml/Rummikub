#ifndef TBOLSA_H_
#define TBOLSA_H_	

#include "tSoporte.h"

const int NumFichas = 8; //8-13
const int NumColores = 4;
const int IniFichas = 6;//26

typedef bool tMatrizBool[NumColores * 2][NumFichas];

struct tBolsa {
	tMatrizBool m;
	int cont;
};

void inicializarBolsa(tBolsa& bolsa);
tFicha robar(tBolsa& bolsa);
void repartir(tBolsa& bolsa, tManos& manos);
void mostrar(const tBolsa& bolsa);

#endif
