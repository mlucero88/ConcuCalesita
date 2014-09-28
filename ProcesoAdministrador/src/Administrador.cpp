#include "Administrador.h"

Administrador::Administrador() {
}

Administrador::~Administrador() {
}

const std::string Administrador::solicitarComando() const {
	std::string comando;
	std::cout << "Por favor ingrese su comando: ";
	std::cin >> comando;
	return comando;
}

void Administrador::interpretarComando(const std::string& comando) const {
	// por ahora lo unico es consultar saldo (asignarle un comando)
	// podemos usar la "q" para salir
}

unsigned double Administrador::consultarSaldo() const {
	// acceder a caja por memoria compartida o algo
	return 0;
}
