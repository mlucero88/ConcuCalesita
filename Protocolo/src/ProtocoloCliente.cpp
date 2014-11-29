#include "ProtocoloCliente.h"
#include "Message_Queue/MessageQueue.h"
#include <cstring>

ProtocoloCliente::ProtocoloCliente(const std::string& nombreArchivo,
		char caracter, long idCliente) :
		cola(NULL), idCliente(idCliente) {
	try {
		cola = new MessageQueue< Mensaje >(nombreArchivo, caracter, false);
	}
	catch(const MessageQueueException &e) {
		throw std::string(e.what());
	}
}

ProtocoloCliente::~ProtocoloCliente() {
	// El cliente no debe destruir la cola. La destruye el gestor
	if (cola) {
		delete cola;
	}
}

bool ProtocoloCliente::enviarAgregarRegistro(const Registro &registro) {
	Mensaje mensaje;
	mensaje.mtype = Protocolo::idGestor;
	mensaje.idRemitente = idCliente;
	mensaje.comando = Protocolo::add_reg;
	mensaje.registro = registro;
	try {
		cola->sendMsg(mensaje);
		return true;
	}
	catch(const MessageQueueException &e) {
		return false;
	}
}

bool ProtocoloCliente::enviarSolicitarTabla() {
	Mensaje mensaje;
	mensaje.mtype = Protocolo::idGestor;
	mensaje.idRemitente = idCliente;
	mensaje.comando = Protocolo::get_regs;
	try {
		cola->sendMsg(mensaje);
		return true;
	}
	catch(const MessageQueueException &e) {
		return false;
	}
}

bool ProtocoloCliente::enviarSolicitarRegistroPorNombre(
		const std::string& nombre) {
	Mensaje mensaje;
	mensaje.mtype = Protocolo::idGestor;
	mensaje.idRemitente = idCliente;
	mensaje.comando = Protocolo::get_reg_by_name;
	strcpy(mensaje.registro.nombre, nombre.c_str());
	try {
		cola->sendMsg(mensaje);
		return true;
	}
	catch(const MessageQueueException &e) {
		return false;
	}
}

Mensaje ProtocoloCliente::recibirMensaje() const {
	Mensaje mensaje;
	try {
		cola->receiveMsg(idCliente, mensaje);
	}
	catch(const MessageQueueException &e) {
		std::string str("No se pudo recibir el mensaje: ");
		str.append(e.what());
		throw str;
	}
	return mensaje;
}
