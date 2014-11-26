#include "ProtocoloGestor.h"
#include "Message_Queue/MessageQueue.h"

ProtocoloGestor::ProtocoloGestor(const std::string& nombreArchivo,
		char caracter) :
		cola(NULL) {
	try {
		cola = new MessageQueue< Mensaje >(nombreArchivo, caracter);
	}
	catch(const MessageQueueException &e) {
		throw std::string(e.what());
	}
}

ProtocoloGestor::~ProtocoloGestor() {
	if (cola) {
		try {
			cola->destroy();
		}
		catch(const MessageQueueException &e) {
		}
		delete cola;
	}
}

bool ProtocoloGestor::enviarOperacionExitosa(long idCliente) {
	return enviarResultado(idCliente, Protocolo::op_success);
}

bool ProtocoloGestor::enviarOperacionFallida(long idCliente) {
	return enviarResultado(idCliente, Protocolo::op_failure);
}

bool ProtocoloGestor::enviarComandoDesconocido(long idCliente) {
	return enviarResultado(idCliente, Protocolo::cmd_unknown);
}

bool ProtocoloGestor::enviarRegistro(long idCliente, const Registro& registro) {
	Mensaje mensaje;
	mensaje.mtype = idCliente;
	mensaje.idRemitente = Protocolo::idGestor;
	mensaje.comando = Protocolo::reg_send;
	mensaje.registro = registro;
	try {
		cola->sendMsg(mensaje);
		return true;
	}
	catch(const MessageQueueException &e) {
		return false;
	}
}

bool ProtocoloGestor::enviarResultado(long idCliente,
		enum Protocolo::comando cmd) {
	Mensaje mensaje;
	mensaje.mtype = idCliente;
	mensaje.idRemitente = Protocolo::idGestor;
	mensaje.comando = cmd;
	try {
		cola->sendMsg(mensaje);
		return true;
	}
	catch(const MessageQueueException &e) {
		return false;
	}
}

Mensaje ProtocoloGestor::recibirMensaje() const {
	Mensaje mensaje;
	try {
		cola->receiveMsg(Protocolo::idGestor, &mensaje);
	}
	catch(const MessageQueueException &e) {
		std::string str("No se pudo recibir el mensaje: ");
		str.append(e.what());
		throw str;
	}
	return mensaje;
}
