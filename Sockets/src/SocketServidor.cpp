#include "SocketServidor.h"
#include "SocketCliente.h"
#include <cstring>
#include <cerrno>

SocketServidor::SocketServidor(in_port_t puerto, int protocolo) :
		SocketTCP_IP(protocolo) {
	direccion.setPuerto(puerto);
	direccion.setDireccionIP(INADDR_ANY);
}

SocketServidor::SocketServidor(const SocketServidor &servidor) :
		SocketTCP_IP(servidor.protocolo) {
	direccion = servidor.direccion;
	sockfd = servidor.sockfd;
}

void SocketServidor::enlazarServidor() {
	int resultadoEnlace = bind(sockfd, direccion.getDireccion(),
			sizeof(struct sockaddr));
	if (resultadoEnlace == -1) {
		throw EnlaceExcepcion(strerror(errno));
	}
}

void SocketServidor::escucharClientes(int colaMaxima) {
	int resultadoEscucha = listen(sockfd, colaMaxima);
	if (resultadoEscucha == -1) {
		throw EscuchaExcepcion(strerror(errno));
	}
}

SocketCliente* SocketServidor::aceptarClientes() {
	struct sockaddr address;
	socklen_t tamanio = sizeof(struct sockaddr);
	socket_t nuevoSocket = accept(sockfd, &address, &tamanio);

	if (nuevoSocket == -1) {
		throw AceptacionExcepcion(strerror(errno));
	}
	SocketCliente *nuevoCliente = new SocketCliente(nuevoSocket, address,
			protocolo);
	return nuevoCliente;
}

SocketServidor::~SocketServidor() {
}
