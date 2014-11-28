#ifndef MESSAGEQUEUEEXCEPTION_H_
#define MESSAGEQUEUEEXCEPTION_H_

#include <exception>
#include <string>

/**
 * @brief Clase que define una excepcion en la manipulacion de una cola de
 * mensajes
 */

class MessageQueueException: public std::exception {
public:

	/**
	 * @brief Codigo de la funcion que genero el error
	 */
	enum FunctionCode {
		msgget,				///< Funcion msgget()
		ftok,				///< Funcion ftok()
		msgctl,				///< Funcion msgctl()
		msgsnd,				///< Funcion msgsnd()
		msgrcv				///< Funcion msgrcv()
	};

	/**
	 * @brief Constructor
	 * @param fnCode Codigo de la funcion que genero la excepcion
	 */
	explicit MessageQueueException(enum FunctionCode fnCode) throw();

	/**
	 * @brief Destructor
	 */
	~MessageQueueException() throw();

	/**
	 * @brief Metodo que obtiene el codigo de la funcion que genero la
	 * excepcion
	 * @return Codigo de la funcion que genero la excepcion
	 */
	FunctionCode getCode() const throw();

	/**
	 * @brief Metodo que obtiene una descripcion del error
	 * @return Una descripcion del error
	 */
	const char* what() const throw();

private:

	std::string error_message;
	FunctionCode code;
};

#endif
