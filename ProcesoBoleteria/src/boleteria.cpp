#include "Boleteria.h"
#include "Logger.h"
#include "TraductorNinio.h"
#include "Pipe/Deserializador.h"
#include "Pipe/Serializador.h"
#include <iostream>
#include <sstream>

int main(int argc, char* argv[]) {
	if (argc != 2) {
		std::cerr << "Uso: " << argv[0] << " <precio_boleto>" << std::endl;
		return 1;
	}
	double precio = 0;
	std::istringstream arg;
	arg.str(std::string(argv[1]));
	arg >> precio;
	try {
		Boleteria boleteria(precio);

		// todo ver como hacer para q termine la boleteria
		int count = 0;
		while (count < 100) {
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
	}
	return 0;
}
