#include "CreacionExcepcion.h"

CreacionExcepcion::CreacionExcepcion(const char *motivo) throw () :
		SocketExcepcion(motivo) {
}

CreacionExcepcion::~CreacionExcepcion() throw () {
}

const char* CreacionExcepcion::what() const throw () {
	std::string error("ERROR EN LA CREACION DEL SOCKET! Motivo: ");
	error.append(motivo);
	return error.c_str();
}
