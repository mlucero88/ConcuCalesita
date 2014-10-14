#ifndef CONFIGURACION_H_
#define CONFIGURACION_H_

#include "FilePaths.h"

class Configuracion {

public:
	Configuracion();
	~Configuracion();
	const char* getPrecioBoleto() const;
	const char* getCapacidadCalesita() const;
	const char* getDuracionVueltaCalesita() const;
	const char* getCantidadNiniosGenerador() const;

private:
	std::string precioBoleto, capacidadCalesita, duracionVuelta,
			cantNiniosGenerador;
};

#endif
