#include "Lock.h"
#include <unistd.h>

Lock::Lock(const std::string& filename) :
		filename(filename), fd(0) {
	fd = open(filename.c_str(), O_CREAT | O_RDWR, 0777);
	if (fd == -1) {
		throw LockException(LockException::invalidFile);
	}
	fl.l_whence = SEEK_SET;
	fl.l_start = 0;
	fl.l_len = 0;
}

void Lock::seizeSharedLock() {
	fl.l_type = F_RDLCK;
	if (fcntl(fd, F_SETLKW, &fl) == -1) {
		throw LockException(LockException::fcntl);
	}
}

void Lock::seizeExclusiveLock() {
	fl.l_type = F_WRLCK;
	if (fcntl(fd, F_SETLKW, &fl) == -1) {
		throw LockException(LockException::fcntl);
	}
}

void Lock::releaseLock() {
	fl.l_type = F_UNLCK;
	if (fcntl(fd, F_SETLK, &fl) == -1) {
		throw LockException(LockException::fcntl);
	}
}

Lock::~Lock() {
	close(fd);
}
