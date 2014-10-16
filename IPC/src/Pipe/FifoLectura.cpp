#include "FifoLectura.h"

#include <cerrno>
#include <cstring>
#include <stdexcept>
FifoLectura::FifoLectura(const std::string nombre) :
		Fifo(nombre) {
}

FifoLectura::~FifoLectura() {
}

void FifoLectura::abrir() {
	fd = open(nombre.c_str(), O_RDONLY);
	if (fd < 0) {
		throw std::runtime_error(strerror(errno));
	}
}

ssize_t FifoLectura::leer(void* buffer, const ssize_t buffsize) const {
	ssize_t bytesRead = 0;
	while (bytesRead != buffsize) {
		ssize_t res = read(fd, ((char*) buffer + bytesRead), buffsize - bytesRead);
		if (res < 0) {
			throw std::runtime_error(strerror(errno));
		} else if (res == 0) {
			throw std::logic_error(strerror(errno));
		} else {
			bytesRead += res;
		}
	}
	return bytesRead;
}
