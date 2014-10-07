#include "SharedMemoryException.h"
#include <cerrno>
#include <cstring>

SharedMemoryException::SharedMemoryException(enum FunctionCode fnCode) throw() :
		error_message("Error in "), code(fnCode) {
	switch (fnCode) {
	case shmget:
		error_message.append("shmget() - ");
		break;
	case shmat:
		error_message.append("shmgat() - ");
		break;
	case shmdt:
		error_message.append("shmgdt() - ");
		break;
	case shmctl:
		error_message.append("shmctl() - ");
		break;
	case ftok:
		error_message.append("ftok() - ");
		break;
	}
	error_message.append(strerror(errno));
}

SharedMemoryException::~SharedMemoryException() throw() {
}

SharedMemoryException::FunctionCode SharedMemoryException::getCode() const throw() {
	return code;
}

const char* SharedMemoryException::what() const throw() {
	return error_message.c_str();
}
