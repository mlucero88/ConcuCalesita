#include "Boleteria.h"
#include "Seniales/PipeSignalHandler.h"
#include "Seniales/SignalHandler.h"
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <stdexcept>
#include <Logger.h>

int main(int argc, char* argv[]) {
	if (argc != 4) {
		std::cerr << "Uso: " << argv[0] << " <precio_boleto> <cant_ninios_a_atender> <LOG_UNIFICADO (0/1)>" << std::endl;
		exit(EXIT_FAILURE);
	}

	int unificado = atoi(argv[3]);
	Logger::getLogger(unificado == 0 ? false : true);
	PipeSignalHandler handler;
	SignalHandler::getInstance()->registrarHandler(SIGPIPE, &handler);
	int exitState = EXIT_SUCCESS;
	double precio = 0;
	std::istringstream arg;
	arg.str(std::string(argv[1]));
	arg >> precio;
	try {
		Boleteria boleteria(precio);
		// todo ver como hacer para q termine la boleteria
		int count = 0;
		int maxCount = atoi(argv[2]);
		bool eof = false;
		while (!eof) {
			try {
				boleteria.atenderNinio();
			} catch (std::logic_error& error) {
				eof = true;
			}
		}
		boleteria.closePipe();
	} catch (const std::string& e) {
		std::cerr << e << std::endl;
		exitState = EXIT_FAILURE;
	} catch (const std::exception& e) {
		//Porque puede haber roto el/los pipe/s en la boleteria
		std::cerr << e.what() << std::endl;
	}
	SignalHandler::getInstance()->removerHandler(SIGPIPE);
	SignalHandler::getInstance()->destruir();

	exit(exitState);
}
