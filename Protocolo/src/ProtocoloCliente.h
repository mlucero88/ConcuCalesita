#ifndef PROTOCOLOCLIENTE_H_
#define PROTOCOLOCLIENTE_H_

#include "Mensaje.h"
#include "Comandos.h"
#include <string>

template < class T >
class MessageQueue;

/**
 * @brief Clase utilizada por el cliente para comunicarse con el gestor. Maneja
 * internamente una cola de mensajes
 */
class ProtocoloCliente {
public:

	/**
	 * @brief Constructor que crea una cola de mensajes (en caso de no existir)
	 * o se conecta a la cola (en caso de ya existir), cuyo identificador de
	 * cola se obtiene a partir de el nombre de archivo @a nombreArchivo y el
	 * caracter @a caracter
	 * @pre El archivo @a nombreArchivo debe existir
	 * @param nombreArchivo Nombre de archivo utilizado para generar el
	 * identificador de la cola
	 * @param caracter Caracter utilizado para generar el identificador de la
	 * cola
	 * @param idCliente Identificador del cliente
	 * @throw std::string Error al crear o conectarse a la cola
	 */
	ProtocoloCliente(const std::string& nombreArchivo, char caracter,
			long idCliente) /* throw (std::string) */;

	/**
	 * @brief Destructor
	 * @note Este metodo no destruye la cola de mensajes, ya que el gestor es
	 * el encargado de hacerlo
	 */
	~ProtocoloCliente();

	/**
	 * @brief Metodo que acola una solicitud (mensaje) para agregar un registro
	 * a la base de datos
	 * @param registro Registro a agregar
	 * @return <tt>true</tt> El mensaje se acolo exitosamente
	 * @return <tt>false</tt> El mensaje no se pudo acolar
	 */
	bool enviarAgregarRegistro(const Registro &registro);

	/**
	 * @brief Metodo que acola una solicitud (mensaje) para obtener la tabla
	 * de la base de datos
	 * @return <tt>true</tt> El mensaje se acolo exitosamente
	 * @return <tt>false</tt> El mensaje no se pudo acolar
	 */
	bool enviarSolicitarTabla();

	/**
	 * @brief Metodo para desacolar un mensaje de la cola de mensajes cuyo
	 * id destinatario coincida con @a idCliente asignado en
	 * ProtocoloCliente::ProtocoloCliente
	 * @note En caso de no haber un mensaje que cumpla las condiciones
	 * solicitadas para desacolar, el metodo se bloqueara hasta recibir un
	 * mensaje o que la cola haya sido destruida
	 * @return El mensaje desacolado
	 * @throw std::string Error al intentar desacolar el mensaje
	 */
	Mensaje recibirMensaje() const /* throw (std::string) */;

private:
	MessageQueue< Mensaje >* cola;
	const long idCliente;

	// Prohibo las siguientes operaciones
	ProtocoloCliente(const ProtocoloCliente&);
	ProtocoloCliente& operator=(const ProtocoloCliente&);
};

#endif
