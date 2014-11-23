#include "ProtocoloGestor.h"
#include "Message_Queue/MessageQueue.h"

ProtocoloGestor::ProtocoloGestor(const std::string& nombreArchivo,
		char caracter) :
		Protocolo(nombreArchivo, caracter) {
}

ProtocoloGestor::~ProtocoloGestor() {
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

Mensaje Protocolo::recibirMensaje() const {
	Mensaje mensaje;
	try {
		cola->receiveMsg(Protocolo::idGestor, &mensaje);
	}
	catch(const MessageQueueException &e) {
		// todo
	}
	return mensaje;
}
