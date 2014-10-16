#include "MotorCalesita.h"
#include "Seniales/PipeSignalHandler.h"
#include "Seniales/SignalHandler.h"
#include <iostream>
#include <signal.h>
#include <cstdlib>
#include <stdexcept>

int main(int argc, char* argv[]) {
	if (argc != 3) {
		std::cerr << "Uso: " << argv[0] << " <capacidad> <duracion_vuelta>"
				<< std::endl;
		exit(EXIT_FAILURE);
	}
	PipeSignalHandler handler;
	SignalHandler::getInstance()->registrarHandler(SIGPIPE, &handler);
	unsigned capacidad = static_cast< unsigned >(atoi(argv[1]));
	unsigned duracionVuelta = static_cast< unsigned >(atoi(argv[2]));
	bool eof = false;
	try {
		MotorCalesita motorCalesita(capacidad, duracionVuelta);
		while (!eof) {
			try {
				motorCalesita.subirNinios();
			}
			catch(std::logic_error& ex) {
				//es el EOF
				eof = true;
			}
			motorCalesita.encenderCalesita();
			motorCalesita.bajarNinios();
		}
	}
	catch(const std::exception& e) {
		std::cerr << e.what() << std::endl;
	}
	SignalHandler::getInstance()->removerHandler(SIGPIPE);
	SignalHandler::getInstance()->destruir();

	exit(EXIT_SUCCESS);
}
