#include "MotorCalesita.h"

MotorCalesita::MotorCalesita(unsigned capacidad, unsigned duracionVuelta) :
		calesita(capacidad, duracionVuelta), colaEntrada(), colaSalida() {
}

MotorCalesita::~MotorCalesita() {
}

void MotorCalesita::encender() {
	// Mover ninios de colaEntrada a calesita hasta llenarse o colaEntrada vacia
	// Arrancar la calesita
	// sleep durante la vuelta
	// detener la calesita
	// Mover ninios de calesita a colaSalida
	// Desacolar ninios de colaSalida
}

void MotorCalesita::detener() {

}
