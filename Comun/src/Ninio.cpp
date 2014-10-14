#include "Ninio.h"
#include "Logger.h"
#include <ctime>
#include <cstdlib>

Ninio::Ninio(const std::string& nombre) {
	this->nombre = nombre;
	estado = COLA_BOLETERIA;
	LOGGER->Log(this->nombre, this->estado);
}

void Ninio::siguienteEstado() {
	switch (estado) {
	case (COLA_BOLETERIA):
		estado = COLA_CALESITA;
		break;
	case (COLA_CALESITA):
		estado = EN_CALESITA;
		break;
	case (EN_CALESITA):
		estado = COLA_SALIDA;
		break;
	case (COLA_SALIDA):
		estado = SALIO;
		break;
	case (SALIO):
		break;
	}

	LOGGER->Log(this->nombre, this->estado);
}

Estado Ninio::getEstado() const {
	return estado;
}

void Ninio::setEstado(Estado estado) {
	this->estado = estado;
}

const std::string& Ninio::getNombre() const {
	return nombre;
}

void Ninio::setNombre(const std::string& nombre) {
	this->nombre = nombre;
}

unsigned Ninio::getUbicacionPreferida(unsigned cantidadUbicaciones) const {
	srand(time(NULL));
	return rand() % cantidadUbicaciones;
}
