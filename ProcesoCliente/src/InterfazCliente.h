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

	void realizarAccion();
	bool yaFinalizo() const;

	int getId() const;

	~InterfazCliente();

private:
	void enviarComandoAlServidor(const std::string &comando);
	std::string recibirRespuestaDelServidor();

	void mostrarAcciones() const;
	void agregarRegistro();
	void obtenerTabla();

	SocketCliente *cliente;
	ProtocoloCliente* protocolo;
	int idCliente;
	bool finalizo;
};

#endif
