#ifndef SOCKETEXCEPCION_H_
#define SOCKETEXCEPCION_H_

#include <exception>
#include <string>

/**
 * @brief Clase que define una excepción de un socket. Se utiliza para tener
 * una jerarquía de excepciones para la clase Socket
 */

class SocketExcepcion: public std::exception {
public:

	/**
	 * @brief Constructor
	 * @param motivo Texto descriptivo del error
	 */
	explicit SocketExcepcion(const char *motivo) throw ();

	/**
	 * @brief Destructor
	 */
	virtual ~SocketExcepcion() throw ();

	/**
	 * @brief Método que obtiene una descripción del error
	 * @return Una descripción del error
	 */
	virtual const char* what() const throw ();

protected:

	/**
	 * @brief Texto descriptivo del error
	 */
	std::string motivo;
};

#endif
