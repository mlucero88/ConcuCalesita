#include "LockException.h"
#include <cerrno>
#include <cstring>

LockException::LockException(enum FunctionCode fnCode) throw() :
		error_message("Error in "), code(fnCode) {
	switch (fnCode) {
	case invalidFile: {
		error_message.append("open() - ");
		break;
	}
	case fcntl: {
		error_message.append("fcntl() - ");
		break;
	}
	}
	error_message.append(strerror(errno));
}

LockException::~LockException() throw() {
}

LockException::FunctionCode LockException::getCode() const throw() {
	return code;
}

const char* LockException::what() const throw() {
	return error_message.c_str();
}
