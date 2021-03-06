#include "MotorCalesita.h"
#include "FilePaths.h"
#include "Logger.h"
#include <unistd.h>

MotorCalesita::MotorCalesita(unsigned capacidad, unsigned duracionVuelta) :
		calesita(capacidad, duracionVuelta), traductor(), deserializadorBoleteria(traductor, Paths::getFifoBoleteriaCalesitaFilename()) {
}

MotorCalesita::~MotorCalesita() {
}

void MotorCalesita::subirNinios() {
	while (!calesita.estaLlena()) {
		Ninio ninio = deserializadorBoleteria.deserializar();
		ninio.siguienteEstado();
		calesita.agregarNinio(ninio);
	}
}

void MotorCalesita::encenderCalesita() const {
	Logger::getLogger()->Log("CALESITA: comienza la vuelta");
	sleep(calesita.getDuracionVuelta());
	Logger::getLogger()->Log("CALESITA: finaliza la vuelta");
}

void MotorCalesita::bajarNinios() {
	calesita.vaciar();
}
