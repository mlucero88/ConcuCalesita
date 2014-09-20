#include "SharedMemoryBlock.h"
#include "SharedMemoryData.h"
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#include <iostream>
#include <cerrno>
#include <cstring>

SharedMemoryBlock::SharedMemoryBlock(const std::string& file, char character) {
	key_t key = ftok(file.c_str(), character);

	if (key > 0) {
		// todo Poder setear permisos?
		shmId = shmget(key, sizeof(ByteStream), 0644 | IPC_CREAT);

		if (shmId > 0) {
			void* tmpPtr = shmat(shmId, NULL, 0);
			if (tmpPtr != (void*) -1) {
				ptrData = static_cast< ByteStream* >(tmpPtr);
			}
			else {
				// todo Liberar la memoria obtenida en shmget?
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

SharedMemoryBlock::~SharedMemoryBlock() {
	int errorDt = shmdt(static_cast< void* >(ptrData));

	if (errorDt != -1) {
		if (getAmountProcessesAttached() == 0) {
			shmctl(this->shmId, IPC_RMID, NULL);
		}
	}
	else {
		// todo Buscar otra forma y sacar iostream
		std::cerr << "Error en shmdt(): " << strerror(errno) << std::endl;
	}
}

void SharedMemoryBlock::write(const SharedMemoryData &data) {
	// todo Hacer boundcheck
	*ptrData = data.serialize();
}

void SharedMemoryBlock::read(SharedMemoryData &data) const {
	data.hidratate(*ptrData);
}

int SharedMemoryBlock::getAmountProcessesAttached() const {
// todo genera excepciones?
	shmid_ds state;
	shmctl(shmId, IPC_STAT, &state);
	return state.shm_nattch;
}
