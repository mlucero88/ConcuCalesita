#include "Cliente.h"
#include <iostream>

int main(int argc, char** argv) {
	if (argc != 3) {
		std::cerr << "Uso: " << argv[0]
				<< " <ruta_archivo_cola> <caracter_cola>" << std::endl;
		return 1;
	}

	Cliente* cliente;

	// Intento iniciar un cliente y conectarlo con el gestor
	try {
		cliente = new Cliente(std::string(argv[1]), argv[2][0]);
	}
	catch(const std::string &e) {
		std::cerr << "Error al intentar conectarse al gestor. " << e
				<< std::endl;
		return 2;
	}

	// El cliente comineza a hacer solicitudes
	do {
		cliente->realizarAccion();
	} while (!cliente->eligioSalir());

	delete cliente;
	return 0;
}
