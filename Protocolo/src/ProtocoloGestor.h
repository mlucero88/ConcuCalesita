#ifndef PROTOCOLOGESTOR_H_
#define PROTOCOLOGESTOR_H_

#include "Mensaje.h"
#include "Comandos.h"
#include <string>

template < class T >
class MessageQueue;

class ProtocoloGestor {
public:
	ProtocoloGestor(const std::string& nombreArchivo,
			char caracter) /* throw (std::string) */;
	~ProtocoloGestor();

	bool enviarOperacionExitosa(long idCliente);
	bool enviarOperacionFallida(long idCliente);
	bool enviarComandoDesconocido(long idCliente);

	bool enviarRegistro(long idCliente, const Registro& registro);

	Mensaje recibirMensaje() const;

private:
	MessageQueue< Mensaje >* cola;

	bool enviarResultado(long idCliente, enum Protocolo::comando cmd);

	// Prohibo las siguientes operaciones
	ProtocoloGestor(const ProtocoloGestor&);
	ProtocoloGestor& operator=(const ProtocoloGestor&);
};

#endif
