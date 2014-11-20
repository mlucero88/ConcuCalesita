#ifndef CONEXIONEXCEPCION_H_
#define CONEXIONEXCEPCION_H_

#include "SocketExcepcion.h"

/**
 * @brief Clase que define una excepción generada al intentar conectarse al
 * socket de un servidor
 */

class ConexionExcepcion: public SocketExcepcion {
public:

	/**
	 * @brief Constructor
	 * @param motivo Texto descriptivo del error
	 */
	explicit ConexionExcepcion(const char *motivo) throw ();

	/**
	 * @brief Destructor
	 */
	virtual ~ConexionExcepcion() throw ();

	/**
	 * @brief Método que obtiene una descripción del error
	 * @return Una descripción del error
	 */
	virtual const char* what() const throw ();
};

#endif
