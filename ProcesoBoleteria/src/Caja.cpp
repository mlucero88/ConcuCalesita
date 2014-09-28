#include "Caja.h"
#include <string>

Caja::Caja(unsigned double saldoInicial) :
		saldo(saldoInicial) {
}

Caja::~Caja() {
}

void Caja::insertarDinero(unsigned double dinero) {
	saldo += dinero;
}
void Caja::retirarDinero(unsigned double dinero) {
	if (saldo >= dinero) {
		saldo -= dinero;
	}
	else {
		throw std::string("Saldo Insuficiente");
	}
}

unsigned double Caja::consultarSaldo() const {
	return saldo;
}
