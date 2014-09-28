#ifndef MOTORCALESITA_H_
#define MOTORCALESITA_H_

#include <queue>

class MotorCalesita {
public:
	MotorCalesita(unsigned capacidad, unsigned duracionVuelta);
	~MotorCalesita();

	void encender();
	void detener();

private:

	Calesita calesita;
	std::queue< Ninio > colaEntrada, colaSalida;
};

#endif
