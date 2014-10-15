#ifndef SIGINT_HANDLER_H_
#define SIGINT_HANDLER_H_

#include <signal.h>
#include <assert.h>

#include "EventHandler.h"

class PipeSignalHandler: public EventHandler {

public:

	PipeSignalHandler() {
	}

	~PipeSignalHandler() {
	}

	virtual int handleSignal(int signum) {
		assert(signum == SIGPIPE);
		return 0;
	}

};

#endif /* SIGINT_HANDLER_H_ */
