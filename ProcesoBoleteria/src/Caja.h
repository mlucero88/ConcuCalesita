#ifndef CAJA_H_
#define CAJA_H_
#include <iostream>
class Caja {
public:
	Caja(double saldoInicial = 0);
	~Caja();

	void insertarDinero(double dinero);
	void retirarDinero(double dinero);
	double consultarSaldo() const;

private:
	double saldo;
};

#endif
