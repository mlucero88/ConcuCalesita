#ifndef BOLETERIA_H_
#define BOLETERIA_H_

#include "Ninio.h"
#include "Caja.h"
#include "TraductorNinio.h"
#include "Pipe/Serializador.h"
#include "Pipe/Deserializador.h"

class SharedMemoryBlock;

class Boleteria {
public:
	Boleteria(double precioBoleto);

	void closePipe();

	~Boleteria();

	void atenderNinio();

private:
	SharedMemoryBlock* memoriaCompartida;
	TraductorNinio traductor;
	Deserializador<Ninio> deserializadorGenerador;
	Serializador<Ninio> serializadorCalesita;
	Caja caja;
	double precioBoleto;

	void actualizarSaldo();
};

#endif
