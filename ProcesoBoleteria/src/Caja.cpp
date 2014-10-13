#include "Caja.h"
#include <string>

Caja::Caja(double saldoInicial) :
		saldo(saldoInicial) {
}

Caja::~Caja() {
}

void Caja::insertarDinero(double dinero) {
	saldo += dinero;
}
void Caja::retirarDinero(double dinero) {
	if (saldo >= dinero) {
		saldo -= dinero;
	}
	else {
		throw std::string("Saldo Insuficiente");
	}
}

double Caja::consultarSaldo() const {
	return saldo;
}

const ByteStream Caja::serializar() const {
	ByteStream stream(sizeof(saldo));
	stream.insertarDatos(&saldo, sizeof(saldo));
	return stream;
}
