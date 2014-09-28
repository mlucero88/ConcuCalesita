#ifndef ADMINISTRADOR_H_
#define ADMINISTRADOR_H_

#include <string>

class Administrador {
public:
	Administrador();
	~Administrador();

	const std::string solicitarComando() const;
	void interpretarComando(const std::string& comando) const;

private:

	unsigned double consultarSaldo() const;
};

#endif
