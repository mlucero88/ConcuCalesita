#ifndef SHAREDMEMORYBLOCK_H_
#define SHAREDMEMORYBLOCK_H_

#include "SharedMemoryException.h"
#include "../Common/ByteStream.h"
#include "../Lock/Lock.h"

class SharedMemoryBlock {

public:
	SharedMemoryBlock(const std::string& filename, char character,
			size_t blocKSize = 0);
	~SharedMemoryBlock();
	size_t write(const ByteStream& data);
	size_t read(ByteStream& data) const;
	void freeResources() const;

private:
	mutable Lock lock;
	byte_t* ptrData;
	size_t blockSize;
	int shmId;

	int getAmountProcessesAttached() const;

	// Prohibo las siguientes operaciones
	SharedMemoryBlock(const SharedMemoryBlock& copy);
	SharedMemoryBlock& operator=(const SharedMemoryBlock& copy);
};

#endif
