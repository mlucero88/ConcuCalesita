#ifndef PROTOCOLOGESTOR_H_
#define PROTOCOLOGESTOR_H_

#include "Mensaje.h"
#include <string>

template < class T >
class MessageQueue;

/**
 * @brief Clase utilizada por el gestor para comunicarse con el cliente. Maneja
 * internamente una cola de mensajes
 */
class ProtocoloGestor {
public:

	/**
	 * @brief Constructor que crea una cola de mensajes cuyo identificador de
	 * cola se obtiene a partir de el nombre de archivo @a nombreArchivo y el
	 * caracter @a caracter
	 * @pre El archivo @a nombreArchivo debe existir
	 * @pre La cola de mensajes no debe existir
	 * @param nombreArchivo Nombre de archivo utilizado para generar el
	 * identificador de la cola
	 * @param caracter Caracter utilizado para generar el identificador de la
	 * cola
	 * @throw std::string Error al crear la cola
	 */
	ProtocoloGestor(const std::string& nombreArchivo,
			char caracter) /* throw (std::string) */;

	/**
	 * @brief Destructor
	 * @note Este metodo destruye la cola de mensajes
	 */
	~ProtocoloGestor();

	/**
	 * @brief Metodo que acola un aviso de operacion exitosa (mensaje)
	 * @param idCliente Identificador del cliente destinatario
	 * @return <tt>true</tt> El mensaje se acolo exitosamente
	 * @return <tt>false</tt> El mensaje no se pudo acolar
	 */
	bool enviarOperacionExitosa(long idCliente);

	/**
	 * @brief Metodo que acola un aviso de operacion fallida (mensaje)
	 * @param idCliente Identificador del cliente destinatario
	 * @return <tt>true</tt> El mensaje se acolo exitosamente
	 * @return <tt>false</tt> El mensaje no se pudo acolar
	 */
	bool enviarOperacionFallida(long idCliente);

	/**
	 * @brief Metodo que acola un aviso de comando desconocido (mensaje)
	 * @param idCliente Identificador del cliente destinatario
	 * @return <tt>true</tt> El mensaje se acolo exitosamente
	 * @return <tt>false</tt> El mensaje no se pudo acolar
	 */
	bool enviarComandoDesconocido(long idCliente);

	/**
	 * @brief Metodo que acola un mensaje que contiene un registro
	 * @param idCliente Identificador del cliente destinatario
	 * @param registro Registro a enviar
	 * @return <tt>true</tt> El mensaje se acolo exitosamente
	 * @return <tt>false</tt> El mensaje no se pudo acolar
	 */
	bool enviarRegistro(long idCliente, const Registro& registro);

	/**
	 * @brief Metodo para desacolar un mensaje de la cola de mensajes cuyo
	 * id destinatario coincida con @a Protocolo::idGestor definido en
	 * Comandos.h
	 * @note En caso de no haber un mensaje que cumpla las condiciones
	 * solicitadas para desacolar, el metodo se bloqueara hasta recibir un
	 * mensaje o que la cola haya sido destruida
	 * @return El mensaje desacolado
	 * @throw std::string Error al intentar desacolar el mensaje
	 */
	Mensaje recibirMensaje() const /* throw (std::string) */;

private:
	MessageQueue< Mensaje >* cola;

	bool enviarResultado(long idCliente, enum Protocolo::comando cmd);

	// Prohibo las siguientes operaciones
	ProtocoloGestor(const ProtocoloGestor&);
	ProtocoloGestor& operator=(const ProtocoloGestor&);
};

#endif
