#include "Calesita.h"
#include "Logger.h"
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
	std::string mensaje;
	if (!estaLlena()) {
		unsigned ubicacion = ninio.getUbicacionPreferida(capacidad);
		char buffer[50];
		sprintf(buffer, "%d", ubicacion);
		if (estaOcupado(ubicacion)) {
			mensaje = "CALESITA: El ninio " + ninio.getNombre() + " intento"
					" subirse a la ubicacion " + buffer + " y estaba ocupada";
			LOGGER.log(mensaje);
			ubicacion = encontrarLugarLibre();
			sprintf(buffer, "%d", ubicacion);
		}
		ubicaciones[ubicacion] = new Ninio(ninio);
		mensaje = "CALESITA: El ninio " + ninio.getNombre() + " se subio a"
				" la ubicacion " + buffer;
		LOGGER.log(mensaje);
		++cantidadOcupada;
	}
	else {
		mensaje = "CALESITA: El ninio " + ninio.getNombre() + " no se pudo"
				" ubicar en la calesita. Calesita Llena";
		LOGGER.log(mensaje);
		throw std::string("Calesita Llena");
	}
}

void Calesita::vaciar() {
	if (!estaVacia()) {
		for (unsigned int i = 0; i < capacidad; ++i) {
			if (ubicaciones[i] != NULL) {
				ubicaciones[i]->siguienteEstado();
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
