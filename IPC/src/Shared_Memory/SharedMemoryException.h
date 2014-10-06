#ifndef SHAREDMEMORYEXCEPTION_H_
#define SHAREDMEMORYEXCEPTION_H_

#include <exception>
#include <string>

/**
 * @brief Clase que define una excepcion en la manipulacion de memoria
 * compartida
 */

class SharedMemoryException: public std::exception {
public:

	enum FunctionCode {
		shmget, shmat, shmdt, shmctl, ftok
	};

	/**
	 * @brief Constructor
	 * @param fnCode Codigo de la funcion que genero la excepcion
	 */
	explicit SharedMemoryException(enum FunctionCode fnCode) throw();

	/**
	 * @brief Destructor
	 */
	virtual ~SharedMemoryException() throw();

	/**
	 * @brief Metodo que obtiene una descripcion del error
	 * @return Una descripcion del error
	 */
	virtual const char* what() const throw();

protected:

	std::string error_message;
};

#endif
