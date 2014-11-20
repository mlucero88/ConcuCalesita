#include "EscuchaExcepcion.h"

EscuchaExcepcion::EscuchaExcepcion(const char *motivo) throw () :
		SocketExcepcion(motivo) {
}

EscuchaExcepcion::~EscuchaExcepcion() throw () {
}

const char* EscuchaExcepcion::what() const throw () {
	std::string error("ERROR EN LA ESCUCHA DE CLIENTES! Motivo: ");
	error.append(motivo);
	return error.c_str();
}
