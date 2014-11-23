#include "ProtocoloCliente.h"
#include "Message_Queue/MessageQueue.h"

ProtocoloCliente::ProtocoloCliente(const std::string& nombreArchivo,
		char caracter, long idCliente) :
		cola(NULL), idCliente(idCliente) {
	try {
		cola = new MessageQueue< Mensaje >(nombreArchivo, caracter);
	}
	catch(const MessageQueueException &e) {
		throw std::string(e.what());
	}
}

ProtocoloCliente::~ProtocoloCliente() {
	if (cola) {
		try {
			cola->freeResources();
		}
		catch(const MessageQueueException &e) {
		}
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

Mensaje ProtocoloCliente::recibirMensaje() const {
	Mensaje mensaje;
	try {
		cola->receiveMsg(idCliente, &mensaje);
	}
	catch(const MessageQueueException &e) {
		// todo
	}
	return mensaje;
}
