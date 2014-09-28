#ifndef BOLETERIA_H_
#define BOLETERIA_H_

class Boleteria {
public:
	Boleteria(unsigned double precioBoleto, unsigned cantidadBoletos);
	~Boleteria();

	void atenderNinio(const Ninio& ninio);

private:
	Caja caja;
	unsigned double precioBoleto;
	unsigned cantidadBoletos;
};

#endif
