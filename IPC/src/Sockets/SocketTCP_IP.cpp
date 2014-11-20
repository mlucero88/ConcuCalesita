#include "SocketTCP_IP.h"
#include <cstring>
#include <cerrno>

static const int FLAGS = 0;

SocketTCP_IP::SocketTCP_IP(int protocolo) :
		Socket(AF_INET, SOCK_STREAM, protocolo) {
	direccion.setFamilia(AF_INET);
}

SocketTCP_IP::SocketTCP_IP(const struct sockaddr &dir, int protocolo) :
		Socket(AF_INET, SOCK_STREAM, protocolo, dir) {
}

SocketTCP_IP::SocketTCP_IP(const SocketTCP_IP &socket) :
		Socket(socket.tipo, socket.tipo, socket.protocolo) {
	direccion = socket.direccion;
	sockfd = socket.sockfd;
}

in_port_t SocketTCP_IP::getPuerto() const {
	return direccion.getPuerto();
}

std::string SocketTCP_IP::getDireccionIP() const {
	std::string str;
	direccion.getDireccionIP(str);
	return str;
}

ssize_t SocketTCP_IP::enviar(const ByteStream &buffer) const {
	ssize_t bytesEnviados;
	bytesEnviados = send(sockfd, buffer.obtenerStream(),
			buffer.getTamanioOcupado(), FLAGS);

	if (bytesEnviados == -1) {
		throw EnvioExcepcion(strerror(errno));
	}
	return bytesEnviados;
}

ssize_t SocketTCP_IP::recibir(ByteStream &buffer) const {
	ssize_t bytesRecibidos;
	byte_t *tempBuffer = new byte_t[buffer.getCapacidadTotal()];
	bytesRecibidos = recv(sockfd, tempBuffer, buffer.getCapacidadTotal(),
			FLAGS);

	if (bytesRecibidos > 0) {
		buffer.asignarStream(tempBuffer, bytesRecibidos);
	}
	delete[] tempBuffer;

	if (bytesRecibidos == -1) {
		throw RecepcionExcepcion(strerror(errno),
				RecepcionExcepcion::error_recepcion);
	}
	if (bytesRecibidos == 0) {
		throw RecepcionExcepcion(strerror(errno),
				RecepcionExcepcion::usuario_desconectado);
	}
	return bytesRecibidos;
}

SocketTCP_IP::~SocketTCP_IP() {
}
