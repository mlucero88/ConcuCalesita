#ifndef LOCK_H_
#define LOCK_H_

#include <fcntl.h>
#include "LockException.h"

class Lock {
public:

	Lock(const std::string& filename);
	~Lock();

	void seizeSharedLock();
	void seizeExclusiveLock();
	void releaseLock();

private:
	std::string filename;
	struct flock fl;
	int fd;
};

#endif
