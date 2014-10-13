/*
 * ProcesoGenerador.cpp
 *
 *  Created on: Oct 13, 2014
 *      Author: pable
 */
#include <src/Pipe/Serializador.h>
#include "TraductorNinio.h"
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <boost/lexical_cast.hpp>

int calcularRandom() {
	srand(time(NULL));
	int resultado = rand() % 10 + 1;
	return resultado;
}

int main(int argc, char *argv[]) {

	if (argc != 2) {

		std::cout << "Usage: " << argv[0] << "CANTIDAD_NINIOS" << std::endl;
		exit(1);

	}

	unsigned int cantidad = atoi(argv[1]);

	if (cantidad != 0) {
		LOGGER->Log("GENERADOR: Generando "+boost::lexical_cast<std::string>(cantidad)+" ninios");
		TraductorNinio traductor;
		Serializador<Ninio> serializador(traductor, "/tmp/COLA_BOLETERIA");

		for (unsigned int i = 0; i < cantidad; i++) {

			Ninio ninio("Ninio" + boost::lexical_cast<std::string>(cantidad));
			LOGGER->Log("GENERADOR: Creado ninio: "+ninio.getNombre());
			ninio.setEstado(COLA_BOLETERIA);
			serializador.serializar(ninio);
			LOGGER->Log("GENERADOR: ninio: "+ninio.getNombre()+" en la cola de la Boleteria.");

			//Sleep para simular en tiempo entre ninio y ninio.
			sleep ( calcularRandom() );
		}
	} else {

		exit(1);

	}
	return 0;
}
