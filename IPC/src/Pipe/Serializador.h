/*
 * Serializador.h
 *
 *  Created on: Oct 11, 2014
 *      Author: pable
 */

#ifndef SERIALIZADOR_H_
#define SERIALIZADOR_H_

#include "FifoEscritura.h"
#include <stdint.h>
#include <cstring>
#include <exception>
#include <iostream>
#include <string>
#include "ITraductor.h"

template<class T>
class Serializador {
public:
	explicit Serializador(ITraductor<T>& traductor, const std::string& fifo) :
			traductor(traductor), fifoEscritura(fifo) {
		fifoEscritura.abrir();
	}

	void cerrar() {
		fifoEscritura.cerrar();
	}

	virtual ~Serializador() {
		fifoEscritura.cerrar();
		fifoEscritura.eliminar();
	}

	void serializar(const T& obj) {
		std::string json = traductor.toJson(obj);
		enviarString(json);
	}

private:
	void enviarString(const std::string& json) {
		uint32_t size = json.length() + sizeof(uint32_t);
		char buffer[size];
		uint32_t length = json.length();
		memcpy(buffer, &length, sizeof(uint32_t));
		memcpy(buffer + sizeof(uint32_t), json.c_str(), json.size());
		fifoEscritura.escribir(buffer, size);
	}

private:
	ITraductor<T>& traductor;
	FifoEscritura fifoEscritura;

};

#endif /* SERIALIZADOR_H_ */
