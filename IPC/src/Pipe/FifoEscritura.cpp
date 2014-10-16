#include "FifoEscritura.h"

#include <cerrno>
#include <cstring>
#include <stdexcept>
FifoEscritura::FifoEscritura(const std::string nombre) :
		Fifo(nombre) {
}

FifoEscritura::~FifoEscritura() {
}

void FifoEscritura::abrir() {
	fd = open(nombre.c_str(), O_WRONLY);
	if (fd < 0) {
		throw std::runtime_error(strerror(errno));
	}
}

ssize_t FifoEscritura::escribir(const void* buffer, const ssize_t buffsize) const {
	ssize_t bytesWritten = 0;
	while (bytesWritten != buffsize) {
		ssize_t res = write(fd, ((char*) buffer + bytesWritten), buffsize - bytesWritten);
		if (res <= 0) {
			throw std::runtime_error(strerror(errno));
		} else {
			bytesWritten += res;
		}
	}
	return bytesWritten;
}
