#include <netdb.h>
#include <unistd.h>
#include <cstring>
#include <cerrno>

#include "Socket.h"

/* METODOS DE SOCKETADDRESS */

Socket::SocketAddress::SocketAddress() {
	memset(&direccion, 0, sizeof(direccion));
}

Socket::SocketAddress::SocketAddress(const struct sockaddr &direccion) {
	this->direccion = direccion;
}

Socket::SocketAddress::SocketAddress(const SocketAddress& aCopiar) {
	direccion = aCopiar.direccion;
}

const Socket::SocketAddress& Socket::SocketAddress::operator=(
		const SocketAddress &aAsignar) {
	direccion = aAsignar.direccion;
	return *this;
}

void Socket::SocketAddress::setFamilia(sa_family_t familia) {
	sockaddr_in *addr = (sockaddr_in*) &direccion;
	addr->sin_family = familia;
}

void Socket::SocketAddress::setPuerto(in_port_t puerto) {
	sockaddr_in *addr = (sockaddr_in*) &direccion;
	addr->sin_port = htons(puerto);
}

bool Socket::SocketAddress::setDireccionIP(const char* dirIP) {
	in_addr_t dir = inet_addr(dirIP);
	if (dir == (in_addr_t) -1) {
		return false;
	}
	sockaddr_in *addr = (sockaddr_in*) &direccion;
	addr->sin_addr.s_addr = dir;
	return true;
}

void Socket::SocketAddress::setDireccionIP(in_addr_t dirIP) {
	sockaddr_in *addr = (sockaddr_in*) &direccion;
	addr->sin_addr.s_addr = htonl(dirIP);
}

bool Socket::SocketAddress::setDireccionIPconDNS(const char *dirDNS) {
	struct hostent *he;
	he = gethostbyname(dirDNS);
	if (he == NULL) {
		return false;
	}
	sockaddr_in *addr = (sockaddr_in*) &direccion;
	addr->sin_addr = *((struct in_addr*) he->h_addr);
	return true;
}

in_port_t Socket::SocketAddress::getPuerto() const {
	return ntohs(((sockaddr_in*) &direccion)->sin_port);
}

void Socket::SocketAddress::getDireccionIP(std::string &aGuardarIP) const {
	aGuardarIP = inet_ntoa(((sockaddr_in*) &direccion)->sin_addr);
}

const struct sockaddr* Socket::SocketAddress::getDireccion() const {
	return &direccion;
}

Socket::SocketAddress::~SocketAddress() {
}

/* METODOS DE SOCKET */

Socket::Socket(int dominio, int tipo, int protocolo) :
		direccion(), dominio(dominio), tipo(tipo), protocolo(protocolo),
				sockfd(-1) {
}

Socket::Socket(int dominio, int tipo, int protocolo, const struct sockaddr &dir) :
		direccion(dir), dominio(dominio), tipo(tipo), protocolo(protocolo),
				sockfd(-1) {
}

Socket::Socket(const Socket& aCopiar) :
		direccion(aCopiar.direccion), dominio(aCopiar.dominio),
				tipo(aCopiar.tipo), protocolo(aCopiar.protocolo),
				sockfd(aCopiar.sockfd) {
}

void Socket::crear() {
	sockfd = socket(dominio, tipo, protocolo);
	if (sockfd == -1) {
		throw CreacionExcepcion(strerror(errno));
	}
}

void Socket::cortarComunicacion(enum sentido_corte sentido) {
	if (shutdown(sockfd, sentido) == -1) {
		throw CierreExcepcion(strerror(errno));
	}
}

void Socket::cerrar() {
	if (close(sockfd) == -1) {
		throw CierreExcepcion(strerror(errno));
	}
}

Socket::~Socket() {
}
