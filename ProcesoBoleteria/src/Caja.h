#ifndef CAJA_H_
#define CAJA_H_

class Caja {
public:
	Caja(unsigned double saldoInicial = 0);
	~Caja();

	void insertarDinero(unsigned double dinero);
	void retirarDinero(unsigned double dinero);
	unsigned double consultarSaldo() const;

private:
	unsigned double saldo;
};

#endif
