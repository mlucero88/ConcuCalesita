#ifndef ENVIOEXCEPCION_H_
#define ENVIOEXCEPCION_H_

#include "SocketExcepcion.h"

/**
 * @brief Clase que define una excepción generada al intentar enviar datos
 * por el socket
 */

class EnvioExcepcion: public SocketExcepcion {
public:

	/**
	 * @brief Constructor
	 * @param motivo Texto descriptivo del error
	 */
	explicit EnvioExcepcion(const char *motivo) throw ();

	/**
	 * @brief Destructor
	 */
	virtual ~EnvioExcepcion() throw ();

	/**
	 * @brief Método que obtiene una descripción del error
	 * @return Una descripción del error
	 */
	virtual const char* what() const throw ();
};

#endif
