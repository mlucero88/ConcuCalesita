#ifndef REGISTRO_H_
#define REGISTRO_H_

/**
 * @brief Estructura usada como registro en la tabla de base de datos
 */
struct sRegistro {
	char nombre[61];		///< Nombre
	char direccion[120];	///< Direccion
	char telefono[13];		///< Telefono
};

typedef sRegistro Registro;

#endif
