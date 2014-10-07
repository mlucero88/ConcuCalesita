#include <iostream>
#include <unistd.h>
#include <cstring>
#include <cstdlib>
#include <sys/wait.h>
#include <cerrno>
#include "Shared_Memory/SharedMemoryBlock.h"
#include "Lock/Lock.h"
#include "NoPointerData.h"

//#define TEST_SHAREDMEMORY
#define TEST_SHAREDMEMORYBLOCK
//#define TEST_SHAREDMEMORYDATA

//#define TEST_LOCKS

static const char* ruta =
		"/home/martin/Repositorios/ConcuCalesita/IPC_Test/src/IPC_Test.cpp";

using namespace std;

int main() {

#ifdef TEST_SHAREDMEMORY

	string archivo(ruta);
	char caracter = 'M';

	pid_t hijo = fork();
	switch (hijo) {
		case -1: {
			cout << "Error en el FORK: " << strerror(errno) << endl;
			exit(EXIT_FAILURE);
		}
		case 0: {
			int statusHijo = EXIT_SUCCESS;
			cout << "Hijo: Creado" << endl;
			/******************************************/
			/******************************************/
			try {
				SharedMemoryBlock bloqueHijo(archivo, caracter);
				NoPointerData origen(101312324, 1247.2412, '@');
				cout << "Hijo - Data: " << origen.getEntero() << " - "
				<< origen.getReal() << " - " << origen.getCaracter()
				<< endl;
				bloqueHijo.write(origen);
			}
			catch(const SharedMemoryException& e) {
				cout << e.what() << endl;
				statusHijo = EXIT_FAILURE;
			}
			/******************************************/
			/******************************************/
			cout << "Hijo: Finalizo" << endl;
			exit(statusHijo);
		}
	}
	int status;
	/******************************************/
	/******************************************/
	try {
		sleep(3);
		SharedMemoryBlock bloquePadre(archivo, caracter);
		NoPointerData destino;
		bloquePadre.read(destino);
		cout << "Padre - Data: " << destino.getEntero() << " - "
		<< destino.getReal() << " - " << destino.getCaracter() << endl;
	}
	catch(const SharedMemoryException& e) {
		cout << e.what() << endl;
	}
	/******************************************/
	/******************************************/
	if (wait(&status) == -1) {
		cout << "Padre: Error en el WAIT: " << strerror(errno) << endl;
	}
	else {
		cout << "Padre: Exito en el WAIT. Status: " << status << endl;
	}
	cout << "Padre: Finalizo" << endl;

#endif

#ifdef TEST_SHAREDMEMORYBLOCK

//#define MISMOBLOQUE

	string archivo(ruta);
	char caracter = 'M';

#ifdef MISMOBLOQUE

	try {
		SharedMemoryBlock bloque(archivo, caracter);
		NoPointerData origen(101312324, 1247.2412, '@');
		cout << "Origen: " << origen.getEntero() << " - " << origen.getReal()
		<< " - " << origen.getCaracter() << endl;
		bloque.write(origen);
		NoPointerData destino;
		bloque.read(destino);
		cout << "Destino: " << destino.getEntero() << " - " << destino.getReal()
		<< " - " << destino.getCaracter() << endl;
	}
	catch(const SharedMemoryException& e) {
		cout << e.what() << endl;
	}

#endif

#ifndef MISMOBLOQUE

	try {
		SharedMemoryBlock bloqueOrigen(archivo, caracter);
		NoPointerData origen(101312324, 1247.2412, '@');
		cout << "Origen: " << origen.getEntero() << " - " << origen.getReal()
				<< " - " << origen.getCaracter() << endl;
		bloqueOrigen.write(origen);

		SharedMemoryBlock bloqueDestino(archivo, caracter);
		NoPointerData destino;
		bloqueDestino.read(destino);
		cout << "Destino: " << destino.getEntero() << " - " << destino.getReal()
				<< " - " << destino.getCaracter() << endl;
	}
	catch(const SharedMemoryException& e) {
		cout << e.what() << endl;
	}

#endif

#endif

#ifdef TEST_SHAREDMEMORYDATA
	NoPointerData origen(101312324, 1247.2412, '@');
	cout << origen.getEntero() << " - " << origen.getReal() << " - "
	<< origen.getCaracter() << endl;

	const ByteStream stream = origen.serialize();

	ByteStream stream2 = stream;

	NoPointerData destino;
	cout << destino.getEntero() << " - " << destino.getReal() << " - "
	<< destino.getCaracter() << endl;

	destino.hidratate(stream);

	cout << destino.getEntero() << " - " << destino.getReal() << " - "
	<< destino.getCaracter() << endl;

#endif

	return 0;
}
