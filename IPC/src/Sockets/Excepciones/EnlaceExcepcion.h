#ifndef ENLACEEXCEPCION_H_
#define ENLACEEXCEPCION_H_

#include "SocketExcepcion.h"

/**
 * @brief Clase que define una excepción generada al intentar enlazar un socket
 * al puerto
 */

class EnlaceExcepcion: public SocketExcepcion {
public:

	/**
	 * @brief Constructor
	 * @param motivo Texto descriptivo del error
	 */
	explicit EnlaceExcepcion(const char *motivo) throw ();

	/**
	 * @brief Destructor
	 */
	virtual ~EnlaceExcepcion() throw ();

	/**
	 * @brief Método que obtiene una descripción del error
	 * @return Una descripción del error
	 */
	virtual const char* what() const throw ();
};

#endif
