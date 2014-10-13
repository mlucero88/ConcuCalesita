#ifndef BOLETERIA_H_
#define BOLETERIA_H_
#include "Ninio.h"
#include "Caja.h"

#include "Caja.h"

class SharedMemoryBlock;

class Boleteria {
public:
	Boleteria(double precioBoleto, unsigned cantidadBoletos);
	~Boleteria();

//	void atenderNinio(const Ninio& ninio);

private:
	SharedMemoryBlock* memoriaCompartida;
	Caja caja;
	double precioBoleto;
	unsigned cantidadBoletos;

	void actualizarSaldo();
};

#endif
