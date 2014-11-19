#include "SocketCliente.h"
#include <cstring>
#include <cerrno>

SocketCliente::SocketCliente(in_port_t puertoDestino, in_addr_t dirIPdestino,
		int protocolo) :
		SocketTCP_IP(protocolo) {
	direccion.setPuerto(puertoDestino);
	direccion.setDireccionIP(dirIPdestino);
}

SocketCliente::SocketCliente(in_port_t puertoDestino, const char *dirIPdestino,
		int protocolo) :
		SocketTCP_IP(protocolo) {
	direccion.setPuerto(puertoDestino);
	direccion.setDireccionIP(dirIPdestino);
}

SocketCliente::SocketCliente(in_port_t puertoDestino,
		const std::string &dirDNSdestino, int protocolo) :
		SocketTCP_IP(protocolo) {
	direccion.setPuerto(puertoDestino);
	direccion.setDireccionIPconDNS(dirDNSdestino.c_str());
}

SocketCliente::SocketCliente(socket_t socket, const struct sockaddr &dir,
		int protocolo) :
		SocketTCP_IP(dir, protocolo) {
	sockfd = socket;
}

SocketCliente::SocketCliente(const SocketCliente &cliente) :
		SocketTCP_IP(cliente.protocolo) {
	direccion = cliente.direccion;
	sockfd = cliente.sockfd;
}

void SocketCliente::conectar() {
	int resultadoConectar = connect(sockfd, direccion.getDireccion(),
			sizeof(struct sockaddr));
	if (resultadoConectar == -1) {
		throw ConexionExcepcion(strerror(errno));
	}
}

SocketCliente::~SocketCliente() {
}
