#ifndef CREACIONEXCEPCION_H_
#define CREACIONEXCEPCION_H_

#include "SocketExcepcion.h"

/**
 * @brief Clase que define una excepción generada al intentar crear un socket
 */

class CreacionExcepcion: public SocketExcepcion {
public:

	/**
	 * @brief Constructor
	 * @param motivo Texto descriptivo del error
	 */
	explicit CreacionExcepcion(const char *motivo) throw ();

	/**
	 * @brief Destructor
	 */
	virtual ~CreacionExcepcion() throw ();

	/**
	 * @brief Método que obtiene una descripción del error
	 * @return Una descripción del error
	 */
	virtual const char* what() const throw ();
};

#endif
