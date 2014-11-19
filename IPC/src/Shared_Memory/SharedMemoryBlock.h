#ifndef SHAREDMEMORYBLOCK_H_
#define SHAREDMEMORYBLOCK_H_

#include "SharedMemoryException.h"
#include "../Common/ByteStream.h"
#include "../Lock/Lock.h"

class SharedMemoryBlock {

public:
	SharedMemoryBlock(const std::string& filename, char character,
			size_t blocKSize = 0) /* throw (SharedMemoryException) */;
	~SharedMemoryBlock();
	size_t write(const ByteStream& data) /* throw (SharedMemoryException) */;
	size_t read(ByteStream& data) const /* throw (SharedMemoryException) */;
	void freeResources() const /* throw (SharedMemoryException) */;

private:
	mutable Lock lock;
	byte_t* ptrData;
	size_t blockSize;
	int shmId;

	int getAmountProcessesAttached() const;

	// Prohibo las siguientes operaciones
	SharedMemoryBlock(const SharedMemoryBlock&);
	SharedMemoryBlock& operator=(const SharedMemoryBlock&);
};

#endif
