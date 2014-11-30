#ifndef COMANDOS_H_
#define COMANDOS_H_

namespace Protocolo {
/**
 *  \addtogroup Protocolo
 *  @{
 */

/**
 * @brief Tipos de comandos que se pueden enviar en el campo sMensaje::comando
 */
enum comando {
	cmd_unknown = -2,		///< Comando desconocido (gestor a cliente)
	op_failure,				///< Operacion fallida (gestor a cliente)
	op_success,				///< Operacion exitosa (gestor a cliente)
	add_reg,				///< Agregar registro (cliente a gestor)
	get_regs,				///< Obtener tabla (cliente a gestor)
	get_reg_by_name,		///< Obtener registro por nombre (cliente a gestor)
	reg_send				///< Envio de registro (gestor a cliente)
};

/**
 * @brief Identificador del gestor (usado en sMensaje)
 */
static const long idGestor = 1;

/** @} */
}

#endif
