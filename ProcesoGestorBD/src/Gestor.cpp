#include "Gestor.h"
#include <fstream>
#include <iostream>
#include <cerrno>

Gestor::Gestor(const std::string& nombreArchivoTabla,
		const std::string& nombreArchivoCola, char caracter) :
		tabla(), protocolo(nombreArchivoCola, caracter),
				nombreArchivoTabla(nombreArchivoTabla) {
	cargarTabla();
}

Gestor::~Gestor() {
	persistirTabla();
}

void Gestor::atenderSolicitud() {
	static int nroSolicitud = 1;
	Mensaje solicitud;
	try {
		solicitud = protocolo.recibirMensaje();
	}
	catch(const std::string &e) {
		/* Si no se pudo recibir un mensaje y errno vale EINTR, fue porque se
		 * recibio la senial de cierre del gestor que desbloqueo a msgrcv() */
		if (errno != EINTR) {
			std::cerr << e << std::endl;
		}
		return;
	}
	switch (solicitud.comando) {
	case Protocolo::add_reg: {
		std::cout << "SOLICITUD " << nroSolicitud << " - AGREGAR REGISTRO"
				<< std::endl;
		if (agregarRegistro(solicitud.registro)) {
			std::cout << "Solicitud " << nroSolicitud
					<< " - Registro agregado exitosamente" << std::endl;
			protocolo.enviarOperacionExitosa(solicitud.idRemitente);
		}
		else {
			std::cout << "Solicitud " << nroSolicitud
					<< " - Registro no pudo ser agregado" << std::endl;
			protocolo.enviarOperacionFallida(solicitud.idRemitente);
		}
		break;
	}
	case Protocolo::get_regs: {
		std::cout << "SOLICITUD " << nroSolicitud << " - OBTENER TABLA"
				<< std::endl;
		std::vector< Registro >::const_iterator it;
		Registro registro;
		bool envioExitoso = true;
		int indice = 0;
		for (it = tabla.begin(); it != tabla.end() && envioExitoso;
				++it, ++indice) {
			registro = *it;
			envioExitoso = protocolo.enviarRegistro(solicitud.idRemitente,
					registro);
			if (envioExitoso) {
				std::cout << "Solicitud " << nroSolicitud << " - Registro "
						<< indice << " enviado exitosamente" << std::endl;
			}
			else {
				std::cout << "Solicitud " << nroSolicitud << " - Registro "
						<< indice << " no pudo ser enviado" << std::endl;
				envioExitoso = false;
			}
		}
		if (envioExitoso) {
			std::cout << "Solicitud " << nroSolicitud
					<< " - Tabla enviada exitosamente" << std::endl;
			protocolo.enviarOperacionExitosa(solicitud.idRemitente);
		}
		else {
			std::cout << "Solicitud " << nroSolicitud
					<< " - Tabla no pudo ser enviada" << std::endl;
			protocolo.enviarOperacionFallida(solicitud.idRemitente);
		}
		break;
	}
	default: {
		std::cout << "SOLICITUD " << nroSolicitud << " - COMANDO DESCONOCIDO"
				<< std::endl;
		protocolo.enviarComandoDesconocido(solicitud.idRemitente);
	}
	}
	std::cout << std::endl;
	++nroSolicitud;
}

void Gestor::cargarTabla() {
	std::ifstream stream(nombreArchivoTabla.c_str(), std::ios::binary);
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
	}
}

void Gestor::persistirTabla() const {
	std::ofstream stream(nombreArchivoTabla.c_str(),
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
	}
}

bool Gestor::agregarRegistro(const Registro& registro) {
	// todo Hacer verificacion de unicidad
	tabla.push_back(registro);
	return true;
}
