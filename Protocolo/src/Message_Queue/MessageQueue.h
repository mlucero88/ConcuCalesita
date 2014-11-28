#ifndef MESSAGEQUEUE_H_
#define MESSAGEQUEUE_H_

#include <sys/types.h>
#include <sys/msg.h>
#include "MessageQueueException.h"

/**
 * @brief Clase que encapsula el manejo de una cola de mensajes (mecanismo IPC)
 * @details Utiliza template con la condicion de que dicho template sea una
 * estructura cuyo primer miembro sea un long con nombre @a mtype, y que este
 * miembro tome solo valores enteros >0
 * struct <name> {
 * 	long mtype;
 * 	...
 * };
 */

template < typename T >
class MessageQueue {

public:
	/**
	 * @brief Constructor que crea una cola de mensajes (en caso de no existir)
	 * o se conecta a la cola (en caso de ya existir), cuyo identificador de
	 * cola se obtiene a partir de el nombre de archivo @a filename y el
	 * caracter @a character
	 * @pre El archivo @a filename debe existir
	 * @param filename Nombre de archivo utilizado para generar el identificador
	 * de la cola
	 * @param character Caracter utilizado para generar el identificador de la
	 * cola
	 * @throw MessageQueueExcepcion Error generado al intentar abrir el archivo
	 * o crear/conectarse a la cola
	 */
	MessageQueue(const std::string& filename,
			char character) /* throw (MessageQueueException) */;

	/**
	 * @brief Destructor
	 * @note Este metodo no destruye la cola de mensajes. Para hacerlo utilizar
	 * el metodo MessageQueue::destroy
	 */
	~MessageQueue();

	/**
	 * @brief Metodo para acolar un mensaje en la cola de mensajes
	 * @pre Tener conexion a la cola de mensajes (es decir, no fue destruida
	 * por el proceso en ejecucion o cualquier otro que haga uso de la misma
	 * cola de mensajes)
	 * @param message Mensaje a acolar en la cola
	 * @throw MessageQueueException Error generado al intentar acolar el
	 * mensaje
	 */
	void sendMsg(const T& message) /* throw (MessageQueueException) */;

	/**
	 * @brief Metodo para desacolar un mensaje de la cola de mensajes
	 * @note En caso de no haber un mensaje que cumpla las condiciones
	 * solicitadas para desacolar, el metodo se bloqueara hasta recibir un
	 * mensaje o que la cola haya sido destruida
	 * @pre Tener conexion a la cola de mensajes (es decir, no fue destruida
	 * por el proceso en ejecucion o cualquier otro que haga uso de la misma
	 * cola de mensajes)
	 * @param type Identificador de mensaje a desacolar. En caso de ser 0, toma
	 * el siguiente mensaje de la cola, sin importar el valor @a mtype del
	 * mensaje. En caso de ser >0, toma el siguiente mensaje de la cola con
	 * @a mytpe igual a @type. En caso de ser <0, toma el siguiente mensaje
	 * de la cola con menor @a mtype, cuyo valor de @a mtype es menor o igual
	 * al valor absoluto de @type
	 * @param buffer Estructura donde se guardara el mensaje
	 * @return Cantidad de bytes copiados en @buffer, sin contar el primer
	 * miembro de la estructura (mtype)
	 * @throw MessageQueueException Error generado al intentar desacolar el
	 * mensaje
	 */
	ssize_t receiveMsg(long type,
			T& buffer) const /* throw (MessageQueueException) */;

	/**
	 * @brief Metodo para eliminar la cola de mensajes
	 * @note Si la cola esta siendo usada por otros procesos y uno o varios se
	 * encuentran bloqueados en espera de MessageQueue::receiveMsg, estos
	 * seran desbloqueados.
	 * @pre Tener conexion a la cola de mensajes (es decir, no fue destruida
	 * por el proceso en ejecucion o cualquier otro que haga uso de la misma
	 * cola de mensajes)
	 * @throw MessageQueueException Error generado al intentar destruir la cola
	 * de mensajes
	 */
	void destroy() const /* throw (MessageQueueException) */;

private:
	int msgId;

	// Prohibo las siguientes operaciones
	MessageQueue(const MessageQueue&);
	MessageQueue& operator=(const MessageQueue&);
};

template < typename T >
MessageQueue< T >::MessageQueue(const std::string& filename, char character) {
	key_t key = ftok(filename.c_str(), character);

	if (key > 0) {
		msgId = msgget(key, 0666 | IPC_CREAT);
		if (msgId < 0) {
			throw MessageQueueException(MessageQueueException::msgget);
		}
	}
	else {
		throw MessageQueueException(MessageQueueException::ftok);
	}
}

template < typename T >
MessageQueue< T >::~MessageQueue() {
}

template < typename T >
void MessageQueue< T >::sendMsg(const T& message) {
	if (msgsnd(msgId, static_cast< const void* >(&message),
			sizeof(T) - sizeof(long), 0) == -1) {
		throw MessageQueueException(MessageQueueException::msgsnd);
	}
}

template < typename T >
ssize_t MessageQueue< T >::receiveMsg(long type, T& buffer) const {
	ssize_t bytesReceived = msgrcv(msgId, static_cast< void * >(&buffer),
			sizeof(T) - sizeof(long), type, 0);
	if (bytesReceived == -1) {
		throw MessageQueueException(MessageQueueException::msgrcv);
	}
	return bytesReceived;
}

template < typename T >
void MessageQueue< T >::destroy() const {
	if (msgctl(msgId, IPC_RMID, NULL) == -1) {
		throw MessageQueueException(MessageQueueException::msgctl);
	}
}

#endif
