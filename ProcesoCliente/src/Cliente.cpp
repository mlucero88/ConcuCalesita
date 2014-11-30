#include "Cliente.h"
#include <iostream>
#include <vector>
#include <unistd.h>
#include <cstdlib>

Cliente::Cliente(const std::string& nombreArchivoCola, char caracter) :
		protocolo(nombreArchivoCola, caracter, getpid()), finalizo(false) {
}

Cliente::~Cliente() {
}

void Cliente::realizarAccion() {
	int opcion;
	mostrarAcciones();
	std::cout << std::endl;
	std::cout << "Opción: ";
	std::cin >> opcion;
	if (std::cin.fail()) {
		std::cin.clear();
		std::cin.ignore();
	}
	std::cout << std::endl;
	switch (opcion) {
	case 1: {
		agregarRegistro();
		break;
	}
	case 2: {
		obtenerTabla();
		break;
	}
	case 3: {
		obtenerRegistroPorNombre();
		break;
	}
	case 4: {
		finalizo = true;
		break;
	}
	default: {
		std::cout << "Opción incorrecta. Vuelva a intentarlo" << std::endl
				<< std::endl;
	}
	}
}

bool Cliente::eligioSalir() const {
	return finalizo;
}

void Cliente::mostrarAcciones() const {
	std::cout << "¿Qué acción desea realizar?" << std::endl;
	std::cout << "1- Agregar registro" << std::endl;
	std::cout << "2- Imprimir tabla" << std::endl;
	std::cout << "3- Buscar registro por nombre" << std::endl;
	std::cout << "4- Salir" << std::endl;
}

void Cliente::agregarRegistro() {
	Registro registro;
	std::cout << "Completar el registro a agregar" << std::endl;
	std::cin.ignore();
	std::cout << "Nombre: ";
	std::cin.getline(registro.nombre, sizeof(registro.nombre));
	std::cout << "Dirección: ";
	std::cin.getline(registro.direccion, sizeof(registro.direccion));
	std::cout << "Telefono: ";
	std::cin.getline(registro.telefono, sizeof(registro.telefono));
	std::cout << std::endl;
	if (protocolo.enviarAgregarRegistro(registro)) {
		switch (protocolo.recibirMensaje().comando) {
		case Protocolo::op_success: {
			std::cout << "Registro agregado" << std::endl << std::endl;
			return;
		}
		case Protocolo::op_failure: {
			std::cout << "No se agregó el registro - operación fallida"
					<< std::endl << std::endl;
			return;
		}
		case Protocolo::cmd_unknown: {
			std::cout
					<< "No se agregó el registro - el gestor no reconoció la operación"
					<< std::endl << std::endl;
			return;
		}
		default:
			exit(EXIT_FAILURE);
		}
	}
	else {
		std::cout << "Falló el envío de la solicitud" << std::endl << std::endl;
	}
}

void Cliente::obtenerTabla() {
	if (protocolo.enviarSolicitarTabla()) {
		std::vector< Registro > tabla;
		Mensaje respuesta;
		do {
			respuesta = protocolo.recibirMensaje();
			switch (respuesta.comando) {
			case Protocolo::reg_send: {
				tabla.push_back(respuesta.registro);
				break;
			}
			case Protocolo::op_success: {
				if (!tabla.empty()) {
					unsigned short indice = 0;
					std::vector< Registro >::const_iterator it;
					std::cout << "Tabla obtenida:" << std::endl << std::endl;
					for (it = tabla.begin(); it != tabla.end();
							++it, ++indice) {
						std::cout << "Registro " << indice << ":" << std::endl;
						std::cout << "Nombre: " << it->nombre << std::endl;
						std::cout << "Dirección: " << it->direccion
								<< std::endl;
						std::cout << "Telefono: " << it->telefono << std::endl
								<< std::endl;
					}
				}
				else {
					std::cout << "No hay registros en la tabla" << std::endl
							<< std::endl;
				}
				break;
			}
			case Protocolo::op_failure: {
				std::cout << "No se pudo obtener la tabla - operación fallida"
						<< std::endl << std::endl;
				break;
			}
			case Protocolo::cmd_unknown: {
				std::cout << "No se pudo obtener la tabla - el gestor no"
						" reconoció la operación" << std::endl << std::endl;
				break;
			}
			default:
				exit(EXIT_FAILURE);
			}
		} while (respuesta.comando == Protocolo::reg_send);
	}
	else {
		std::cout << "Falló el envío de la solicitud" << std::endl << std::endl;
	}
}

void Cliente::obtenerRegistroPorNombre() {
	Registro registro;
	std::cout << "Ingrese el nombre a buscar" << std::endl;
	std::cin.ignore();
	std::cout << "Nombre: ";
	std::cin.getline(registro.nombre, sizeof(registro.nombre));
	std::cout << std::endl;
	if (protocolo.enviarSolicitarRegistroPorNombre(
			std::string(registro.nombre))) {
		Mensaje respuesta;
		respuesta = protocolo.recibirMensaje();
		switch (respuesta.comando) {
		case Protocolo::reg_send: {
			std::cout << "Registro obtenido:" << std::endl << std::endl;
			std::cout << "Nombre: " << respuesta.registro.nombre << std::endl;
			std::cout << "Dirección: " << respuesta.registro.direccion
					<< std::endl;
			std::cout << "Telefono: " << respuesta.registro.telefono
					<< std::endl << std::endl;
			break;
		}
		case Protocolo::op_failure: {
			std::cout << "No se pudo obtener el registro - el registro no"
					" existe" << std::endl << std::endl;
			break;
		}
		case Protocolo::cmd_unknown: {
			std::cout << "No se pudo obtener el registro - el gestor no"
					" reconoció la operación" << std::endl << std::endl;
			break;
		}
		default:
			exit(EXIT_FAILURE);
		}
	}
	else {
		std::cout << "Falló el envío de la solicitud" << std::endl << std::endl;
	}
}
