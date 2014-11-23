#include "InterfazServidor.h"
#include "Sockets/SocketServidor.h"
#include "Sockets/SocketCliente.h"
#include <iostream>
#include <cstdlib>
#include <cstdio>

static const int buffer_size = 50;
static const std::string cmd_id_recibido = "OK";
static const char cmd_fin_comando = '\n';
static const int id_inicial = 2;

InterfazServidor::InterfazServidor(const char *puerto) {
	servidor = new SocketServidor((in_port_t) atoi(puerto));
}

bool InterfazServidor::crearSocket() {
	try {
		servidor->crear();
		return true;
	}
	catch(const CreacionExcepcion &ce) {
		std::cerr << ce.what() << std::endl;
	}
	return false;
}

bool InterfazServidor::enlazar() {
	try {
		servidor->enlazarServidor();
		return true;
	}
	catch(const EnlaceExcepcion &ee) {
		std::cerr << ee.what() << std::endl;
	}
	return false;
}

bool InterfazServidor::escuchar(int colaMaxima) {
	try {
		servidor->escucharClientes(colaMaxima);
		return true;
	}
	catch(const EscuchaExcepcion &ee) {
		std::cerr << ee.what() << std::endl;
	}
	return false;
}

void InterfazServidor::atenderCliente() {
	static int idNuevo = id_inicial;
	SocketCliente *cliente = NULL;

	/* Intento aceptar una conexion. Si falla, se considera que el fallo fue
	 * generado por un cierre del socket servidor por parte de una senial
	 * SIGINT */
	try {
		cliente = servidor->aceptarClientes();
	}
	catch(const AceptacionExcepcion &ae) {
		return;
	}

	/* Envio un id de cola al cliente */
	ByteStream bufferEnvio(0);
	char aux[20];
	sprintf(aux, "%d%c", idNuevo, cmd_fin_comando);
	std::string mensaje(aux);
	int bytesEnviados = 0;
	int bytesAenviar = mensaje.size();
	try {
		while (bytesEnviados < bytesAenviar) {
			bufferEnvio.asignarStream(mensaje.substr(bytesEnviados).c_str(),
					mensaje.length() - bytesEnviados);
			bytesEnviados += cliente->enviar(bufferEnvio);
		}
	}
	catch(const EnvioExcepcion &ee) {
		std::cerr << ee.what() << std::endl;
		exit(EXIT_FAILURE);
	}

	/* Espero su respuesta de id recibido */
	ByteStream bufferRecepcion(buffer_size);
	mensaje.clear();
	int bytesRecibidos = 0;
	bool recepcionCompleta = false;

	try {
		/* Recepcion de datos segun protocolo establecido */
		while (!recepcionCompleta) {
			bytesRecibidos = cliente->recibir(bufferRecepcion);
			mensaje.append(bufferRecepcion.obtenerStream(), bytesRecibidos);
			if (mensaje[mensaje.length() - 1] == cmd_fin_comando) {
				/* Quito el '\n' */
				mensaje.erase(mensaje.length() - 1);
				recepcionCompleta = true;
			}
		}
	}
	catch(const RecepcionExcepcion &re) {
		if (re.obtenerCodigoError()
				== RecepcionExcepcion::usuario_desconectado) {
			return;
		}
		std::cerr << re.what() << std::endl;
		exit(EXIT_FAILURE);
	}

	/* Interpreto el mensaje del cliente */
	if (mensaje.compare(cmd_id_recibido) == 0) {
		/* Cierro el socket que se comunica con el cliente */
		try {
			cliente->cerrar();
		}
		catch(const CierreExcepcion &ce) {
			std::cerr << ce.what() << std::endl;
		}
		delete cliente;
		++idNuevo;
	}
	else {
		std::cerr << "El cliente no recibio el id correctamente\n";
	}
}

bool InterfazServidor::cerrarSocket() {
	try {
		servidor->cerrar();
		return true;
	}
	catch(const CierreExcepcion &ce) {
		std::cerr << ce.what() << std::endl;
	}
	return false;
}

InterfazServidor::~InterfazServidor() {
	delete servidor;
}
