#include "Gestor.h"
#include <iostream>
#include <cstring>

// todo al gestor lo lanza el servidor, viceversa o separadamente?

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
	gestor->cargarTabla(std::string(argv[1]));

	// todo operaciones gestor

	delete gestor;
	return 0;
}
