#ifndef SOCKETTCPIP_H
#define	SOCKETTCPIP_H

#include "Socket.h"
#include "../Common/ByteStream.h"

/**
 * @brief Clase que define el comportamiento en común de un socket TCP_IP, sea
 * cliente o servidor
 */

class SocketTCP_IP: public Socket {
public:

	/**
	 * @brief Método para obtener el puerto al que se está conectado (en caso
	 * de ser un SocketCliente) o su propio puerto (si es un SocketServidor)
	 * @return El número de puerto de la conexión
	 */
	virtual in_port_t getPuerto() const;

	/**
	 * @brief Método para obtener la IP a la que se está conectado (en caso
	 * de ser un SocketCliente) o su propia IP (si es un SocketServidor)
	 * @return Un string con el número de IP, campos separados con '.'
	 */
	virtual std::string getDireccionIP() const;

	/**
	 * @brief Método para enviar datos a través del socket. Puede no enviar
	 * el buffer completo en un solo llamado
	 * @pre Conexión establecida mediante SocketCliente::conectar (por parte
	 * del cliente) y SocketServidor::aceptar (por parte del servidor)
	 * @param buffer Contenedor con los datos a enviar
	 * @return La cantidad de bytes enviados
	 * @throw EnvioExcepcion Error generado al enviar datos
	 */
	virtual ssize_t enviar(const ByteStream &buffer) const
	/* throw (EnvioExcepcion) */;

	/**
	 * @brief Método para recibir datos a través del socket. Puede no recibir
	 * todos los bytes que se le enviaron en un solo llamado. Si no hay datos
	 * para recibir, se bloquea la ejecución hasta recibir datos o se corte
	 * la comunicación con Socket::cortarComunicacion
	 * @pre Conexión establecida mediante SocketCliente::conectar (por parte
	 * del cliente) y SocketServidor::aceptar (por parte del servidor)
	 * @param buffer Contenedor donde se guardarán los datos recibidos. El
	 * contenido previo es descartado
	 * @return La cantidad de bytes recibidos
	 * @throw RecepcionExcepcion Error generado al recibir datos
	 */
	virtual ssize_t recibir(ByteStream &buffer) const
	/* throw (RecepcionExcepcion) */;

	/**
	 * @brief Destructor
	 */
	virtual ~SocketTCP_IP();

protected:

	/**
	 * @brief Constructor
	 * @param protocolo Protocolo del socket, comúnmente 0
	 */
	explicit SocketTCP_IP(int protocolo = 0);

	/**
	 * @brief Constructor
	 * @param dir Estructura con la configuración de la dirección del socket
	 * @param protocolo Protocolo del socket, comúnmente 0
	 */
	explicit SocketTCP_IP(const struct sockaddr &dir, int protocolo = 0);

	/**
	 * Constructor copia
	 * @param socket SocketTCP_IP a copiar
	 */
	SocketTCP_IP(const SocketTCP_IP &socket);
};

#endif
