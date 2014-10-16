#include "Fifo.h"

#include <cerrno>
#include <cstring>
#include <stdexcept>
Fifo::Fifo(const std::string nombre) :
		nombre(nombre), fd(-1) {
	int res = mknod(static_cast<const char*>(nombre.c_str()), S_IFIFO | 0666, 0);
//	if (res != 0) {
//		throw std::runtime_error(strerror(errno));
//	}
}

Fifo::~Fifo() {
}

void Fifo::cerrar() {
	close(fd);
	fd = -1;
}

void Fifo::eliminar() const {
	unlink(nombre.c_str());
}
