#ifndef CALESITA_H_
#define CALESITA_H_

#include "Ninio.h"

class Calesita {
public:
	Calesita(unsigned capacidad, unsigned duracionVuelta);
	~Calesita();

	bool estaLlena() const;
	bool estaVacia() const;
	unsigned getDuracionVuelta() const;
	void agregarNinio(const Ninio& ninio);
	void vaciar();

private:
	Ninio** ubicaciones;
	const unsigned capacidad, duracionVuelta;
	unsigned cantidadOcupada;

	bool estaOcupado(unsigned lugar) const;
	unsigned encontrarLugarLibre() const;
};

#endif
