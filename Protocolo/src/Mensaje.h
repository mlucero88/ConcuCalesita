#ifndef MENSAJE_H_
#define MENSAJE_H_

#include "Registro.h"

/**
 * @brief Estructura usada como tipo de dato que se envia a traves de la cola
 * de mensajes
 */

typedef struct sMensaje {
	long mtype;			// id del destinatario
	long idRemitente;
	int comando;
	Registro registro;
} Mensaje;

#endif
