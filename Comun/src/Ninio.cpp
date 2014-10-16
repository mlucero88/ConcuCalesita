#include "Ninio.h"
#include "Logger.h"
#include <ctime>
#include <cstdlib>

Ninio::Ninio(const std::string& nombre) {
	this->nombre = nombre;
	estado = NACE;
}

Ninio::Ninio(const Ninio& copia) :
		nombre(copia.nombre), estado(copia.estado) {
}

Ninio& Ninio::operator=(const Ninio& copia) {
	nombre = copia.nombre;
	estado = copia.estado;
	return *this;
}

void Ninio::siguienteEstado() {
	switch (estado) {
	case (NACE):
		estado = EN_COLA_BOLETERIA;
		break;
	case (EN_COLA_BOLETERIA):
		estado = COMPRA_BOLETO;
		break;
	case (COMPRA_BOLETO):
		estado = EN_COLA_CALESITA;
		break;
	case (EN_COLA_CALESITA):
		estado = ENTRA_CALESITA;
		break;
	case (ENTRA_CALESITA):
		estado = SALE_CALESITA;
		break;
	case (SALE_CALESITA):
		break;
	}
	LOGGER->Log(nombre, estado);
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
