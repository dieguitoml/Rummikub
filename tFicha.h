#ifndef TFICHA_H_
#define TFICHA_H_

enum tColor { rojo, verde, azul, amarillo, blanco };

struct tFicha {
	int n;
	tColor c;
};

bool operator==(const tFicha& ficha1, const tFicha& ficha2);
void colorTexto(tColor color);
void mostrar(const tFicha& ficha);

#endif
