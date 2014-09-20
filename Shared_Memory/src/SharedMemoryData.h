#ifndef SHAREDMEMORYDATA_H_
#define SHAREDMEMORYDATA_H_

#include "ByteStream.h"

class SharedMemoryData {
public:
	virtual ~SharedMemoryData();

	virtual const ByteStream serialize() const = 0;
	virtual void hidratate(const ByteStream& stream) = 0;
};

#endif
