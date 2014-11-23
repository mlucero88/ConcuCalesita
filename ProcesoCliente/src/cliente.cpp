#include "InterfazCliente.h"
#include <cstdlib>
#include <iostream>

int main(int argc, char** argv) {
	if (argc != 4) {
		std::cerr << "Uso: ./cliente <nombre-host>:<puerto>"
				" <ruta_archivo_cola> <caracter>" << std::endl;
		return EXIT_FAILURE;
	}
	InterfazCliente cliente(argv[1]);

	if (!cliente.crearSocket()) {
		exit(EXIT_FAILURE);
	}
	if (!cliente.conectarAlServidor()) {
		exit(EXIT_FAILURE);
	}

	if (cliente.solicitarId()) {
		cliente.cerrarSocket();
		if (cliente.conectarAlGestor(std::string(argv[2]), argv[3][0])) {
			// todo: hacer las cosas del enunciado
		}
		else {
			std::cerr << "Error al intentar conectarse al gestor" << std::endl;
		}
	}
	return EXIT_SUCCESS;
}
