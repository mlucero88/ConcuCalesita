#ifndef SOCKETCLIENTE_H
#define	SOCKETCLIENTE_H

#include "SocketTCP_IP.h"

/**
 * @brief Clase que define el comportamiento de un socket TCP_IP por parte
 * de un cliente
 */

class SocketCliente: public SocketTCP_IP {
public:

	/**
	 * @brief Constructor que instancia los valores para una conexión TCP_IP
	 * @param puertoDestino Número del puerto a conectarse
	 * @param dirIPdestino Dirección ip a conectarse, en formato in_addr_t
	 * @param protocolo Protocolo a utilizar (comúnmente 0)
	 */
	SocketCliente(in_port_t puertoDestino, in_addr_t dirIPdestino,
			int protocolo = 0);

	/**
	 * @brief Constructor que instancia los valores para una conexión TCP_IP
	 * @param puertoDestino Número del puerto a conectarse
	 * @param dirIPdestino Dirección ip a conectarse, en formato de cadena,
	 * campos separados por '.'
	 * @param protocolo Protocolo a utilizar (comúnmente 0)
	 */
	SocketCliente(in_port_t puertoDestino, const char *dirIPdestino,
			int protocolo = 0);

	/**
	 * @brief Constructor que instancia los valores para una conexión TCP_IP
	 * @param puertoDestino Número del puerto a conectarse
	 * @param dirDNSdestino Dirección DNS a conectarse
	 * @param protocolo Protocolo a utilizar (comúnmente 0)
	 */
	SocketCliente(in_port_t puertoDestino, const std::string &dirDNSdestino,
			int protocolo = 0);

	/**
	 * @brief Constructor crea una instancia a partir de un socket abierto
	 * @details El uso principal de este constructor es para crear un cliente
	 * a partir de un aceptación por parte del servidor en el método
	 * SocketServidor::aceptarClientes
	 * @param socket File descriptor del socket a utilizar (ya creado)
	 * @param dir Estructura que almacena los datos de dirección del socket
	 * @param protocolo Protocolo a utilizar (comúnmente 0)
	 */
	SocketCliente(socket_t socket, const struct sockaddr &dir,
			int protocolo = 0);

	/**
	 * @brief Método que envía un pedido de conexión a un servidor con el valor
	 * de puerto y direccion IP asignados en la construccion del objeto
	 * @pre Socket creado mediante Socket::crear
	 * @pre El servidor destino debe estar enlazado al puerto seteado mediante
	 * el método SocketServidor::enlazarServidor
	 * @throw ConexionExcepcion Error generado al intentar conectarse
	 */
	void conectar() /* throw (ConexionExcepcion) */;

	/**
	 * @brief Destructor
	 */
	~SocketCliente();

private:

	/**
	 * @brief Constructor copia
	 * @param cliente SocketCliente a copiar
	 */
	SocketCliente(const SocketCliente &cliente);
};

#endif
