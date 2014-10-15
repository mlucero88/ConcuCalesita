#include "MotorCalesita.h"
#include "Seniales/PipeSignalHandler.h"
#include "Seniales/SignalHandler.h"
#include <iostream>
#include <cstdlib>

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

	try {
		// todo ver como hacer para q termine la calesita (con handler)
		MotorCalesita motorCalesita(capacidad, duracionVuelta);
		while (1) {
			motorCalesita.subirNinios();
			motorCalesita.encenderCalesita();
			motorCalesita.bajarNinios();
		}
	}
	catch(std::exception& e) {
		std::cerr << e.what() << std::endl;
	}
	SignalHandler::getInstance()->removerHandler(SIGPIPE);
	SignalHandler::getInstance()->destruir();

	exit(EXIT_SUCCESS);
}
