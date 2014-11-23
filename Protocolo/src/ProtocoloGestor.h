#ifndef PROTOCOLOGESTOR_H_
#define PROTOCOLOGESTOR_H_

#include "Protocolo.h"

class ProtocoloGestor: public Protocolo {
public:
	ProtocoloGestor(const std::string& nombreArchivo,
			char caracter) /* throw (std::string) */;
	~ProtocoloGestor();

	bool enviarOperacionExitosa(long idCliente);
	bool enviarOperacionFallida(long idCliente);
	bool enviarComandoDesconocido(long idCliente);

	Mensaje recibirMensaje() const;

private:

	bool enviarResultado(long idCliente, enum Protocolo::comando cmd);

	// Prohibo las siguientes operaciones
	ProtocoloGestor(const ProtocoloGestor&);
	ProtocoloGestor& operator=(const ProtocoloGestor&);
};

#endif
