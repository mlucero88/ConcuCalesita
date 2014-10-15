#include "Boleteria.h"
#include "Logger.h"
#include "TraductorNinio.h"
#include "Pipe/Deserializador.h"
#include "Pipe/Serializador.h"
#include <iostream>
#include <sstream>
#include <cstdlib>

int main(int argc, char* argv[]) {
	if (argc != 3) {
		std::cerr << "Uso: " << argv[0]
				<< " <precio_boleto> <cant_ninios_a_atender>" << std::endl;
		exit(EXIT_FAILURE);
	}
	double precio = 0;
	std::istringstream arg;
	arg.str(std::string(argv[1]));
	arg >> precio;
	try {
		Boleteria boleteria(precio);

		// todo ver como hacer para q termine la boleteria
		int count = 0;
		int maxCount = atoi(argv[2]);
		while (count < maxCount) {
			boleteria.atenderNinio();
			++count;
		}

		/*
		 TraductorNinio traductor;
		 Deserializador< Ninio > deserializador(traductor, "/tmp/COLA_BOLETERIA");
		 //Serializador<Ninio> serializador(traductor, "/tmp/COLA_CALESITA");
		 for (unsigned int i = 0; i < cantidadBoletos; i++) {
		 Ninio ninio = deserializador.deserializar();
		 ninio.siguienteEstado();
		 LOGGER->Log("BOLETERIA: Recibido ninio: " + ninio.getNombre() + " en la Boleteria.");
		 LOGGER->Log("BOLETERIA: Atendiendo ninio: " + ninio.getNombre());
		 boleteria.atenderNinio(ninio);
		 //serializador.serializar(ninio);
		 LOGGER->Log("BOLETERIA: Ninio: " + ninio.getNombre() + " en la cola de la Calesita");
		 }
		 */
	}
	catch(std::string& e) {
		std::cerr << e << std::endl;
		exit(EXIT_FAILURE);
	}
	return 0;
}
