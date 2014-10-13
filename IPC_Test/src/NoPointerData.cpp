#include "NoPointerData.h"
#include <cstring>

NoPointerData::NoPointerData() {
	entero = 100;
	real = 3.14;
	caracter = 'M';
}

NoPointerData::NoPointerData(int entero, double real, char caracter) {
	this->entero = entero;
	this->real = real;
	this->caracter = caracter;
}

NoPointerData::~NoPointerData() {
}

int NoPointerData::getEntero() const {
	return entero;
}

double NoPointerData::getReal() const {
	return real;
}

char NoPointerData::getCaracter() const {
	return caracter;
}

const ByteStream NoPointerData::serialize() const {
	size_t capacidad = sizeof(entero) + sizeof(real) + sizeof(caracter);
	ByteStream stream(capacidad);
	stream.insertarDatos(&entero, sizeof(entero));
	stream.insertarDatos(&real, sizeof(real));
	stream.insertarDatos(&caracter, sizeof(caracter));
	return stream;
}

bool NoPointerData::hidratate(const ByteStream& stream) {
	if (stream.getTamanioOcupado()
			>= sizeof(entero) + sizeof(real) + sizeof(caracter)) {
		const byte_t* data = stream.obtenerStream();
		memcpy(&entero, data, sizeof(entero));
		data += sizeof(entero);
		memcpy(&real, data, sizeof(real));
		data += sizeof(real);
		memcpy(&caracter, data, sizeof(caracter));
		return true;
	}
	else {
		return false;
	}
}
