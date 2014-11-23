#ifndef COMANDOS_H_
#define COMANDOS_H_

namespace Protocolo {
enum comando {
	cmd_unknown = -2, op_failure, op_success, add_reg, get_regs, reg_send
};

static const long idGestor = 1;

}

#endif
