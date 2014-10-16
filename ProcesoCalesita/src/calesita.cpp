#include <signal.h>
#include <Seniales/PipeSignalHandler.h>
#include "Logger.h"
#include "MotorCalesita.h"
#include "Seniales/PipeSignalHandler.h"
#include "Seniales/SignalHandler.h"
#include <iostream>
#include <cstdlib>
#include <stdexcept>

int main(int argc, char* argv[]) {
	if (argc != 4) {
		std::cerr << "Uso: " << argv[0] << " <capacidad> <duracion_vuelta> <log_unificado>" << std::endl;
		exit(EXIT_FAILURE);
	}
	Logger::getLogger(true);
	PipeSignalHandler handler;
	SignalHandler::getInstance()->registrarHandler(SIGPIPE, &handler);
	unsigned capacidad = static_cast<unsigned>(atoi(argv[1]));
	unsigned duracionVuelta = static_cast<unsigned>(atoi(argv[2]));
	int unificado = atoi(argv[3]);
	Logger::getLogger(unificado == 0 ? false : true);
	bool eof = false;
	try {
		// todo ver como hacer para q termine la calesita (con handler)
		MotorCalesita motorCalesita(capacidad, duracionVuelta);
		while (!eof) {
			try {
				motorCalesita.subirNinios();
			} catch (std::logic_error& ex) {
				//es el EOF
				eof = true;
			}
			motorCalesita.encenderCalesita();
			motorCalesita.bajarNinios();
		}
	} catch (std::exception& e) {
		std::cerr << e.what() << std::endl;
	}
	SignalHandler::getInstance()->removerHandler(SIGPIPE);
	SignalHandler::getInstance()->destruir();

	exit(EXIT_SUCCESS);
}
