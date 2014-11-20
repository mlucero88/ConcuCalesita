#ifndef SOCKETSERVIDOR_H
#define	SOCKETSERVIDOR_H

#include "SocketTCP_IP.h"

class SocketCliente;

/**
 * @brief Clase que define el comportamiento de un socket TCP_IP por parte
 * de un servidor
 */

class SocketServidor: public SocketTCP_IP {
public:

	/**
	 * @brief Construye un socket TCP_IP servidor
	 * @param puerto Valor del puerto del socket servidor. Un valor 0 escoge un
	 * puerto que no esté en uso
	 * @param protocolo Protocolo del socket, comúnmente 0
	 */
	explicit SocketServidor(in_port_t puerto = 0, int protocolo = 0);

	/**
	 * @brief Método para enlazar el socket al puerto asignado, por el que se
	 * escucharán conexiones entrantes
	 * @pre Socket creado mediante Socket::crear
	 * @throw EnlaceExcepcion Error generado al enlazar el socket
	 */
	void enlazarServidor() /* throw (EnlaceExcepcion) */;

	/**
	 * @brief Método que pone al servidor a escuchar conexiones entrantes por
	 * el puerto definido, teniendo una cola para recibir conexiones de
	 * capacidad @a colaMaxima
	 * @pre Tener el socket enlazado mediante SocketServidor::enlazarServidor
	 * @param colaMaxima Capacidad de la cola
	 * @throw EscuchaExcepcion Error generado al escuchar conexiones por el
	 * socket
	 */
	void escucharClientes(int colaMaxima) /* throw (EscuchaExcepcion) */;

	/**
	 * @brief Método que toma una conexión de la cola de conexiones entrantes
	 * y devuelve un puntero a un objeto de tipo SocketCliente, el cual servirá
	 * para comunicarse (enviar datos, recibirlos o cerrar la conexión) con el
	 * cliente que fue sacado de la cola de conexiones entrantes. Si no hay
	 * conexiones en la cola, la ejecución se bloquea hasta que llegue una
	 * nueva conexión o se llame a Socket::cortarComunicación
	 * @details El manejo de este objeto SocketCliente se vuelve independiente
	 * del objeto actual SocketServidor, es decir, el método invocante debe
	 * encargarse de cerrar este socket. Además, el objeto se aloca en el heap,
	 * entonces se debe hacer el correspondiente delete para liberar la
	 * memoria
	 * @pre Tener al socket escuchando clientes mediante
	 * SocketServidor::escucharClientes
	 * @return Puntero al socket que se utilizará para comunicarse con el
	 * usuario de la conexión aceptada
	 * @throw AceptacionExcepcion Error generado al aceptar una conexión
	 */
	SocketCliente* aceptarClientes() /* throw (AceptacionExcepcion) */;

	/**
	 * @brief Destructor
	 */
	~SocketServidor();

private:

	/**
	 * @brief Constructor copia
	 * @param servidor Objeto a copiar
	 */
	SocketServidor(const SocketServidor &servidor);
};

#endif
