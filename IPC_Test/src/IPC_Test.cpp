#include <iostream>
#include <unistd.h>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <sys/wait.h>
#include <cerrno>
#include "Shared_Memory/SharedMemoryBlock.h"
#include "NoPointerData.h"

#define TEST_SHAREDMEMORY

static const char* ruta =
		"/home/martin/Repositorios/ConcuCalesita/IPC_Test/src/IPC_Test.cpp";

using namespace std;

int main() {

#ifdef TEST_SHAREDMEMORY

	string archivo(ruta);
	char caracter = 'M';

//#define ESCRIBE_EN_MEMORIA

#ifdef ESCRIBE_EN_MEMORIA

	cout << "Escribo en memoria" << endl;
	NoPointerData origen(123456789, 3.1415, '@');
	ByteStream stream = origen.serialize();
	try {
		SharedMemoryBlock bloque(archivo, caracter, stream.getTamanioOcupado());
		size_t bytes = bloque.write(stream);
		cout << "Escribi Data (" << bytes << " bytes): " << origen.getEntero()
				<< " - " << origen.getReal() << " - " << origen.getCaracter()
				<< endl;
		cout << "Presione una enter para finalizar";
		getchar();
		bloque.freeResources();
	}
	catch(const SharedMemoryException& e) {
		cerr << e.what() << endl;
	}

#endif

#ifndef ESCRIBE_EN_MEMORIA

	cout << "Leo de memoria" << endl;
	try {
		SharedMemoryBlock bloque(archivo, caracter);
		NoPointerData destino;
		ByteStream stream;
		size_t bytes = bloque.read(stream);
		destino.hidratate(stream);
		cout << "Lei Data (" << bytes << " bytes): " << destino.getEntero()
		<< " - " << destino.getReal() << " - " << destino.getCaracter()
		<< endl;
		cout << "Presione una enter para finalizar";
		getchar();
		bloque.freeResources();
	}
	catch(const SharedMemoryException& e) {
		cerr << e.what() << endl;
	}

#endif

#endif

	return 0;
}

/* todo
 * funciona bajo ciertas condiciones
 * 1- Si hago un read de la shared memory sin haber hecho un write antes (desde
 * mismo u otro proceso) se genera el segmentation fault
 * 2- Todos los procesos que compartan un mismo bloque de memoria, ademas de
 * tener que poner el mismo filename, tienen que poner el mismo blockSize. Esto
 * lo podria arreglar si al hacer shmget seteo bien flags y verifico (ver man).
 * Igual esto ya escapa al alcance, es muy detallista.
 */
