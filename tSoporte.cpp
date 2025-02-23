#include "tSoporte.h"

void ordenarPorNum(tSoporte& soporte) {
	int i = 0;
	bool continuar = true;
	while ((i < soporte.cont - 1) && (continuar)) {
		continuar = false;
		for (int j = soporte.cont - 1; j > i; j--) {
			if (soporte.a[j].n < soporte.a[j - 1].n) {
				tFicha aux = soporte.a[j];
				soporte.a[j] = soporte.a[j - 1];
				soporte.a[j - 1] = aux;
				continuar = true;
			}
			else if (((int)soporte.a[j].c < (int)soporte.a[j - 1].c)&&(soporte.a[j].n == soporte.a[j - 1].n)) {
				tFicha aux = soporte.a[j];
				soporte.a[j] = soporte.a[j - 1];
				soporte.a[j - 1] = aux;
				continuar = true;
			}
		}
		i++;
	}
}

void ordenarPorColor(tSoporte& soporte) {
	int i = 0;
	bool continuar = true;
	while ((i < soporte.cont - 1) && (continuar)) {
		continuar = false;
		for (int j = soporte.cont - 1; j > i; j--) {
			if ((int)soporte.a[j].c < (int)soporte.a[j - 1].c) {
				tFicha aux = soporte.a[j];
				soporte.a[j] = soporte.a[j - 1];
				soporte.a[j - 1] = aux;
				continuar = true;
			}
			else if ((soporte.a[j].n < soporte.a[j - 1].n)&&((int)soporte.a[j].c == (int)soporte.a[j - 1].c)) {
				tFicha aux = soporte.a[j];
				soporte.a[j] = soporte.a[j - 1];
				soporte.a[j - 1] = aux;
				continuar = true;
			}
		}
		i++;
	}
}

void eliminaFicha(tSoporte& soporte, tFicha const& ficha){
	int j = 0;
	bool encontrado = false;
	while (j < soporte.cont && !encontrado) {
		if (soporte.a[j] == ficha) {
			encontrado = true;
			soporte.cont--;
			soporte.a[j] = soporte.a[soporte.cont];
		}
		j++;
	}
}

int sumar(tSoporte const& soporte){ //Suma los valores de las fichas de un soporte
	int suma = 0;
	for (int i = 0; i < soporte.cont; i++) {
		suma += soporte.a[i].n;
	}
	return suma;
}
