#include "Configuracion.h"
#include <fstream>

Configuracion::Configuracion() :
		precioBoleto("7.50"), capacidadCalesita("30"), duracionVuelta("35"),
				cantNiniosGenerador("200") {
	std::ifstream archivo(Paths::getConfigFilename().c_str());
	if (archivo.is_open()) {
		//todo leer campos precio, capacidad, duracion y cantidad generador
		archivo.close();
	}
	else {
		throw std::string("Error al abrir el archivo de configuración");
	}
}

Configuracion::~Configuracion() {
}

const char* Configuracion::getPrecioBoleto() const {
	return precioBoleto.c_str();
}

const char* Configuracion::getCapacidadCalesita() const {
	return capacidadCalesita.c_str();
}

const char* Configuracion::getDuracionVueltaCalesita() const {
	return duracionVuelta.c_str();
}

const char* Configuracion::getCantidadNiniosGenerador() const {
	return cantNiniosGenerador.c_str();
}
