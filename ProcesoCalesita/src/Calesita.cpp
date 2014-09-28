#include "Calesita.h"
#include <string>

Calesita::Calesita(unsigned capacidad, unsigned duracionVuelta) :
		capacidad(capacidad), cantidadOcupada(0), duracionVuelta(duracionVuelta) {
}

Calesita::~Calesita() {
}

bool Calesita::estaLlena() const {
	return cantidadOcupada == capacidad;
}

bool Calesita::estaVacia() const {
	return cantidadOcupada == 0;
}

unsigned Calesita::getDuracionVuelta() const {
	return duracionVuelta;
}

void Calesita::agregarNinio() {
	if (!estaLlena()) {
		++cantidadOcupada;
	}
	else {
		throw std::string("Calesita Llena");
	}
}

void Calesita::quitarNinio() {
	if (!estaVacia()) {
		--cantidadOcupada;
	}
	else {
		throw std::string("Calesita Vacia");
	}
}
