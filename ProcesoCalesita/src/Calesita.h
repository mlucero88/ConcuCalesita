#ifndef CALESITA_H_
#define CALESITA_H_

class Calesita {
public:
	Calesita(unsigned capacidad, unsigned duracionVuelta);
	~Calesita();

	bool estaLlena() const;
	bool estaVacia() const;
	unsigned getDuracionVuelta() const;
	void agregarNinio();
	void quitarNinio();

private:
	// hay que ver si se implementa con "cantidadOcupada" (es decir, sin estar
	// los ninios en el objeto), o haciendo una std::list de ninios
	unsigned capacidad, cantidadOcupada, duracionVuelta;
};

#endif
