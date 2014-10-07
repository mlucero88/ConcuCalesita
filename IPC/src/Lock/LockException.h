#ifndef LOCKEXCEPTION_H_
#define LOCKEXCEPTION_H_

#include <exception>
#include <string>

/**
 * @brief Clase que define una excepcion en la manipulacion de locks
 */

class LockException: public std::exception {
public:

	enum FunctionCode {
		invalidFile, fcntl
	};

	/**
	 * @brief Constructor
	 * @param fnCode Codigo de la funcion que genero la excepcion
	 */
	explicit LockException(enum FunctionCode fnCode) throw();

	/**
	 * @brief Destructor
	 */
	virtual ~LockException() throw();

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
	virtual const char* what() const throw();

protected:

	std::string error_message;
	FunctionCode code;
};

#endif
