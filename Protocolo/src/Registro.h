#ifndef REGISTRO_H_
#define REGISTRO_H_

typedef struct sRegistro {
	long mtype;
	char nombre[61];
	char direccion[120];
	char telefono[13];
} Registro;

#endif
