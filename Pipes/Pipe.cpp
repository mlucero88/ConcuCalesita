/*
 * Pipe.cpp
 *
 *  Created on: 5/10/2014
 *      Author: nico
 */

#include "Pipe.h"
#include <string.h>

Pipe :: Pipe() : lectura(true), escritura(true) {
	pipe(this->descriptores);
}

Pipe::~Pipe() {
}

int Pipe :: setearModo(const int modo) {

	if ( modo == LECTURA ) {
		close ( this->descriptores[1] );
		this->escritura = false;

	} else if ( modo == ESCRITURA ) {
		close ( this->descriptores[0] );
		this->lectura = false;
	}

	return 0;
}

ssize_t Pipe :: escribir(const void* dato, int datoSize) {
	if ( this->lectura == true ) {
		close ( this->descriptores[0] );
		this->lectura = false;
	}

	return write(this->descriptores[1], dato,datoSize);
}

ssize_t Pipe :: leer(void* buffer, const int buffSize) {
	if (this->escritura == true) {
		close ( this->descriptores[1]);
		this->escritura = false;
	}

	return read(this->descriptores[0], buffer,buffSize);
}

int Pipe :: getFdLectura() const {
	if ( this->lectura == true )
		return this->descriptores[0];
	else
		return -1;
}

int Pipe :: getFdEscritura() const {
	if ( this->escritura == true )
		return this->descriptores[1];
	else
		return -1;
}

void Pipe :: cerrar() {
	if ( this->lectura == true ) {
		close ( this->descriptores[0] );
		this->lectura = false;
	}

	if ( this->escritura == true ) {
		close ( this->descriptores[1] );
		this->escritura = false;
	}
}

int Pipe :: transmitirNinio(Ninio ninio){
	// escritor
	this->setearModo( Pipe::ESCRITURA );

	char buffer[100];

	strcpy(buffer,ninio.getNombre().c_str());
	strcat(buffer,";");
	strcat(buffer,ninio.getStringEstado().c_str());

	// se redirige la salida estandar
	dup2 ( this->getFdEscritura(),1 );
	// se escribe el dato en el pipe
	std::cout << buffer;

	return 0;
}

Ninio Pipe :: recibirNinio(){
	// lector
	char buffer[100];
	this->setearModo( Pipe::LECTURA );

	// se redirige la entrada estandar
	dup2 ( this->getFdLectura(),0 );
	// se lee el dato del pipe
	std::cin.get ( buffer, 100 );

	std::cout << "La cadena recibida es: " << buffer << endl;

	char *nombre = strtok(buffer, ";");
	char *estado = strtok(NULL, ";");

	std::cout << "El nombre obtenido es: " << nombre << endl;
	std::cout << "El estado obtenido es: " << estado << endl;

	Ninio *nene = new Ninio();
	nene->setNombre(nombre);
	nene->setEstado(estado);

	std::cout << "El nombre del objeto es: " << nene->getNombre() << endl;
	std::cout << "El estado del objeto es: " << nene->getStringEstado() << endl;
	return *nene;
}
