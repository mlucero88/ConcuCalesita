/*
 * Logger.h
 *
 *  Created on: 03/10/2014
 *      Author: nico
 */

#ifndef NINIO_H
#define NINIO_H

#include "EstadosNinio.h"
#include "Logger.h"

using namespace std;

/**
 *   Clase de Ninio.
 */
class Ninio
{
public:
    /**
     *    Default constructor for class.
     */
	Ninio(string nombre){
		this->nombre = nombre;
		estado = COLA_BOLETERIA;
		LOGGER->Log(this->nombre, this->estado);
	}

	void siguienteEstado(){
		switch(estado){
			case (COLA_BOLETERIA): estado=COLA_CALESITA;
				break;
			case (COLA_CALESITA): estado=EN_CALESITA;
				break;
			case (EN_CALESITA): estado=COLA_SALIDA;
				break;
			case (COLA_SALIDA): estado=SALIO;
				break;
			case (SALIO):
				break;
		}

		LOGGER->Log(this->nombre, this->estado);
	}

private:
	string nombre;
	Estado estado;
};
#endif
