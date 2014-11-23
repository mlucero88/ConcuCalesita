#ifndef INTERFAZCLIENTE_H_
#define INTERFAZCLIENTE_H_

#include <string>
#include "Registro.h"

class SocketCliente;
class ProtocoloCliente;

class InterfazCliente {
public:
	InterfazCliente(const char *direccionServidor);

	bool crearSocket();
	bool conectarAlServidor();
	bool solicitarId();
	bool cerrarSocket();

	bool conectarAlGestor(const std::string& nombreArchivo, char caracter);
	bool agregarRegistro(const Registro& registro);
	bool obtenerTabla(const Registro& registro);

	~InterfazCliente();

private:
	void enviarComandoAlServidor(const std::string &comando);
	std::string recibirRespuestaDelServidor();

	SocketCliente *cliente;
	ProtocoloCliente* protocolo;
	int idCliente;
};

#endif
