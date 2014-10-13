#include "Boleteria.h"
#include "Shared_Memory/SharedMemoryBlock.h"
#include <cstdlib>
#include <cstring>
#include <iostream>

static const std::string nombreArchivo(
		"/home/martin/Repositorios/ConcuCalesita/IPC_Test/src/IPC_Test.cpp");
static const char caracter = 'M';

Boleteria::Boleteria(double precioBoleto, unsigned cantidadBoletos) :
		caja(), precioBoleto(precioBoleto), cantidadBoletos(cantidadBoletos) {
	try {
		memoriaCompartida = new SharedMemoryBlock(nombreArchivo, caracter,
				sizeof(double));
		actualizarSaldo();
	}
	catch(SharedMemoryException& e) {
		std::cerr << "Error al crear la memoria compartida. " << e.what()
				<< std::endl;
		exit(EXIT_FAILURE);
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

//void Boleteria::atenderNinio(const Ninio& ninio) {
//	// fijarse si ninio tiene dinero
//	// darle boleto, decrementar cantidad de boletos en uno
//	// agregar dinero a la caja
//}

void Boleteria::actualizarSaldo() {
	memoriaCompartida->write(caja.serializar());
}
