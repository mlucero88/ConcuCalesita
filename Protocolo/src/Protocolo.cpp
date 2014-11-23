#include "Protocolo.h"
#include "Message_Queue/MessageQueue.h"

Protocolo::Protocolo(const std::string& nombreArchivo, char caracter) :
		cola(NULL) {
	try {
		cola = new MessageQueue< Mensaje >(nombreArchivo, caracter);
	}
	catch(const MessageQueueException &e) {
		throw std::string(e.what());
	}
}

Protocolo::~Protocolo() {
	if (cola) {
		try {
			cola->freeResources();
		}
		catch(const MessageQueueException &e) {
		}
		delete cola;
	}
}
