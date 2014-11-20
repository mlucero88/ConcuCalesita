#include "MessageQueue.h"
#include <sys/msg.h>

template < class T >
MessageQueue< T >::MessageQueue(const std::string& filename, char character) {
	key_t key = ftok(filename.c_str(), character);

	if (key > 0) {
		msgId = msgget(key, 0666 | IPC_CREAT);
		if (msgId < 0) {
			throw MessageQueueException(MessageQueueException::msgget);
		}
	}
	else {
		throw MessageQueueException(MessageQueueException::ftok);
	}
}

template < class T >
MessageQueue< T >::~MessageQueue() {
	// Destructor sin lanzamiento de excepciones
	try {
		freeResources();
	}
	catch(const MessageQueueException &e) {
	}
}

template < class T >
void MessageQueue< T >::sendMsg(const T& message) {
	if (msgsnd(msgId, static_cast< const void* >(&message),
			sizeof(T) - sizeof(long), 0) == -1) {
		throw MessageQueueException(MessageQueueException::msgsnd);
	}
}

template < class T >
ssize_t MessageQueue< T >::receiveMsg(int type, T* buffer) const {
	ssize_t bytesReceived = msgrcv(msgId, static_cast< void * >(buffer),
			sizeof(T) - sizeof(long), type, 0);
	if (bytesReceived == -1) {
		throw MessageQueueException(MessageQueueException::msgrcv);
	}
	return bytesReceived;
}

template < class T >
void MessageQueue< T >::freeResources() const {
	if (msgctl(msgId, IPC_RMID, NULL) == -1) {
		throw MessageQueueException(MessageQueueException::msgctl);
	}
}
