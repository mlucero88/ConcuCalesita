#ifndef ESCUCHAEXCEPCION_H_
#define ESCUCHAEXCEPCION_H_

#include "SocketExcepcion.h"

/**
 * @brief Clase que define una excepción generada al intentar escuchar
 * conexiones por un puerto con un socket
 */

class EscuchaExcepcion: public SocketExcepcion {
public:

	/**
	 * @brief Constructor
	 * @param motivo Texto descriptivo del error
	 */
	explicit EscuchaExcepcion(const char *motivo) throw ();

	/**
	 * @brief Destructor
	 */
	virtual ~EscuchaExcepcion() throw ();

	/**
	 * @brief Método que obtiene una descripción del error
	 * @return Una descripción del error
	 */
	virtual const char* what() const throw ();
};

#endif
