#ifndef GESTOR_H_
#define GESTOR_H_

#include "ProtocoloGestor.h"
#include <vector>

class Gestor {
public:
	Gestor(const std::string& nombreArchivo,
			char caracter) /* throw (std::string) */;
	~Gestor();

	bool cargarTabla(const std::string& nombreArchivo);
	bool persistirTabla(const std::string& nombreArchivo) const;

	void agregarRegistro(const Registro& registro);
	const std::vector< Registro >& retornarTabla() const;

private:
	std::vector< Registro > tabla;
	ProtocoloGestor protocolo;
};

#endif
