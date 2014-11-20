#ifndef CIERREEXCEPCION_H_
#define CIERREEXCEPCION_H_

#include "SocketExcepcion.h"

/**
 * @brief Clase que define una excepción generada al intentar cerrar un socket
 */

class CierreExcepcion: public SocketExcepcion {
public:

	/**
	 * @brief Constructor
	 * @param motivo Texto descriptivo del error
	 */
	explicit CierreExcepcion(const char *motivo) throw ();

	/**
	 * @brief Destructor
	 */
	virtual ~CierreExcepcion() throw ();

	/**
	 * @brief Método que obtiene una descripción del error
	 * @return Una descripción del error
	 */
	virtual const char* what() const throw ();
};

#endif
