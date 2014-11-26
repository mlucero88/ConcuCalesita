#include "Gestor.h"
#include <iostream>
#include <signal.h>

/* Uso variables globales para poder cerrar el gestor con una senial */

static bool cerrarGestor = false;

void handlerSIGINT(int s) {
	cerrarGestor = true;
}

int main(int argc, char* argv[]) {
	if (argc != 4) {
		std::cerr << "Uso: " << argv[0]
				<< " <ruta_archivo_bd> <ruta_archivo_cola> <caracter>"
				<< std::endl;
		return 1;
	}
	Gestor* gestor;
	try {
		gestor = new Gestor(std::string(argv[2]), argv[3][0]);
	}
	catch(const std::string &e) {
		std::cerr << e << std::endl;
		return 2;
	}
	signal(SIGINT, handlerSIGINT);
	gestor->cargarTabla(std::string(argv[1]));
	do {
		gestor->atenderCliente();
	} while (!cerrarGestor);
	gestor->persistirTabla(std::string(argv[1]));
	delete gestor;
	return 0;
}
