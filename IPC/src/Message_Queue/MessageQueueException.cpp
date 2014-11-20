#include "MessageQueueException.h"
#include <cerrno>
#include <cstring>

MessageQueueException::MessageQueueException(enum FunctionCode fnCode) throw() :
		error_message("Error in "), code(fnCode) {
	switch (fnCode) {
	case msgget:
		error_message.append("msgget() - ");
		break;
	case ftok:
		error_message.append("ftok() - ");
		break;
	case msgctl:
		error_message.append("msgclt() - ");
		break;
	case msgsnd:
		error_message.append("msgsnd() - ");
		return;
	case msgrcv:
		error_message.append("msgrcv() - ");
		return;
	}
	error_message.append(strerror(errno));
}

MessageQueueException::~MessageQueueException() throw() {
}

MessageQueueException::FunctionCode MessageQueueException::getCode() const throw() {
	return code;
}

const char* MessageQueueException::what() const throw() {
	return error_message.c_str();
}
