#ifndef NINIO_H
#define NINIO_H

#include "EstadosNinio.h"
#include <string>

class Ninio {
public:

	Ninio(const std::string& nombre);

	void siguienteEstado();

	Estado getEstado() const;

	void setEstado(Estado estado);

	const std::string& getNombre() const;

	void setNombre(const std::string& nombre);

	unsigned getUbicacionPreferida(unsigned cantidadUbicaciones) const;

private:
	std::string nombre;
	Estado estado;
};
#endif
