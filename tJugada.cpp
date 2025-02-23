#include "tJugada.h"

int buscar(const tJugada& jugada, const tFicha& ficha) {
	int i = 0;
	bool encontrada = false;
	while (i < jugada.cont && !encontrada) {
		if (jugada.a[i] == ficha) encontrada = true;
		++i;
	}
	if (!encontrada) i = -1;
	return i;
}

void eliminaFichas(tSoporte& soporte, tJugada const& jugada) {
	for (int i = 0; i < jugada.cont; i++) {
		eliminaFicha(soporte, jugada.a[i]);
	}
}

bool nuevaJugada(tSoporte& soporte, tJugada& jugada){
	std::cout << "Fichas (0 al final): ";
	bool error = false;
	int numero;
	jugada.cont = 0;
	std::cin >> numero;
	if ((numero < 1) && (numero > soporte.cont)) {
		error = true;
	}
	int i = 0;
	while (numero != 0 && !error) {
		jugada.a[i] = soporte.a[numero - 1];
		jugada.cont++;
		std::cin >> numero;
		if ((numero < 1) && (numero > soporte.cont)) {
			error = true;
		}
		i++;
	}

	return error;
}

bool completarJugadas(tTablero& tablero, tJugada& jugada) {
	bool error = false;
	int i = 0;
	int cont = 0;
	int indice;
	std::cout << "Jugadas del tablero donde poner la ficha: ";
	while ((i < tablero.cont)) {
		if (comprobar(tablero.a[i], jugada.a[0])) {
			indice = i;
			std::cout << indice + 1 << " ";
			cont++;
		}
		i++;
	}
	if (cont == 1) {
		addFicha(tablero.a[indice], jugada.a[0]);
		std::cout << " -> Colocada!\n";
	}
	else if (cont == 0) {
		std::cout << "No se puede colocar\n";
		error = true;
	}
	else {
		std::cout << "\nIntroduzca la jugada en la que desea colocar la ficha: ";
		int n;
		std::cin >> n;
		if ((n > 0) && (n <= tablero.cont) && (comprobar(tablero.a[n - 1], jugada.a[0]))) {
			addFicha(tablero.a[n - 1], jugada.a[0]);
			std::cout << "Colocada!\n";
		}
		else {
			error = true;
			std::cout << "No se puede colocar\n";
		}
	}
	return error;
}

bool ponerJugada(tTablero& tablero, tJugada& jugada) {
	bool error = false;
	tJugada validacion; //Aqui se comprobarn si las fichas de jugada son válidas
	validacion.a[0] = jugada.a[0];
	validacion.a[1] = jugada.a[1];
	validacion.cont = 2;
	tCombinacion combinacion = tipoJugada(validacion);
	if (combinacion == erronea) error = true;
	else {
		int i = 2;
		while ((i < jugada.cont) && (!error)) {
			if (ponerFicha(validacion, jugada.a[i]));
			else {
				error = true;
			}
			i++;
		}
		if (!error) {
			tablero.a[tablero.cont] = validacion;
			tablero.cont++;
		}
	}
	return error;
}

bool ponerFicha(tJugada& jugada, tFicha& ficha){ //Suponemos que lo recibimos es una serie o escalera correcta
	bool correcto = true;
	correcto = comprobar(jugada, ficha);
	if (correcto) {
		addFicha(jugada, ficha);
	}
	return correcto;
}

bool comprobar(const tJugada& jugada, const tFicha& ficha){ //Comprueba si se puede añadir la ficha a una serie válida
	tCombinacion combinacion = tipoJugada(jugada);
	bool correcto = true;
	if (combinacion == serie) { //Para series
		if (jugada.cont == 4) correcto = false; //En cada serie max 4 fichas
		if (correcto && jugada.a[0].n != ficha.n) correcto = false; //Todas las fichas tienen = número que la primera
		int i = 0;
		while (correcto && i < jugada.cont) {
			if (jugada.a[i].c == ficha.c) correcto = false; //En una serie no puede repetirse nunca un color
			i++;
		}
	}
	else {  //Para escaleras
		if (jugada.cont == 13) correcto = false; //En cada serie max 13 fichas
		if (correcto && jugada.a[0].c != ficha.c) correcto = false; //Todas las fichas tienen = color que la primera
		if (correcto && (jugada.a[jugada.cont - 1].n + 1) != ficha.n && (jugada.a[0].n - 1) != ficha.n)correcto = false; //Si no va al final ni al principio está mal
	}
	return correcto;
}

void addFicha(tJugada& jugada, tFicha& ficha){ //Recibe una jugada y una ficha (se supone que ya se ha comprobado que se puesde añadir dicha ficha) y se añade la ficha
	tCombinacion combinacion = tipoJugada(jugada);
	if (combinacion == serie) { //Para series
		jugada.a[jugada.cont] = ficha;
		jugada.cont++;
	}
	else {
		if ((jugada.a[jugada.cont - 1].n + 1) == ficha.n) { //Si se puede añadir al final se añade
			jugada.a[jugada.cont] = ficha;
			jugada.cont++;
		}
		else if ((jugada.a[0].n - 1) == ficha.n) { //Si se puede añadir al principio se añade
			desplazarJugada(jugada);
			jugada.a[0] = ficha;
		}
	}
}

