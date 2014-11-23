#ifndef MENSAJE_H_
#define MENSAJE_H_

#include "Registro.h"

typedef struct sMensaje {
	long mtype;			// id del destinatario
	long idRemitente;
	int comando;
	Registro registro;
} Mensaje;

#endif
