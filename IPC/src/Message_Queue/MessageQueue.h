#ifndef MESSAGEQUEUE_H_
#define MESSAGEQUEUE_H_

#include "MessageQueueException.h"
#include <sys/types.h>

template < class T > class MessageQueue {
public:
	MessageQueue(const std::string& filename,
			char character) /* throw (MessageQueueException) */;
	~MessageQueue();

	void sendMsg(const T& message) /* throw (MessageQueueException) */;
	ssize_t receiveMsg(int type,
			T* buffer) const /* throw (MessageQueueException) */;
	void freeResources() const /* throw (MessageQueueException) */;

private:
	int msgId;

	// Prohibo las siguientes operaciones
	MessageQueue(const MessageQueue&);
	MessageQueue& operator=(const MessageQueue&);
};

#endif
