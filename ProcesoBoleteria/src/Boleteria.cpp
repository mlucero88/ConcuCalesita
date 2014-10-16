#include "Boleteria.h"
#include "Shared_Memory/SharedMemoryBlock.h"
#include "FilePaths.h"
#include "Logger.h"
#include <iostream>

Boleteria::Boleteria(double precioBoleto) :
		traductor(),
				serializadorCalesita(traductor,
						Paths::getFifoBoleteriaCalesitaFilename()),
				deserializadorGenerador(traductor,
						Paths::getFifoGeneradorBoleteriaFilename()), caja(),
				precioBoleto(precioBoleto) {
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
	LOGGER->Log("BOLETERIA ABIERTA");
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
	LOGGER->Log("BOLETERIA CERRADA");
}

void Boleteria::atenderNinio() {
	// Recibe ninio del generador
	Ninio ninio = deserializadorGenerador.deserializar();
	ninio.siguienteEstado();
	caja.insertarDinero(precioBoleto);
	// Manda ninio por el fifo a la calesita
	serializadorCalesita.serializar(ninio);
	ninio.siguienteEstado();
}

void Boleteria::actualizarSaldo() {
	memoriaCompartida->write(caja.serializar());
}
