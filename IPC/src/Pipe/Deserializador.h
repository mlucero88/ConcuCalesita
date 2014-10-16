/*
 * Deserializador.h
 *
 *  Created on: Oct 12, 2014
 *      Author: pable
 */

#ifndef DESERIALIZADOR_H_
#define DESERIALIZADOR_H_
#include "ITraductor.h"
#include "FifoLectura.h"
#include <stdint.h>


template<class T>
class Deserializador {
public:
	Deserializador(ITraductor<T>& traductor, const std::string& fifo) :
			traductor(traductor), fifoLectura(fifo) {
		fifoLectura.abrir();
	}
	virtual ~Deserializador() {
		fifoLectura.cerrar();
	}

	T deserializar() {
		std::string json = obtenerString();
		return traductor.fromJson(json);
	}
private:
	std::string obtenerString() {
		uint32_t size;
		fifoLectura.leer(reinterpret_cast<void*>(&size), sizeof(uint32_t));
		char json[size];
		fifoLectura.leer(reinterpret_cast<void*>(&json), size);
		return std::string(json);
	}

private:
	ITraductor<T>& traductor;
	FifoLectura fifoLectura;

};

#endif /* DESERIALIZADOR_H_ */
