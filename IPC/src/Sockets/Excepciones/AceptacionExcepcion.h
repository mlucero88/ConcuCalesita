#ifndef ACEPTACIONEXCEPCION_H_
#define ACEPTACIONEXCEPCION_H_

#include "SocketExcepcion.h"

/**
 * @brief Clase que define una excepción generada al intentar aceptar una
 * conexión almacenada en la cola de conexiones entrantes
 */

class AceptacionExcepcion: public SocketExcepcion {
public:

	/**
	 * @brief Constructor
	 * @param motivo Texto descriptivo del error
	 */
	explicit AceptacionExcepcion(const char *motivo) throw ();

	/**
	 * @brief Destructor
	 */
	virtual ~AceptacionExcepcion() throw ();

	/**
	 * @brief Método que obtiene una descripción del error
	 * @return Una descripción del error
	 */
	virtual const char* what() const throw ();
};

#endif
