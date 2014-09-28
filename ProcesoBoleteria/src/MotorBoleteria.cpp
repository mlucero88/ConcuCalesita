#include "MotorBoleteria.h"

MotorBoleteria::MotorBoleteria(unsigned double precioBoleto,
		unsigned cantidadBoletos) :
		boleteria(precioBoleto, cantidadBoletos), colaBoleteria() {
}

MotorBoleteria::~MotorBoleteria() {
}
