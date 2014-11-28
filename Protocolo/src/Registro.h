#ifndef REGISTRO_H_
#define REGISTRO_H_

/**
 * @brief Estructura usada como registro en la tabla de base de datos
 */

typedef struct sRegistro {
	char nombre[61];
	char direccion[120];
	char telefono[13];
} Registro;

#endif
