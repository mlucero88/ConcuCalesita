#ifndef BOLETERIA_H_
#define BOLETERIA_H_

#include "Ninio.h"
#include "Caja.h"

class SharedMemoryBlock;

class Boleteria {
public:
	Boleteria(double precioBoleto);
	~Boleteria();

	void atenderNinio();

private:
	SharedMemoryBlock* memoriaCompartida;
	Caja caja;
	double precioBoleto;

	void actualizarSaldo();
};

#endif
