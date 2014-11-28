#ifndef CLIENTE_H_
#define CLIENTE_H_

#include "ProtocoloCliente.h"

/**
 * @brief Clase que maneja a un cliente de la base de datos
 */
class Cliente {
public:

	/**
	 * @brief Constructor que instancia un cliente y lo intenta conectar al
	 * gestor de la base de datos. Para conectarse al gestor,
	 * @a nombreArchivoCola y @a caracter deben coincidir con los valores
	 * usados para iniciar el gestor
	 * @pre El archivo @a nombreArchivoCola debe existir
	 * @param nombreArchivoCola Nombre de archivo utilizado para iniciar el
	 * gestor
	 * @param caracter Caracter utilizado para iniciar el gestor
	 * @throw std::string Error al conectarse al gestor
	 */
	Cliente(const std::string& nombreArchivoCola,
			char caracter) /* throw (std::string) */;

	/**
	 * @brief Destructor
	 */
	~Cliente();

	/**
	 * @brief Metodo que solicita una accion al usuario por entrada estandar
	 * y realiza dicha accion
	 */
	void realizarAccion();

	/**
	 * @brief Metodo que retorna si el usuario eligio la opcion 'salir'
	 * @return <tt>true</tt> El cliente solicito finalizar la ejecucion
	 * @return <tt>false</tt> El cliente no solicito finalizar la ejecucion
	 */
	bool eligioSalir() const;

private:

	void mostrarAcciones() const;
	void agregarRegistro();
	void obtenerTabla();

	ProtocoloCliente protocolo;
	bool finalizo;
};

#endif
