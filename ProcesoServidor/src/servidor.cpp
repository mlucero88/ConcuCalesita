#include "InterfazServidor.h"
#include <iostream>
#include <cstdlib>
#include <signal.h>

static const int cola_maxima = 5;

/* Uso variables globales para poder cerrar el servidor con una senial. Hay
 * formas mejores (implementar threads, funcion select()), pero al escapar
 * el uso de sockets en el enunciado, se resuelve de esta forma para que sea
 * simple y simplemente mostrar un ejemplo de uso de sockets */

static InterfazServidor* ptrServidor = NULL;
static bool cerrarServidor = false;

void handlerSIGINT(int s) {
	if (ptrServidor) {
		/* Desbloqueo el metodo aceptarClientes() */
		ptrServidor->cerrarSocket();
		cerrarServidor = true;
		std::cout << "Servidor cerrado correctamente\n";
	}
}

int main(int argc, char** argv) {
	if (argc != 2) {
		std::cerr << "Uso: ./server <puerto>\n";
		return EXIT_FAILURE;
	}

	std::cout << "************************************************\n";
	std::cout << "Para cerrar el servidor, enviar la señal SIGINT\n";
	std::cout << "************************************************\n";
	InterfazServidor servidor(argv[1]);

	/* Abro la conexion del servidor */
	if (!servidor.crearSocket()) {
		exit(EXIT_FAILURE);
	}
	if (!servidor.enlazar()) {
		exit(EXIT_FAILURE);
	}
	if (!servidor.escuchar(cola_maxima)) {
		exit(EXIT_FAILURE);
	}

	ptrServidor = &servidor;
	signal(SIGINT, handlerSIGINT);

	/* El servidor comienza a atender clientes, respondiendo a las
	 * solicitudes de los mismos */
	do {
		servidor.atenderCliente();
	} while (!cerrarServidor);

	return EXIT_SUCCESS;
}
