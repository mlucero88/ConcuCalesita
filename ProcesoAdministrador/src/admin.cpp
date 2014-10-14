#include "Administrador.h"
#include <iostream>
#include <string>
#include <cstdlib>

int main() {
	try {
		Administrador admin;
		admin.iniciar();
	}
	catch(std::string& e) {
		std::cerr << e << std::endl;
		exit(EXIT_FAILURE);
	}
	return 0;
}
