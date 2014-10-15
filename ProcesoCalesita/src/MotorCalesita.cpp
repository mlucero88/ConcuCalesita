#include "MotorCalesita.h"
#include "FilePaths.h"
#include <unistd.h>

MotorCalesita::MotorCalesita(unsigned capacidad, unsigned duracionVuelta) :
		calesita(capacidad, duracionVuelta), traductor(),
				deserializadorBoleteria(traductor,
						Paths::getFifoBoleteriaCalesitaFilename()) {
}

MotorCalesita::~MotorCalesita() {
}

void MotorCalesita::subirNinios() {
	while (!calesita.estaLlena()) {
		Ninio ninio = deserializadorBoleteria.deserializar();
		calesita.agregarNinio(ninio);
	}
}

void MotorCalesita::encenderCalesita() const {
	sleep(calesita.getDuracionVuelta());
}

void MotorCalesita::bajarNinios() {
	calesita.vaciar();
}
