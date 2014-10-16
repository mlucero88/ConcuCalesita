#include "Pipe/Serializador.h"
#include "TraductorNinio.h"
#include "Seniales/PipeSignalHandler.h"
#include "Seniales/SignalHandler.h"
#include "Logger.h"
#include "FilePaths.h"
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <sstream>
#include <signal.h>

int calcularRandom() {
	srand(time(NULL));
	int resultado = rand() % 10 + 1;
	return resultado;
}

int main(int argc, char *argv[]) {
	if (argc != 2) {
		std::cout << "Usage: " << argv[0] << "<CANTIDAD_NINIOS>" << std::endl;
		exit(EXIT_FAILURE);
	}
	PipeSignalHandler handler;
	SignalHandler::getInstance()->registrarHandler(SIGPIPE, &handler);
	int exitState = EXIT_SUCCESS;

	unsigned int cantidad = 0;
	std::stringstream ss(argv[1]);
	// Paso ss al int y del int a ss porque no se que sucede si en argv[1]
	// hay algo raro como "25asd"
	ss >> cantidad;
	ss << cantidad;
	std::string str(ss.str());
	LOGGER->Log("PROCESO GENERADOR INICIADO");
	try {
		if (cantidad != 0) {
			LOGGER->Log("GENERADOR: Generando " + str + " ninios");
			TraductorNinio traductor;
			Serializador< Ninio > serializador(traductor, Paths::getFifoGeneradorBoleteriaFilename());

			for (unsigned int i = 0; i < cantidad; i++) {
				ss << i;
				str = ss.str();
				Ninio ninio("Ninio " + str);
				LOGGER->Log("GENERADOR: Creado ninio: " + ninio.getNombre());
				serializador.serializar(ninio);
				ninio.siguienteEstado();

				//Sleep para simular el tiempo entre ninio y ninio.
				sleep(calcularRandom());
			}
		}
		else {
			exitState=EXIT_FAILURE;
		}
	}
	catch(std::exception& ex) {
		std::cerr << ex.what() << std::endl;
	}
	SignalHandler::getInstance()->removerHandler(SIGPIPE);
	SignalHandler::getInstance()->destruir();
	LOGGER->Log("PROCESO GENERADOR FINALIZADO");
	exit(exitState);
}
