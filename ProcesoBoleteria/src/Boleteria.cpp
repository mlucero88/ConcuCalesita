#include "Boleteria.h"

Boleteria::Boleteria(unsigned double precioBoleto, unsigned cantidadBoletos) :
		caja(), precioBoleto(precioBoleto), cantidadBoletos(cantidadBoletos) {
}

Boleteria::~Boleteria() {
}

void Boleteria::atenderNinio(const Ninio& ninio) {
	// fijarse si ninio tiene dinero
	// darle boleto, decrementar cantidad de boletos en uno
	// agregar dinero a la caja
}
