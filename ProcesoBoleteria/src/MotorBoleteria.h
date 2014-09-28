#ifndef MOTORBOLETERIA_H_
#define MOTORBOLETERIA_H_

#include <queue>

class MotorBoleteria {
public:
	MotorBoleteria(unsigned double precioBoleto, unsigned cantidadBoletos);
	~MotorBoleteria();

	void encender();
	void detener();

private:
	Boleteria boleteria;
	std::queue< Ninio > colaBoleteria;
};

#endif
