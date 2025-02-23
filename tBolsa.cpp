#include <cstdlib>
#include <ctime>
#include<iostream>

#include "tBolsa.h"

void inicializarBolsa(tBolsa& bolsa) {
	for (int i = 0; i < NumColores * 2; i++) {
		for (int j = 0; j < NumFichas; j++) {
			bolsa.m[i][j] = true;
		}
	}
	bolsa.cont = NumColores * 2 * NumFichas;
}

tFicha robar(tBolsa& bolsa) {
	int x = rand() % (NumColores * 2);
	int y = rand() % NumFichas;
	tFicha ficha;
	if (bolsa.cont != 0) {
		if (!bolsa.m[x][y]) {
			bool encontrado = true;
			int i = x, j = y + 1;
			while ((j < NumFichas) && (encontrado)) {
				encontrado = !bolsa.m[i][j];
				if (!encontrado) {
					ficha = { j + 1, tColor(i % 4) };
					bolsa.m[i][j] = false;
				}
				j++;
			}

			i = x + 1;
			while ((i < NumColores * 2) && (encontrado)) {
				j = 0;
				while ((j < NumFichas) && (encontrado)) {
					encontrado = !bolsa.m[i][j];
					if (!encontrado) {
						ficha = { j + 1, tColor(i % 4) };
						bolsa.m[i][j] = false;
					}
					j++;
				}
				i++;
			}
			i = 0;
			while ((i < x + 1) && (encontrado)) {
				j = 0;
				while ((j < NumFichas) && (encontrado)) {
					encontrado = !bolsa.m[i][j];
					if (!encontrado) {
						ficha = { j + 1, tColor(i % 4) };
						bolsa.m[i][j] = false;
					}
					j++;
				}
				i++;
			}
		}
		else {
			ficha = { y + 1, tColor(x % 4) };
			bolsa.m[x][y] = false;
		}
		bolsa.cont--;
	}
	else {
		ficha = { -1, blanco };
	}
	return ficha;
}

void repartir(tBolsa& bolsa, tManos& manos) {
	for (int i = 0; i < NumJugadores; i++) {
		manos[i].cont = 0;
		for (int j = 0; j < IniFichas; j++) {
			manos[i].a[j] = robar(bolsa);
			manos[i].cont++;
		}
	}
}

void mostrar(const tBolsa& bolsa) {
	for (int i = 0; i < NumColores * 2; i++) {
		for (int j = 0; j < NumFichas; j++) {
			std::cout << bolsa.m[i][j] << " ";
		}
		std::cout << '\n';
	}

}
