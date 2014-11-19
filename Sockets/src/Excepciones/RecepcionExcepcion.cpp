#include "RecepcionExcepcion.h"

RecepcionExcepcion::RecepcionExcepcion(const char *motivo,
		t_re_cod_error codigo) throw () : SocketExcepcion(motivo) {
	this->codigo = codigo;
}

RecepcionExcepcion::t_re_cod_error RecepcionExcepcion::obtenerCodigoError(
		) const throw () {
	return codigo;
}

RecepcionExcepcion::~RecepcionExcepcion() throw () {
}

const char* RecepcionExcepcion::what() const throw () {
	std::string error("ERROR EN LA RECEPCION! Motivo: ");
	error.append(motivo);
	return error.c_str();
}
