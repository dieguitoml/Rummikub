#include "tFicha.h"
#include <iostream>
#include <iomanip>

bool operator==(const tFicha& ficha1, const tFicha& ficha2) {
	bool iguales = false;
	if (ficha1.c == ficha2.c) {
		if (ficha1.n == ficha2.n) {
			iguales = true;
		}
	}
	return iguales;
}

void colorTexto(tColor color) {
	switch (color) {
	case amarillo:
		std::cout << "\033[1;40;33m";
		break;
	case azul:
		std::cout << "\033[40;34m";
		break;
	case rojo:
		std::cout << "\033[40;31m";
		break;
	case verde:
		std::cout << "\033[40;32m";
		break;
	case blanco:
		std::cout << "\033[40;37m";
		break;
	}
}

void mostrar(const tFicha& ficha) {
	colorTexto(ficha.c);
	std::cout << std::setw(2) << ficha.n << "  ";
	colorTexto(blanco);
}
