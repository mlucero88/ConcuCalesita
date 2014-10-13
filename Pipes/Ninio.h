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
	Ninio(){
		estado = COLA_BOLETERIA;
		//no logueo porque sino en la transmision
		//por Pipe aparece nuevamente
//		LOGGER->Log(this->nombre, this->estado);
	}

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

	string getNombre(){
		return nombre;
	}

	void setNombre(string nombre){
		this->nombre = nombre;
	}

	string getStringEstado(){
		return getStringOfEstado(estado);
	}

	void setEstado(string strEstado){
		this->estado = this->getEstadoOfString(strEstado);
	}

private:
	string nombre;
	Estado estado;

	string getStringOfEstado(Estado estado){
		string strEstado;
		switch(estado){
			case (COLA_BOLETERIA): strEstado="Cola de boleteria";
				break;
			case (COLA_CALESITA): strEstado="Cola de calesita";
				break;
			case (EN_CALESITA): strEstado="En la calesita";
				break;
			case (COLA_SALIDA): strEstado="En la cola de salida";
				break;
			case (SALIO): strEstado="Salio";
				break;
		}

		return strEstado;
	}

	Estado getEstadoOfString(string strEstado){
		Estado estado;
			if (strEstado == "Cola de boleteria")
				estado=COLA_BOLETERIA;
			else if (strEstado == "Cola de calesita")
				estado=COLA_CALESITA;
			else if (strEstado == "En la calesita")
				estado=EN_CALESITA;
			else if (strEstado == "En la cola de salida")
				estado=COLA_SALIDA;
			else //(strEstado == "Salio")
				estado=SALIO;

		return estado;
	}

};
#endif
