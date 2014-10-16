#include "Boleteria.h"
#include "Seniales/PipeSignalHandler.h"
#include "Seniales/SignalHandler.h"
#include <iostream>
#include <sstream>
#include <cstdlib>

int main(int argc, char* argv[]) {
	if (argc != 3) {
		std::cerr << "Uso: " << argv[0]
				<< " <precio_boleto> <cant_ninios_a_atender>" << std::endl;
		exit(EXIT_FAILURE);
	}

	PipeSignalHandler handler;
	SignalHandler::getInstance()->registrarHandler(SIGPIPE, &handler);
	int exitState = EXIT_SUCCESS;
	double precio = 0;
	std::istringstream arg;
	arg.str(std::string(argv[1]));
	arg >> precio;
	try {
		Boleteria boleteria(precio);
		int count = 0;
		int maxCount = atoi(argv[2]);
		while (count < maxCount) {
			boleteria.atenderNinio();
			++count;
		}
	}
	catch(const std::string& e) {
		std::cerr << e << std::endl;
		exitState = EXIT_FAILURE;
	}
	catch(const std::exception& e) {
		//Porque puede haber roto el/los pipe/s en la boleteria
		std::cerr << e.what() << std::endl;
	}
	SignalHandler::getInstance()->removerHandler(SIGPIPE);
	SignalHandler::getInstance()->destruir();

	exit(exitState);
}
