#include "InterfazCliente.h"
#include "Sockets/SocketCliente.h"
#include "Common/ByteStream.h"
#include "ProtocoloCliente.h"
#include <iostream>
#include <cstdlib>

static const int buffer_size = 50;
static const std::string cmd_id_recibido = "OK";
static const char cmd_fin_comando = '\n';

InterfazCliente::InterfazCliente(const char *direccionServidor) :
		cliente(NULL), protocolo(NULL), idCliente(-1) {
	std::string direccion(direccionServidor);
	unsigned int delimitador = direccion.find_first_of(':');
	in_port_t puerto = (in_port_t) atoi(
			direccion.substr(delimitador + 1).c_str());
	direccion.erase(delimitador);
	cliente = new SocketCliente(puerto, direccion);
}

bool InterfazCliente::crearSocket() {
	try {
		cliente->crear();
		return true;
	}
	catch(const CreacionExcepcion &ce) {
		std::cerr << ce.what() << std::endl;
	}
	return false;
}

bool InterfazCliente::conectarAlServidor() {
	try {
		cliente->conectar();
		return true;
	}
	catch(const ConexionExcepcion &ce) {
		std::cerr << ce.what() << std::endl;
	}
	return false;
}

bool InterfazCliente::solicitarId() {
	try {
		idCliente = atoi(recibirRespuestaDelServidor().c_str());
	}
	catch(const RecepcionExcepcion &re) {
		std::cerr << re.what() << std::endl;
		return false;
	}
	std::string comando = cmd_id_recibido + cmd_fin_comando;
	try {
		enviarComandoAlServidor(comando);
	}
	catch(const EnvioExcepcion &ee) {
		std::cerr << ee.what() << std::endl;
		return false;
	}
	return true;
}

bool InterfazCliente::cerrarSocket() {
	try {
		cliente->cerrar();
		return true;
	}
	catch(const CierreExcepcion &ce) {
		std::cerr << ce.what() << std::endl;
	}
	return false;
}

bool InterfazCliente::conectarAlGestor(const std::string& nombreArchivo,
		char caracter) {
	if (idCliente > 1 && protocolo == NULL) {
		try {
			protocolo = new ProtocoloCliente(nombreArchivo, caracter,
					idCliente);
			return true;
		}
		catch(const std::string &e) {
			std::cerr << e << std::endl;
		}
	}
	return false;
}

void InterfazCliente::enviarComandoAlServidor(const std::string &comando) {
	ByteStream buffer(comando.size());
	int bytesEnviados = 0;
	int bytesAenviar = comando.size();

	/* Envio de datos segun protocolo establecido */
	while (bytesEnviados < bytesAenviar) {
		buffer.asignarStream(comando.substr(bytesEnviados).c_str(),
				comando.length() - bytesEnviados);
		bytesEnviados += cliente->enviar(buffer);
	}
}

std::string InterfazCliente::recibirRespuestaDelServidor() {
	std::string respuesta;
	int bytesRecibidos = 0;
	ByteStream buffer(buffer_size);
	bool recepcionCompleta = false;

	/* Recepcion de datos segun protocolo establecido */
	while (!recepcionCompleta) {
		bytesRecibidos = cliente->recibir(buffer);
		respuesta.append(buffer.obtenerStream(), bytesRecibidos);
		if (respuesta[respuesta.length() - 1] == cmd_fin_comando) {
			/* Quito el '\n' */
			respuesta.erase(respuesta.length() - 1);
			recepcionCompleta = true;
		}
	}
	return respuesta;
}

InterfazCliente::~InterfazCliente() {
	delete cliente;
	if (protocolo != NULL) {
		delete protocolo;
	}
}
