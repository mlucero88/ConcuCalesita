#include "EnlaceExcepcion.h"

EnlaceExcepcion::EnlaceExcepcion(const char *motivo) throw () :
		SocketExcepcion(motivo) {
}

EnlaceExcepcion::~EnlaceExcepcion() throw () {
}

const char* EnlaceExcepcion::what() const throw () {
	std::string error("ERROR AL ENLAZAR! Motivo: ");
	error.append(motivo);
	return error.c_str();
}
