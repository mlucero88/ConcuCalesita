#ifndef PROTOCOLOCLIENTE_H_
#define PROTOCOLOCLIENTE_H_

#include "Mensaje.h"
#include "Comandos.h"
#include <string>

template < class T >
class MessageQueue;

class ProtocoloCliente {
public:
	ProtocoloCliente(const std::string& nombreArchivo, char caracter,
			long idCliente) /* throw (std::string) */;
	~ProtocoloCliente();

	bool enviarAgregarRegistro(const Registro &registro);
	bool enviarSolicitarTabla();

	Mensaje recibirMensaje() const /* throw (std::string) */;

private:
	MessageQueue< Mensaje >* cola;
	const long idCliente;

	// Prohibo las siguientes operaciones
	ProtocoloCliente(const ProtocoloCliente&);
	ProtocoloCliente& operator=(const ProtocoloCliente&);
};

#endif
