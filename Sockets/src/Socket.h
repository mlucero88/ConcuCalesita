#ifndef SOCKET_H
#define	SOCKET_H

#include <arpa/inet.h>
#include "ExcepcionesSocket.h"

/**
 * @brief Clase abstracta que encapsula métodos comunes de sockets de cualquier
 * tipo (DARPA, CCITT, etc)
 */

class Socket {

	/**
	 * @brief Clase para manejar la estructura @b socketaddr. Se declaran
	 * métodos para setear valores en una conexión TCP_IP
	 */

	class SocketAddress {
	public:

		/**
		 * @brief Inicializa con ceros todos los campos de la estructura
		 */
		SocketAddress();

		/**
		 * @brief Construye la instancia con los valores de @a direccion
		 * @param direccion Valores de dirección utilizados para crear la
		 * instancia
		 */
		explicit SocketAddress(const struct sockaddr &direccion);

		/**
		 * @brief Constructor copia
		 * @param aCopiar SocketAddress a copiar
		 */
		SocketAddress(const SocketAddress &aCopiar);

		/**
		 * @brief Operador asignación
		 * @param aAsignar SocketAddress a copiar
		 * @return La instancia actual
		 */
		const SocketAddress& operator=(const SocketAddress &aAsignar);

		/**
		 * @brief Método para setear la familia del socket
		 * @param familia Tipo de familia del socket. Para TCP_IP usar AF_INET
		 */
		void setFamilia(sa_family_t familia);

		/**
		 * @brief Método para setear el puerto
		 * @param puerto Número de puerto a setear
		 */
		void setPuerto(in_port_t puerto);

		/**
		 * @brief Método para setear la dirección ip
		 * @param dirIP Dirección ip escrita como cadena de caracteres
		 * numéricos separados por puntos
		 * @return <tt>true</tt> si la dirección se seteó correctamente
		 * @return <tt>false</tt> no se pudo cambiar la dirección
		 */
		bool setDireccionIP(const char *dirIP);

		/**
		 * @brief Método para setear la dirección ip
		 * @note Este método se puede utilizar para asignar direcciones
		 * IP definidas en las macros de in.h
		 * @param dirIP Dirección ip escrita como valor numérico in_addr_t
		 */
		void setDireccionIP(in_addr_t dirIP);

		/**
		 * @brief Método para setear la dirección ip, expresada con su nombre
		 * DNS
		 * @param dirDNS Dirección DNS a setear
		 * @return <tt>true</tt> si la dirección se seteó correctamente
		 * @return <tt>false</tt> no se pudo cambiar la dirección
		 */
		bool setDireccionIPconDNS(const char *dirDNS);

		/**
		 * @brief Método para obtener el puerto almacenado
		 * @return El número de puerto almacenado
		 */
		in_port_t getPuerto() const;

		/**
		 * @brief Método para obtener la dirección ip almacenada
		 * @param aGuardarIP string donde se guardará la dirección ip, en
		 * formato números + puntos
		 */
		void getDireccionIP(std::string &aGuardarIP) const;

		/**
		 * @brief Método para obtener la estructura interna donde se guardan
		 * los datos
		 * @return La estructura sockaddr que almacena los datos
		 */
		const struct sockaddr* getDireccion() const;

		/**
		 * @brief Destructor
		 */
		~SocketAddress();

	private:

		struct sockaddr direccion;
	};

public:

	/**
	 * @brief Tipo de dato de un socket
	 */
	typedef int socket_t;

	/**
	 * @brief Sentido del corte de comunicación
	 */
	enum sentido_corte {
		cortar_envio = 0,    	///< Corta el envío de datos
		cortar_recepcion = 1,	///< Corta la recepción de datos
		cortar_ambos = 2     	///< Corta envío y recepción de datos
	};

	/**
	 * @brief Constructor (no crea el socket, solo instancia el objeto Socket).
	 * @param dominio Dominio del socket (namespace)
	 * @param tipo Tipo del socket (style)
	 * @param protocolo Protocolo del socket (protocol)
	 */
	Socket(int dominio, int tipo, int protocolo);

	/**
	 * @brief Constructor para asignar una estructura de dirección @a sockaddr
	 * al socket
	 * @param dominio Dominio del socket (namespace)
	 * @param tipo Tipo del socket (style)
	 * @param protocolo Protocolo del socket (protocol)
	 * @param dir Estructura sockaddr con la información a asignarle a la
	 * instancia
	 */
	Socket(int dominio, int tipo, int protocolo, const struct sockaddr &dir);

	/**
	 * @brief Constructor copia
	 * @param aCopiar Instancia de Socket a copiar
	 */
	Socket(const Socket& aCopiar);

	/**
	 * @brief Método que crea el socket (abre el file descriptor) a partir de
	 * los valores recibidos por el constructor
	 * @throw CreacionExcepcion Error generado en la creación del socket
	 */
	void crear() /* throw (CreacionExcepcion) */;

	/**
	 * @brief Método para cortar la comunicación del socket en el sentido
	 * definido en @a sentido
	 * @note Este método no libera los recursos. Para hacerlo utilizar el
	 * método Socket::cerrar
	 * @pre Socket creado mediante el método Socket::crear, y tener una
	 * conexión establecida con otra pc
	 * @param sentido Sentido del corte de la comunicación
	 * @throw CierreExcepcion Error generado al intentar cortar la comunicación
	 */
	void cortarComunicacion(
			enum sentido_corte sentido) /* throw (CierreExcepcion) */;

	/**
	 * @brief Método para cerrar el socket y liberar los recursos
	 * @pre Socket creado mediante el método Socket::crear
	 * @throw CierreExcepcion Error generado al intentar cerrar el socket
	 */
	void cerrar() /* throw (CierreExcepcion) */;

	/**
	 * @brief Destructor
	 */
	virtual ~Socket();

protected:

	SocketAddress direccion;
	int dominio, tipo, protocolo;
	socket_t sockfd;
};

#endif
