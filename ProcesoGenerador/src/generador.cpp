#include "Pipe/Serializador.h"
#include "TraductorNinio.h"
#include "Logger.h"
#include <ctime>
#include <cstdlib>
#include <iostream>
#include <sstream>

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

	unsigned int cantidad = 0;
	std::stringstream ss(argv[1]);
	// Paso ss al int y del int a ss porque no se que sucede si en argv[1]
	// hay algo raro como "25asd"
	ss >> cantidad;
	ss << cantidad;
	std::string str(ss.str());

	if (cantidad != 0) {
		LOGGER->Log("GENERADOR: Generando " + str + " ninios");
		TraductorNinio traductor;
		Serializador< Ninio > serializador(traductor, "/tmp/COLA_BOLETERIA");

		for (unsigned int i = 0; i < cantidad; i++) {
			ss << i;
			str = ss.str();
			Ninio ninio("Ninio " + str);
			LOGGER->Log("GENERADOR: Creado ninio: " + ninio.getNombre());
			ninio.setEstado(COLA_BOLETERIA);
			serializador.serializar(ninio);
			LOGGER->Log(
					"GENERADOR: ninio: " + ninio.getNombre()
					+ " en la cola de la Boleteria.");

			//Sleep para simular el tiempo entre ninio y ninio.
			sleep(calcularRandom());
		}
	}
	else {
		exit(EXIT_FAILURE);
	}
	return 0;
}
