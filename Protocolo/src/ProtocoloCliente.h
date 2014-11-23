#ifndef PROTOCOLOCLIENTE_H_
#define PROTOCOLOCLIENTE_H_

#include "Protocolo.h"

class ProtocoloCliente: public Protocolo {
public:
	ProtocoloCliente(const std::string& nombreArchivo, char caracter,
			long idCliente) /* throw (std::string) */;
	~ProtocoloCliente();

	bool enviarAgregarRegistro(const Registro &registro);
	bool enviarSolicitarTabla();

	Mensaje recibirMensaje() const;

private:
	const long idCliente;

	// Prohibo las siguientes operaciones
	ProtocoloCliente(const ProtocoloCliente&);
	ProtocoloCliente& operator=(const ProtocoloCliente&);
};

#endif
