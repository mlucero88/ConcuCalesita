#ifndef SHAREDMEMORYBLOCK_H_
#define SHAREDMEMORYBLOCK_H_

#include "SharedMemoryException.h"

class SharedMemoryData;
class ByteStream;

class SharedMemoryBlock {

public:
	SharedMemoryBlock(const std::string& file, char character);
	~SharedMemoryBlock();
	void write(const SharedMemoryData& data);
	void read(SharedMemoryData &data) const;

private:
	ByteStream* ptrData;
	int shmId;

	int getAmountProcessesAttached() const;

	SharedMemoryBlock(const SharedMemoryBlock& copy);
	SharedMemoryBlock& operator=(const SharedMemoryBlock& copy);
};

#endif
