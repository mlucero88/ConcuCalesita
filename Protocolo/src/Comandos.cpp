#include "Comandos.h"

Comandos::~Comandos() {
}

Comandos& Comandos::getInstancia() {
	static Comandos instancia;
	return instancia;
}
