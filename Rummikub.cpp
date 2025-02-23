#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <climits>
#include <cmath>
#include <cctype>
#include <cfloat>

#include "tFicha.h"
#include "tSoporte.h"
#include "tBolsa.h"
#include "tJugada.h"

int menu() {
	std:: cout << "1: Ordenar por num., 2: Ordenar por color, 3: Sugerir, 4: Poner, 0: Fin >>> ";
	int opcion;
	std::cin >> opcion;
	while ((opcion < 0) || (opcion > 4) ||  (std::cin.fail())) {
		std::cout << "Opcion no valida, introduzca un numero valido >>> ";
		std::cin.clear();
		std::cin.ignore(INT_MAX, '\n');
		std::cin >> opcion;
	}
	return opcion;
}

int main() {
	srand(time(NULL));
	int jugador = rand() % NumJugadores;
	tBolsa bolsa; //Inicializamos bolsa
	inicializarBolsa(bolsa);
	tManos manos; //Inicilizamos soportes y robamos
	repartir(bolsa, manos); 
	tTablero tablero; //Inicilizamos el tablero
	tablero.cont = 0;

	bool ganador = false; //True si hay ganador
	int pasar = 0; //Numero de jugadores consecutivos que pasan turno
	bool bolsa_vacia = false; //True cuando se acabe la bolsa
	int jugador_ganador;
	while (!ganador && !(bolsa_vacia && pasar == NumJugadores)) {
		std::cout << "Turno para el jugador " << jugador + 1 << " ...\n\n";
		bool colocado = false; //True si el player  colocado alguna ficha en su turno
		int opcion = 5;
		while ((opcion != 0)&&!ganador) {
			mostrar(manos[jugador]);
			opcion = menu();
			switch (opcion) {
			case 1:
				ordenarPorNum(manos[jugador]);
				break;
			case 2:
				ordenarPorColor(manos[jugador]);
				break;
			case 3:
				mostrarSeries(manos[jugador]);
				mostrarEscalera(manos[jugador]);
				break;
			case 4:
				bool aux;
				aux = !jugar(tablero, manos[jugador]);
				if (!colocado) colocado = aux;
				std::cout << '\n';
				mostrar(tablero);
				std::cout << '\n';
				if (manos[jugador].cont == 0) {
					ganador = true;
					jugador_ganador = jugador;
				}
				break;
			case 0:
				if (colocado && bolsa_vacia) {
					pasar = 0;
				}
				if (!colocado) {
					if (!bolsa_vacia) {
						int cont = manos[jugador].cont;
						tFicha ficha = robar(bolsa);
						if (ficha.n != -1) {
							manos[jugador].a[cont] = ficha;
							manos[jugador].cont++;
						}
						else {
							bolsa_vacia = true;
						}
					}
					if (bolsa_vacia) {
						pasar++;
						std::cout << "La bolsa esta vacia, y "<< pasar << " jugador/es no ha/han puesto ficha\n\n";
					}
				}
				break;
			}
		}
		jugador = (jugador+1) % NumJugadores;
	}
	std::cout << '\n';
	if (ganador) {
		std::cout << "El jugador " << jugador_ganador + 1 << " gana\n";
	}
	else {
		std::cout << "La partida termina por situacion de bloqueo\n";
		int puntos[NumJugadores];
		for (int i = 0; i < NumJugadores; i++) {
			std::cout << "Jugador " << i + 1 << ":\n";
			mostrar(manos[i]);
			puntos[i] = sumar(manos[i]);
			std::cout << "Puntos: " << puntos[i] << "\n\n\n";
		}
		jugador_ganador = 0;
		for (int i = 1; i < NumJugadores; i++) {
			if (puntos[jugador_ganador] > puntos[i]) {
				jugador_ganador = i;
			}
		}
		std::cout << "El jugador " << jugador_ganador + 1 << " gana con " << puntos[jugador_ganador] << " puntos\n";
	}
	return 0;
}
