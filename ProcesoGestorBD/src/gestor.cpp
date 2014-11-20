#include "Gestor.h"
#include <iostream>
#include <cstring>

int main(int argc, char* argv[]) {
	if (argc != 2) {
		std::cerr << "Uso: " << argv[0] << " <ruta_archivo>" << std::endl;
		return 1;
	}

	/********* TEST ***********/
	Gestor* gestor = new Gestor;
	// todo el registro NO debe persistir con el mtype
	// todo al gestor lo lanza el servidor, viceversa o separadamente?
	Registro reg;
	reg.mtype = 1;
	strcpy(reg.nombre, "Juan Gonzalez");
	strcpy(reg.direccion, "Sarasa 123");
	strcpy(reg.telefono, "47891234");
	gestor->agregarRegistro(reg);

	reg.mtype = 2;
	strcpy(reg.nombre, "Ezequiel Perez");
	strcpy(reg.direccion, "Tucuman 456");
	strcpy(reg.telefono, "47778899");
	gestor->agregarRegistro(reg);

	gestor->persistirTabla(std::string(argv[1]));
	delete gestor;

	// pruebo la carga
	gestor = new Gestor;
	gestor->cargarTabla(std::string(argv[1]));
	const std::vector< Registro >& tabla = gestor->retornarTabla();
	std::vector< Registro >::const_iterator it;
	for (it = tabla.begin(); it != tabla.end(); ++it) {
		std::cout << "Registro.mtype: " << it->mtype << std::endl;
		std::cout << "Registro.nombre: " << it->nombre << std::endl;
		std::cout << "Registro.direccion: " << it->direccion << std::endl;
		std::cout << "Registro.telefono: " << it->telefono << std::endl
				<< std::endl;
	}

	delete gestor;
	/**************************/

	return 0;
}
