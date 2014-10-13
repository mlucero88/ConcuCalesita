#ifndef BOLETERIA_H_
#define BOLETERIA_H_
#include "Ninio.h"
#include "Caja.h"

class Boleteria {
public:
	Boleteria(double precioBoleto, unsigned cantidadBoletos);
	~Boleteria();

	void atenderNinio(const Ninio& ninio);

private:
	Caja caja;
	double precioBoleto;
	unsigned cantidadBoletos;
};

#endif
