<<<<<<< HEAD
#include "Boleteria.h"
#include <iostream>
#include <sstream>
=======
#include <Ninio.h>
#include <src/Pipe/Deserializador.h>
#include <src/Pipe/Serializador.h>
#include <stdlib.h>
>>>>>>> refs/remotes/origin/master

<<<<<<< HEAD
int main(int argc, char* argv[]) {
	if (argc != 3) {
		std::cerr << "Uso: " << argv[0] << " <precio_boleto> <cantidad_boletos>"
				<< std::endl;
		return 0;
	}
	std::istringstream arg;
	double precio = 0;
	unsigned cantidadBoletos = 0;
	arg.str(std::string(argv[1]));
	arg >> precio;
	arg.str(std::string(argv[2]));
	arg >> cantidadBoletos;
	Boleteria boleteria(precio, cantidadBoletos);

	// sacar esto
	std::cin >> precio;
=======
#include "Boleteria.h"
#include "TraductorNinio.h"

int main(int argc, char *argv[]) {

	if (argc != 3) {

		std::cout << "Usage: " << argv[0] << "PRECIO_BOLETO CANTIDAD_BOLETOS" << std::endl;
		exit(1);

	}

	double precio = atof(argv[1]);
	unsigned int cantidad = atoi(argv[2]);
	if (cantidad != 0) {
		Boleteria boleteria(precio, cantidad);
		TraductorNinio traductor;
		Deserializador<Ninio> deserializador(traductor, "/tmp/COLA_BOLETERIA");
		//Serializador<Ninio> serializador(traductor, "/tmp/COLA_CALECITA");
		for (unsigned int i = 0; i < cantidad; i++) {
			Ninio ninio = deserializador.deserializar();
			ninio.siguienteEstado();
			LOGGER->Log("BOLETERIA: Recibido ninio: "+ninio.getNombre()+" en la Boleteria.");
			LOGGER->Log("BOLETERIA: Atendiendo ninio: "+ninio.getNombre());
			boleteria.atenderNinio(ninio);
			//serializador.serializar(ninio);
			LOGGER->Log("BOLETERIA: Ninio: "+ninio.getNombre()+" en la cola de la Calecita");
		}
	} else {
		exit(1);
	}
>>>>>>> refs/remotes/origin/master

	return 0;
}
