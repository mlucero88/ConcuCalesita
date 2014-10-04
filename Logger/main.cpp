#include <iostream>
#include "Logger.h"
#include "Ninio.h"

int main(int argc, char** argv) {
/*
    Estado estadoNinio = COLA_BOLETERIA;
    LOGGER->Log("nombreNene", estadoNinio);
*/
	Ninio *nene = new Ninio("Nico");
	nene->siguienteEstado();
	nene->siguienteEstado();
	nene->siguienteEstado();
	nene->siguienteEstado();

	return 0;


}
