#include "SharedMemoryBlock.h"
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <cstring>

SharedMemoryBlock::SharedMemoryBlock(const std::string& filename,
		char character, size_t blockSize) :
		lock(filename), blockSize(blockSize) {
	key_t key = ftok(filename.c_str(), character);

	if (key > 0) {
		shmId = shmget(key, blockSize + sizeof(size_t), 0644 | IPC_CREAT);

		if (shmId > 0) {
			void* tmpPtr = shmat(shmId, NULL, 0);
			if (tmpPtr != (void*) -1) {
				ptrData = static_cast< byte_t* >(tmpPtr);
			}
			else {
				if (getAmountProcessesAttached() == 0) {
					shmctl(shmId, IPC_RMID, NULL);
				}
				throw SharedMemoryException(SharedMemoryException::shmat);
			}
		}
		else {
			throw SharedMemoryException(SharedMemoryException::shmget);
		}
	}
	else {
		throw SharedMemoryException(SharedMemoryException::ftok);
	}
}

size_t SharedMemoryBlock::write(const ByteStream& data) {
	size_t dataSize = data.getTamanioOcupado();
	if (blockSize < dataSize) {
		throw SharedMemoryException(SharedMemoryException::write_size);
	}
	try {
		lock.seizeExclusiveLock();
		memcpy(ptrData, &dataSize, sizeof(size_t));
		memcpy(ptrData + sizeof(size_t), data.obtenerStream(), dataSize);
		lock.releaseLock();
	}
	catch(LockException &e) {
		throw SharedMemoryException(SharedMemoryException::write_lock);
	}
	return dataSize;
}

size_t SharedMemoryBlock::read(ByteStream& data) const {
	size_t dataSize = 0;
	byte_t* buffer = NULL;
	try {
		lock.seizeSharedLock();
		memcpy(&dataSize, ptrData, sizeof(size_t));
		buffer = new byte_t[dataSize];
		memcpy(buffer, ptrData + sizeof(size_t), dataSize);
		lock.releaseLock();
		data.asignarStream(buffer, dataSize);
	}
	catch(LockException &e) {
		delete[] buffer;
		throw SharedMemoryException(SharedMemoryException::read_lock);
	}
	delete[] buffer;
	return dataSize;
}

void SharedMemoryBlock::freeResources() const {
	if (shmdt(static_cast< void* >(ptrData)) != -1) {
		if (getAmountProcessesAttached() == 0) {
			if (shmctl(shmId, IPC_RMID, NULL) == -1) {
				throw SharedMemoryException(SharedMemoryException::shmctl);
			}
		}
	}
	else {
		throw SharedMemoryException(SharedMemoryException::shmdt);
	}
}

SharedMemoryBlock::~SharedMemoryBlock() {
	// Destructor sin lanzamiento de excepciones
	try {
		freeResources();
	}
	catch(const SharedMemoryException &e) {
	}
}

int SharedMemoryBlock::getAmountProcessesAttached() const {
	shmid_ds state;
	shmctl(shmId, IPC_STAT, &state);
	return state.shm_nattch;
}
