#include "Boleteria.h"
#include <iostream>
#include <sstream>

int main(int argc, char* argv[]) {
	if (argc != 3) {
		std::cerr << "Uso: " << argv[0] << " <precio_boleto> <cantidad_boletos>"
				<< std::endl;
		return 0;
	}
	std::istringstream arg;
	double precio = 0;
	unsigned cantidadBoletos = 0;
	arg.str(std::string(argv[1]));
	arg >> precio;
	arg.str(std::string(argv[2]));
	arg >> cantidadBoletos;
	Boleteria boleteria(precio, cantidadBoletos);

	// sacar esto
	std::cin >> precio;

	return 0;
}
