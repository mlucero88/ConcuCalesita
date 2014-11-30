#ifndef MENSAJE_H_
#define MENSAJE_H_

#include "Registro.h"
#include "Comandos.h"

/**
 * @brief Estructura usada como tipo de dato que se envia a traves de la cola
 * de mensajes
 */
struct sMensaje {
	long mtype;							///< Identificador del destinatario
	long idRemitente;					///< Identificador del remitente
	enum Protocolo::comando comando;	///< Comando
	Registro registro;					///< Registro
};

typedef sMensaje Mensaje;

#endif
