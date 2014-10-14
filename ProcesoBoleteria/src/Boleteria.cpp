#include "Boleteria.h"
#include "Shared_Memory/SharedMemoryBlock.h"
#include "FilePaths.h"
#include <iostream>

Boleteria::Boleteria(double precioBoleto) :
		caja(), precioBoleto(precioBoleto) {
	try {
		memoriaCompartida = new SharedMemoryBlock(
				Paths::getSharedMemoryFilename(),
				Paths::getSharedMemoryCharacter(), sizeof(double));
		actualizarSaldo();
	}
	catch(SharedMemoryException& e) {
		std::string ex("Error al crear la memoria compartida. ");
		ex.append(e.what());
		throw ex;
	}
}

Boleteria::~Boleteria() {
	try {
		memoriaCompartida->freeResources();
	}
	catch(SharedMemoryException &e) {
		std::cerr << "Error al liberar la memoria compartida. " << e.what()
				<< std::endl;
	}
	delete memoriaCompartida;
}

void Boleteria::atenderNinio() {
	// todo
	// sacar ninio del fifo
	caja.insertarDinero(precioBoleto);
	// mandar ninio por el fifo a la calesita
}

void Boleteria::actualizarSaldo() {
	memoriaCompartida->write(caja.serializar());
}
