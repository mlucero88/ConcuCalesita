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
				<< " <ruta_archivo_bd> <ruta_archivo_cola> <caracter_cola>"
				<< std::endl;
		return 1;
	}
	Gestor* gestor;

	// Intento iniciar el gestor
	try {
		gestor = new Gestor(std::string(argv[1]), std::string(argv[2]),
				argv[3][0]);
	}
	catch(const std::string &e) {
		std::cerr << "Error al iniciar el gestor. " << e << std::endl;
		return 2;
	}

	// Establezco la senial para cerrar el gestor
	signal(SIGINT, handlerSIGINT);

	// Atiendo solicitudes hasta recibir la senial SIGINT
	do {
		gestor->atenderSolicitud();
	} while (!cerrarGestor);

	delete gestor;
	return 0;
}
