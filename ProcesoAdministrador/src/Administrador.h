#ifndef ADMINISTRADOR_H_
#define ADMINISTRADOR_H_

class SharedMemoryBlock;

class Administrador {
public:

	Administrador();
	~Administrador();

	void iniciar();

private:

	enum Opcion {
		SALDO = 1, SALIR = 2
	};

	SharedMemoryBlock* memoriaCompartida;
	bool finalizar;

	void mostrarOpciones() const;
	int solicitarOpcion() const;
	void ejecutarOpcion(int opcion);
	void consultarSaldo() const;
};

#endif
