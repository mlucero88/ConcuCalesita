#ifndef INTERFAZCLIENTE_H_
#define INTERFAZCLIENTE_H_

#include <string>

class SocketCliente;

class InterfazCliente {
public:
	explicit InterfazCliente(const char *direccionServidor);
	bool crearSocket();
	bool conectarAlServidor();
	bool solicitarId();
	bool cerrarSocket();
	~InterfazCliente();

	int getId() const {
		 return idColaMensaje;
	}

private:
	void enviarComando(const std::string &comando);
	std::string recibirRespuesta();

	SocketCliente *cliente;
	int idColaMensaje;
};

#endif
