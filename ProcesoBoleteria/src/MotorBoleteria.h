#ifndef MOTORBOLETERIA_H_
#define MOTORBOLETERIA_H_

#include <queue>
#include "Ninio.h"
#include "Boleteria.h"
class MotorBoleteria {
public:
	MotorBoleteria(double precioBoleto, unsigned cantidadBoletos);
	~MotorBoleteria();

	void encender();
	void detener();

private:
	Boleteria boleteria;
	std::queue<Ninio> colaBoleteria;
};

#endif
