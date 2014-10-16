#include "Administrador.h"
#include "Shared_Memory/SharedMemoryBlock.h"
#include "FilePaths.h"
#include <iostream>
#include <cstring>
#include <sstream>

Administrador::Administrador() :
		finalizar(false) {
	try {
		memoriaCompartida = new SharedMemoryBlock(
				Paths::getSharedMemoryFilename(),
				Paths::getSharedMemoryCharacter());
	}
	catch(const SharedMemoryException& e) {
		std::string ex("Error al crear la memoria compartida. ");
		ex.append(e.what());
		throw ex;
	}
}

Administrador::~Administrador() {
	try {
		memoriaCompartida->freeResources();
	}
	catch(const SharedMemoryException &e) {
		std::cerr << "Error al liberar la memoria compartida. " << e.what()
				<< std::endl;
	}
	delete memoriaCompartida;
}

void Administrador::iniciar() {
	while (!finalizar) {
		mostrarOpciones();
		ejecutarOpcion(solicitarOpcion());
	}
}

void Administrador::mostrarOpciones() const {
	std::cout << "Opciones:" << std::endl;
	std::cout << "1 - Consultar saldo" << std::endl;
	std::cout << "2 - Salir" << std::endl << std::endl;
}

int Administrador::solicitarOpcion() const {
	std::string ingreso;
	int opcion;
	std::cout << "Por favor ingrese su opción: ";
	std::cin >> ingreso;
	std::cout << std::endl;
	std::istringstream ss(ingreso);
	ss >> opcion;
	return opcion;
}

void Administrador::ejecutarOpcion(int opcion) {
	switch (opcion) {
	case SALDO: {
		consultarSaldo();
		break;
	}
	case SALIR: {
		finalizar = true;
		break;
	}
	default: {
		std::cout << "Opción no válida" << std::endl << std::endl;
		break;
	}
	}
}

void Administrador::consultarSaldo() const {
	double saldo = 0;
	ByteStream stream;
	try {
		size_t bytes = memoriaCompartida->read(stream);
		if (bytes >= sizeof(saldo)) {
			const byte_t* data = stream.obtenerStream();
			memcpy(&saldo, data, sizeof(saldo));
			std::cout << "Saldo: $" << saldo << std::endl << std::endl;
		}
		else {
			std::cout << "En este momento no se puede acceder a la caja. Por "
					"favor intentelo más tarde." << std::endl << std::endl;
		}
	}
	catch(SharedMemoryException& e) {
		std::cerr << "Error al consultar el saldo. " << e.what() << std::endl;
	}
}
