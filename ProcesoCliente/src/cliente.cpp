#include "InterfazCliente.h"
#include <cstdlib>
#include <iostream>

int main(int argc, char** argv) {
	if (argc != 2) {
		std::cerr << "Uso: ./cliente <nombre-host>:<puerto>\n";
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
		// todo: hacer las cosas del enunciado
		std::cout << cliente.getId() << std::endl;
	}
	return EXIT_SUCCESS;
}
