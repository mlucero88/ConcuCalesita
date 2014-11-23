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

	void atenderCliente();

private:
	std::vector< Registro > tabla;
	ProtocoloGestor protocolo;

	bool agregarRegistro(const Registro& registro);
};

#endif
