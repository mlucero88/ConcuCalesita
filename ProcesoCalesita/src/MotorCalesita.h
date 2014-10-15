#ifndef MOTORCALESITA_H_
#define MOTORCALESITA_H_

#include "Calesita.h"
#include "TraductorNinio.h"
#include "Pipe/Deserializador.h"

class MotorCalesita {
public:
	MotorCalesita(unsigned capacidad, unsigned duracionVuelta);
	~MotorCalesita();

	void subirNinios();
	void encenderCalesita() const;
	void bajarNinios();

private:
	Calesita calesita;
	TraductorNinio traductor;
	Deserializador< Ninio > deserializadorBoleteria;
};

#endif
