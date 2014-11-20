#include "Gestor.h"
#include <fstream>

Gestor::Gestor() :
		tabla() {
}

Gestor::~Gestor() {
}

bool Gestor::cargarTabla(const std::string& nombreArchivo) {
	std::ifstream stream(nombreArchivo.c_str(), std::ios::binary);
	if (stream.is_open()) {
		tabla.clear();
		Registro registro;
		do {
			/* Registros de longitud fija */
			stream.read(reinterpret_cast< char * >(&registro),
					sizeof(registro));
			if (!stream.eof()) {
				tabla.push_back(registro);
			}
		} while (!stream.eof());
		stream.close();
		return true;
	}
	return false;
}

bool Gestor::persistirTabla(const std::string& nombreArchivo) const {
	std::ofstream stream(nombreArchivo.c_str(),
			std::ios::trunc | std::ios::binary);
	if (stream.is_open()) {
		std::vector< Registro >::const_iterator it;
		for (it = tabla.begin(); it != tabla.end(); ++it) {
			Registro registro = *it;
			/* Registros de longitud fija, no hace falta prefijar tamanio */
			stream.write(reinterpret_cast< char * >(&registro),
					sizeof(registro));
		}
		stream.close();
		return true;
	}
	return false;
}

void Gestor::agregarRegistro(const Registro& registro) {
	tabla.push_back(registro);
}

const std::vector< Registro >& Gestor::retornarTabla() const {
	return tabla;
}
