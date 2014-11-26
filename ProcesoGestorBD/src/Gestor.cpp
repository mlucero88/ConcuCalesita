#include "Gestor.h"
#include <fstream>
#include <iostream>
#include <cerrno>

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
				agregarRegistro(registro);
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
	// todo Hay que hacer verificaciones de existencia o algo?
	tabla.push_back(registro);
	return true;
}

void Gestor::atenderCliente() {
	static int nroPeticion = 1;
	Mensaje peticion;
	try {
		peticion = protocolo.recibirMensaje();
	}
	catch(const std::string &e) {
		/* Si no se pudo recibir un mensaje y errno vale EINTR, fue porque se
		 * recibio la senial de cierre del gestor que desbloqueo a msgrcv() */
		if (errno != EINTR) {
			std::cerr << e << std::endl;
		}
		return;
	}
	switch (peticion.comando) {
	case Protocolo::add_reg: {
		std::cout << "PETICIÓN " << nroPeticion << " - AGREGAR REGISTRO"
				<< std::endl;
		if (agregarRegistro(peticion.registro)) {
			std::cout << "Petición " << nroPeticion
					<< " - Registro agregado exitosamente" << std::endl;
			protocolo.enviarOperacionExitosa(peticion.idRemitente);
		}
		else {
			std::cout << "Petición " << nroPeticion
					<< " - Registro no pudo ser agregado" << std::endl;
			protocolo.enviarOperacionFallida(peticion.idRemitente);
		}
		break;
	}
	case Protocolo::get_regs: {
		std::cout << "PETICIÓN " << nroPeticion << " - OBTENER TABLA"
				<< std::endl;
		std::vector< Registro >::const_iterator it;
		Registro registro;
		bool envioExitoso = true;
		int indice = 0;
		for (it = tabla.begin(); it != tabla.end() && envioExitoso;
				++it, ++indice) {
			registro = *it;
			envioExitoso = protocolo.enviarRegistro(peticion.idRemitente,
					registro);
			if (envioExitoso) {
				std::cout << "Petición " << nroPeticion << " - Registro "
						<< indice << " enviado exitosamente" << std::endl;
			}
			else {
				std::cout << "Petición " << nroPeticion << " - Registro "
						<< indice << " no pudo ser enviado" << std::endl;
				envioExitoso = false;
			}
		}
		if (envioExitoso) {
			std::cout << "Petición " << nroPeticion
					<< " - Tabla enviada exitosamente" << std::endl;
			protocolo.enviarOperacionExitosa(peticion.idRemitente);
		}
		else {
			std::cout << "Petición " << nroPeticion
					<< " - Tabla no pudo ser enviada" << std::endl;
			protocolo.enviarOperacionFallida(peticion.idRemitente);
		}
		break;
	}
	default: {
		std::cout << "PETICIÓN " << nroPeticion << " - COMANDO DESCONOCIDO"
				<< std::endl;
		protocolo.enviarComandoDesconocido(peticion.idRemitente);
	}
	}
	std::cout << std::endl;
	++nroPeticion;
}
