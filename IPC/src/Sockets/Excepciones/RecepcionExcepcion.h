#ifndef RECEPCIONEXCEPCION_H_
#define RECEPCIONEXCEPCION_H_

#include "SocketExcepcion.h"

/**
 * @brief Clase que define una excepción generada al intentar recibir datos
 * por un socket
 */

class RecepcionExcepcion: public SocketExcepcion {
public:

	/**
	 * @brief Código de error de la recepción
	 */
	typedef enum {
		error_recepcion = -1,		///< Error en la conexión
		usuario_desconectado = 0	///< El otro extremo del socket desconectado
	} t_re_cod_error;

	/**
	 * @brief Constructor
	 * @param motivo Texto descriptivo del error
	 * @param codigo Código de error de la recepción
	 */
	RecepcionExcepcion(const char *motivo, t_re_cod_error codigo) throw ();

	/**
	 * @brief Método para obtener el código de error
	 * @return El código de error
	 */
	virtual t_re_cod_error obtenerCodigoError() const throw ();

	/**
	 * @brief Destructor
	 */
	virtual ~RecepcionExcepcion() throw ();

	/**
	 * @brief Método que obtiene una descripción del error
	 * @return Una descripción del error
	 */
	virtual const char* what() const throw ();

private:

	t_re_cod_error codigo;
};

#endif
