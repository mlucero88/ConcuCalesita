#ifndef GESTOR_H_
#define GESTOR_H_

#include "Registro.h"
#include <vector>
#include <string>

class Gestor {
public:
	Gestor();
	~Gestor();

	bool cargarTabla(const std::string& nombreArchivo);
	bool persistirTabla(const std::string& nombreArchivo) const;

	void agregarRegistro(const Registro& registro);
	const std::vector< Registro >& retornarTabla() const;

private:
	std::vector< Registro > tabla;
};

#endif
