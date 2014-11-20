#include "CierreExcepcion.h"

CierreExcepcion::CierreExcepcion(const char *motivo) throw () :
		SocketExcepcion(motivo) {
}

CierreExcepcion::~CierreExcepcion() throw () {
}

const char* CierreExcepcion::what() const throw () {
	std::string error("ERROR EN EL CIERRE DEL SOCKET! Motivo: ");
	error.append(motivo);
	return error.c_str();
}
