#include "ConexionExcepcion.h"

ConexionExcepcion::ConexionExcepcion(const char *motivo) throw () :
		SocketExcepcion(motivo) {
}

ConexionExcepcion::~ConexionExcepcion() throw () {
}

const char* ConexionExcepcion::what() const throw () {
	std::string error("ERROR AL CONECTAR! Motivo: ");
	error.append(motivo);
	return error.c_str();
}
