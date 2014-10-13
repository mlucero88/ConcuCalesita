/*
 * main.cpp
 *
 *  Created on: 5/10/2014
 *      Author: nico
 */

#include <string.h>
#include <iostream>
#include <stdlib.h>
#include <sys/wait.h>

#include "Pipe.h"


int main () {

	Pipe *pipe = new Pipe();
	int pid = fork ();

	if ( pid == 0 ) {
		// lector
		Ninio nene = pipe->recibirNinio();
		nene.siguienteEstado();
		pipe->cerrar ();
		exit ( 0 );

	} else {
		// escritor
		Ninio *nene = new Ninio("Nico");
		nene->siguienteEstado();
		nene->siguienteEstado();
		pipe->transmitirNinio(*nene);
		pipe->cerrar ();
		exit ( 0 );
	}
}
