#include "Gestor.h"
#include <fstream>

Gestor::Gestor(const std::string& nombreArchivo, char caracter) :
		tabla(), protocolo(nombreArchivo, caracter) {
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

bool Gestor::agregarRegistro(const Registro& registro) {
	// todo Hay que hacer verificacione de existencia o algo?
	tabla.push_back(registro);
	return true;
}

void Gestor::atenderCliente() {
	Mensaje peticion = protocolo.recibirMensaje();
	switch (peticion.comando) {
	case Protocolo::add_reg: {
		if (agregarRegistro(peticion.registro)) {
			protocolo.enviarOperacionExitosa(peticion.idRemitente);
		}
		else {
			protocolo.enviarOperacionFallida(peticion.idRemitente);
		}
		break;
	}
	case Protocolo::get_regs: {
		std::vector< Registro >::const_iterator it;
		Registro registro;
		for (it = tabla.begin(); it != tabla.end(); ++it) {
			registro = *it;
			if (!protocolo.enviarRegistro(peticion.idRemitente, registro)) {
				protocolo.enviarOperacionFallida(peticion.idRemitente);
				return;
			}
		}
		protocolo.enviarOperacionExitosa(peticion.idRemitente);
		break;
	}
	default: {
		protocolo.enviarComandoDesconocido(peticion.idRemitente);
	}
	}
}
