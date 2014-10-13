#ifndef CAJA_H_
#define CAJA_H_
<<<<<<< HEAD

#include "Common/ByteStream.h"

=======
#include <iostream>
>>>>>>> refs/remotes/origin/master
class Caja {
public:
	Caja(double saldoInicial = 0);
	~Caja();

	void insertarDinero(double dinero);
	void retirarDinero(double dinero);
	double consultarSaldo() const;
<<<<<<< HEAD

	const ByteStream serializar() const;
=======
>>>>>>> refs/remotes/origin/master

private:
	double saldo;
};

#endif
