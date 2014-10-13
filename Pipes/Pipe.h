/*
 * Pipe.h
 *
 *  Created on: 5/10/2014
 *      Author: nico
 */

#ifndef PIPE_H_
#define PIPE_H_

#include <unistd.h>
#include "Ninio.h"

class Pipe {

protected:
	//descriptores[0]: fd de lectura
	//descriptores[1]: fd de escritura
	int descriptores[2];
	bool lectura;
	bool escritura;

public:
	static const int LECTURA = 0;
	static const int ESCRITURA = 1;

	Pipe();
	~Pipe();

	int setearModo(const int modo);

	ssize_t escribir(const void* dato, const int datoSize);
	ssize_t leer(void* buffer, const int buffSize);

	int getFdLectura() const;
	int getFdEscritura() const;

	void cerrar ();

	int transmitirNinio(Ninio ninio);
	Ninio recibirNinio();

};

#endif /* PIPE_H_ */
