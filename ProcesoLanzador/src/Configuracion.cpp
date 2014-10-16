#include "Configuracion.h"
#include <fstream>
#include <sstream>

static const int cantidadCampos = 4;
static const std::string campoPrecio("<precio_boleto>");
static const std::string campoCapacidad("<capacidad_calesita>");
static const std::string campoDuracion("<duracion_vuelta_calesita>");
static const std::string campoCantidad("<ninios_a_generar>");

Configuracion::Configuracion() :
		precioBoleto("7.50"), capacidadCalesita("30"), duracionVuelta("15"),
				cantNiniosGenerador("200") {
	std::ifstream archivo(Paths::getConfigFilename().c_str());
	if (archivo.is_open()) {
		std::string campo;
		std::string valor;
		for (int i = 0; i < cantidadCampos; ++i) {
			archivo >> campo;
			archivo >> valor;
			std::stringstream ss(valor);
			if (campo == campoPrecio) {
				ss >> precioBoleto;
			}
			else if (campo == campoCapacidad) {
				ss >> capacidadCalesita;
			}
			else if (campo == campoDuracion) {
				ss >> duracionVuelta;
			}
			else if (campo == campoCantidad) {
				ss >> cantNiniosGenerador;
			}
		}
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
