#ifndef COMANDOS_H_
#define COMANDOS_H_

// todo agregar e implementar comando solicitar registro por nombre

namespace Protocolo {

/**
 * @brief Tipos de comandos que se pueden enviar en el campo sMensaje::comando
 */
enum comando {
	cmd_unknown = -2,		///< Comando desconocido (gestor a cliente)
	op_failure,				///< Operacion fallida (gestor a cliente)
	op_success,				///< Operacion exitosa (gestor a cliente)
	add_reg,				///< Agregar registro (cliente a gestor)
	get_regs,				///< Obtener tabla (cliente a gestor)
	reg_send				///< Envio de registro (gestor a cliente)
};

/**
 * @brief Identificador del gestor (usado en sMensaje)
 */
static const long idGestor = 1;

}

#endif
