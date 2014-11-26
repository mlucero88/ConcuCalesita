#include "InterfazCliente.h"
#include "Sockets/SocketCliente.h"
#include "Common/ByteStream.h"
#include "ProtocoloCliente.h"
#include <iostream>
#include <vector>
#include <cstdlib>

static const int buffer_size = 50;
static const std::string cmd_id_recibido = "OK";
static const char cmd_fin_comando = '\n';

InterfazCliente::InterfazCliente(const char *direccionServidor) :
		cliente(NULL), protocolo(NULL), idCliente(-1), finalizo(false) {
	std::string direccion(direccionServidor);
	unsigned int delimitador = direccion.find_first_of(':');
	in_port_t puerto = (in_port_t) atoi(
			direccion.substr(delimitador + 1).c_str());
	direccion.erase(delimitador);
	cliente = new SocketCliente(puerto, direccion);
}

bool InterfazCliente::crearSocket() {
	try {
		cliente->crear();
		return true;
	}
	catch(const CreacionExcepcion &ce) {
		std::cerr << ce.what() << std::endl;
	}
	return false;
}

bool InterfazCliente::conectarAlServidor() {
	try {
		cliente->conectar();
		return true;
	}
	catch(const ConexionExcepcion &ce) {
		std::cerr << ce.what() << std::endl;
	}
	return false;
}

bool InterfazCliente::solicitarId() {
	try {
		idCliente = atoi(recibirRespuestaDelServidor().c_str());
	}
	catch(const RecepcionExcepcion &re) {
		std::cerr << re.what() << std::endl;
		return false;
	}
	std::string comando = cmd_id_recibido + cmd_fin_comando;
	try {
		enviarComandoAlServidor(comando);
	}
	catch(const EnvioExcepcion &ee) {
		std::cerr << ee.what() << std::endl;
		return false;
	}
	return true;
}

bool InterfazCliente::cerrarSocket() {
	try {
		cliente->cerrar();
		return true;
	}
	catch(const CierreExcepcion &ce) {
		std::cerr << ce.what() << std::endl;
	}
	return false;
}

bool InterfazCliente::conectarAlGestor(const std::string& nombreArchivo,
		char caracter) {
	if (idCliente > 1 && protocolo == NULL) {
		try {
			protocolo = new ProtocoloCliente(nombreArchivo, caracter,
					idCliente);
			return true;
		}
		catch(const std::string &e) {
			std::cerr << e << std::endl;
		}
	}
	return false;
}

void InterfazCliente::realizarAccion() {
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
		finalizo = true;
		break;
	}
	default: {
		std::cout << "Opción incorrecta. Vuelva a intentarlo" << std::endl
				<< std::endl;
	}
	}
}

bool InterfazCliente::yaFinalizo() const {
	return finalizo;
}

int InterfazCliente::getId() const {
	return idCliente;
}

void InterfazCliente::enviarComandoAlServidor(const std::string &comando) {
	ByteStream buffer(comando.size());
	int bytesEnviados = 0;
	int bytesAenviar = comando.size();

	/* Envio de datos segun protocolo establecido */
	while (bytesEnviados < bytesAenviar) {
		buffer.asignarStream(comando.substr(bytesEnviados).c_str(),
				comando.length() - bytesEnviados);
		bytesEnviados += cliente->enviar(buffer);
	}
}

std::string InterfazCliente::recibirRespuestaDelServidor() {
	std::string respuesta;
	int bytesRecibidos = 0;
	ByteStream buffer(buffer_size);
	bool recepcionCompleta = false;

	/* Recepcion de datos segun protocolo establecido */
	while (!recepcionCompleta) {
		bytesRecibidos = cliente->recibir(buffer);
		respuesta.append(buffer.obtenerStream(), bytesRecibidos);
		if (respuesta[respuesta.length() - 1] == cmd_fin_comando) {
			/* Quito el '\n' */
			respuesta.erase(respuesta.length() - 1);
			recepcionCompleta = true;
		}
	}
	return respuesta;
}

void InterfazCliente::mostrarAcciones() const {
	std::cout << "¿Qué acción desea realizar?" << std::endl;
	std::cout << "1- Agregar registro" << std::endl;
	std::cout << "2- Imprimir tabla" << std::endl;
	std::cout << "3- Salir" << std::endl;
}

void InterfazCliente::agregarRegistro() {
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
	if (protocolo->enviarAgregarRegistro(registro)) {
		switch (protocolo->recibirMensaje().comando) {
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
		}
	}
	else {
		std::cout << "Falló el envío de la solicitud" << std::endl << std::endl;
	}
}

void InterfazCliente::obtenerTabla() {
	if (protocolo->enviarSolicitarTabla()) {
		std::vector< Registro > tabla;
		Mensaje respuesta;
		do {
			respuesta = protocolo->recibirMensaje();
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
			}
		} while (respuesta.comando == Protocolo::reg_send);
	}
	else {
		std::cout << "Falló el envío de la solicitud" << std::endl << std::endl;
	}
}

InterfazCliente::~InterfazCliente() {
	delete cliente;
	if (protocolo != NULL) {
		delete protocolo;
	}
}