tCombinacion tipoJugada(const tJugada jugada){ //Especifica cual es el tipo de jugada de los dos primeros miembros de la jugada.
	tCombinacion combinacion;
	if (jugada.a[0].c == jugada.a[1].c) {
		if (jugada.a[0].n + 1 == jugada.a[1].n) combinacion = escalera;
		else combinacion = erronea;
	}
	else {
		if (jugada.a[0].n == jugada.a[1].n) combinacion = serie;
		else combinacion = erronea;
	}
	return combinacion;
}

void desplazarJugada(tJugada& jugada) { //Recibimos una jugada (como máximo tamaño 12) y añadimos una posicion y desplazamos todos los elementos a la derecha
	jugada.cont++;
	for (int i = jugada.cont; i >= 1; i--) {
		jugada.a[i] == jugada.a[i - 1];
	}
}

bool jugar(tTablero& tablero, tSoporte& soporte){
	mostrar(soporte);
	mostrarNumeros(soporte.cont);
	tJugada jugada; //Aqui iran las fihcas que selecciona el jugador
	bool error = nuevaJugada(soporte, jugada);
	std::cout << "Jugada: ";
	mostrar(jugada);
	if (!error) {
		if (jugada.cont == 1) {
			error = completarJugadas(tablero, jugada);
		}
		else if (jugada.cont >= 3) {
			error = ponerJugada(tablero, jugada);
			if (error) {
				std::cout << "La juagada introducida es erronea\n";
			}
			else {
				tCombinacion combinacion = tipoJugada(jugada);
				if (combinacion == serie) {
					std::cout << "Serie correcta\n";
				}
				else if (combinacion == escalera) {
					std::cout << "Escalera correcta\n";
				}
				else {
					std::cout << "ERROR\n";
				}
			}
		}
		else {
			error = true;
			std::cout << "Ha introducido un numero erroneo de fichas\n";
		}
	}
	else {
		std::cout << "Las fichas especificadas no existen\n";
	}
	if (!error) {
		eliminaFichas(soporte, jugada);
	}
	return error;
}

void mostrar(const tJugada& jugada){
	for (int i = 0; i < jugada.cont; i++) {
		mostrar(jugada.a[i]);
	}
	std::cout << '\n';
}

void mostrar(const tTablero& tablero){
	if (tablero.cont == 0) {
		std::cout << "Tablero: No hay jugadas\n";
	}
	else {
		std::cout << "Tablero:\n";
		for (int i = 0; i < tablero.cont; i++) {
			std::cout << std::setw(3) << i + 1 << ":";
			mostrar(tablero.a[i]);
		}
	}
	std::cout << '\n';
}

void mostrar(const tSoporte& soporte) {
	std::cout << "Soporte:";
	for (int i = 0; i < soporte.cont; i++) {
		mostrar(soporte.a[i]);
	}
	std::cout << '\n';
}

void mostrarSeries(const tSoporte& soporte) {
	tSoporte aux = soporte;
	ordenarPorNum(aux);
	tTablero posibilidades;
	posibilidades.cont = NumFichas;
	for (int i = 0; i < NumFichas; i++) {
		posibilidades.a[i].cont = 0;
	}
	for (int i = 0; i < aux.cont; i++) {
		int n = aux.a[i].n - 1;
		if (!colorRepetido(posibilidades.a[n], aux.a[i].c)) {
			int indice = posibilidades.a[n].cont;
			posibilidades.a[n].a[indice] = aux.a[i];
			posibilidades.a[n].cont++;
		}
	}
	for (int i = 0; i < NumFichas; i++) {
		if (posibilidades.a[i].cont >= 3) {
			mostrar(posibilidades.a[i]);
		}
	}
}

bool colorRepetido(const tJugada& jugada, const tColor& color){
	bool repetido = false;
	int i = 0;
	while ((!repetido) && (i < jugada.cont)) {
		if (jugada.a[i].c == color) {
			repetido = true;
		}
		i++;
	}

	return repetido;
}

void mostrarEscalera(const tSoporte& soporte) {
	tSoporte auxiliar;
	auxiliar = soporte;
	ordenarPorNum(auxiliar);
	ordenarPorColor(auxiliar);
	int i = 0;
	int pos = 0;
	while (i < auxiliar.cont) {
		tJugada nueva;
		nueva.cont = 0;
		nueva.a[0] = auxiliar.a[i];
		nueva.cont++;
		for (int j = i + 1; j < auxiliar.cont; j++) {
			if ((nueva.a[nueva.cont - 1].c == auxiliar.a[j].c) && (((auxiliar.a[j].n) - 1)) == nueva.a[nueva.cont - 1].n) {
				nueva.a[nueva.cont] = auxiliar.a[j];
				nueva.cont++;
				if (nueva.cont >= 3) {
					pos = j;
				}
			}
		}
		if (nueva.cont >= 3) {
			mostrar(nueva);
			i = pos;
		}
		i++;
	}

}

void mostrarNumeros(int n) {
	std::cout << std::setw(6) << ' ';
	for (int i = 0; i < n; i++) {
		std::cout << std::setw(4) << i + 1;
	}
	std::cout << '\n';
}
