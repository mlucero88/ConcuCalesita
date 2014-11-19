#include "AceptacionExcepcion.h"

AceptacionExcepcion::AceptacionExcepcion(const char *motivo) throw () :
		SocketExcepcion(motivo) {
}

AceptacionExcepcion::~AceptacionExcepcion() throw () {
}

const char* AceptacionExcepcion::what() const throw () {
	std::string error("ERROR EN LA ACEPTACION DE CLIENTE! Motivo: ");
	error.append(motivo);
	return error.c_str();
}
