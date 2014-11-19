#include "Boleteria.h"
#include "Shared_Memory/SharedMemoryBlock.h"
#include "FilePaths.h"
#include "Logger.h"
#include <iostream>

Boleteria::Boleteria(double precioBoleto) :
		traductor(),
				deserializadorGenerador(traductor,
						Paths::getFifoGeneradorBoleteriaFilename()),
				serializadorCalesita(traductor,
						Paths::getFifoBoleteriaCalesitaFilename()), caja(),
				precioBoleto(precioBoleto) {
	try {
		memoriaCompartida = new SharedMemoryBlock(
				Paths::getSharedMemoryFilename(),
				Paths::getSharedMemoryCharacter(), sizeof(double));
		actualizarSaldo();
	}
	catch(const SharedMemoryException& e) {
		std::string ex("Error al crear la memoria compartida. ");
		ex.append(e.what());
		throw ex;
	}
	LOGGER.log("BOLETERIA ABIERTA");
}

Boleteria::~Boleteria() {
	try {
		memoriaCompartida->freeResources();
	}
	catch(const SharedMemoryException &e) {
		std::cerr << "Error al liberar la memoria compartida. " << e.what()
				<< std::endl;
	}
	delete memoriaCompartida;
	LOGGER.log("BOLETERIA CERRADA");
}

void Boleteria::atenderNinio() {
	// Recibe ninio del generador
	Ninio ninio = deserializadorGenerador.deserializar();
	ninio.siguienteEstado();
	caja.insertarDinero(precioBoleto);
	actualizarSaldo();
	// Manda ninio por el fifo a la calesita
	ninio.siguienteEstado();
	serializadorCalesita.serializar(ninio);
}

void Boleteria::actualizarSaldo() {
	memoriaCompartida->write(caja.serializar());
}

void Boleteria::closePipe() {
	serializadorCalesita.cerrar();
}
