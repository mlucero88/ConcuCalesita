#include "EnvioExcepcion.h"

EnvioExcepcion::EnvioExcepcion(const char *motivo) throw () :
		SocketExcepcion(motivo) {
}

EnvioExcepcion::~EnvioExcepcion() throw () {
}

const char* EnvioExcepcion::what() const throw () {
	std::string error("ERROR EN EL ENVIO! Motivo: ");
	error.append(motivo);
	return error.c_str();
}
