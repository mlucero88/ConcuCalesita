#include "Calesita.h"
#include <string>

Calesita::Calesita(unsigned capacidad, unsigned duracionVuelta) :
		ubicaciones(NULL), capacidad(capacidad), duracionVuelta(duracionVuelta),
				cantidadOcupada(0) {
	ubicaciones = new Ninio*[capacidad];
	for (unsigned int i = 0; i < capacidad; ++i) {
		ubicaciones[i] = NULL;
	}
}

Calesita::~Calesita() {
	vaciar();
	delete[] ubicaciones;
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

void Calesita::agregarNinio(const Ninio& ninio) {
	if (!estaLlena()) {
		unsigned ubicacion = ninio.getUbicacionPreferida(capacidad);
		if (estaOcupado(ubicacion)) {
			// todo loguear que intento sentarse en su ubicacion preferida y estaba ocupada
			ubicacion = encontrarLugarLibre();
		}
		ubicaciones[ubicacion] = new Ninio(ninio);
		// todo loguear que se sento en la ubicacion "ubicacion"
		++cantidadOcupada;
	}
	else {
		throw std::string("Calesita Llena");
	}
}

void Calesita::vaciar() {
	if (!estaVacia()) {
		for (unsigned int i = 0; i < capacidad; ++i) {
			if (ubicaciones[i] != NULL) {
				// todo loguear que el ninio salio de la calesita
				// el pibe se obtiene asi: ubicaciones[i] (esto retorna un Ninio*)
				delete ubicaciones[i];
				ubicaciones[i] = NULL;
			}
		}
		cantidadOcupada = 0;
	}
}

bool Calesita::estaOcupado(unsigned lugar) const {
	if (lugar < capacidad && ubicaciones[lugar] != NULL) {
		return true;
	}
	return false;
}

unsigned Calesita::encontrarLugarLibre() const {
	if (!estaLlena()) {
		unsigned indice = 0;
		while (indice < capacidad) {
			if (ubicaciones[indice] == NULL) {
				return indice;
			}
			++indice;
		}
	}
	throw std::string("Calesita Llena");
}
