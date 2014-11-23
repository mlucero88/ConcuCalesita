#ifndef PROTOCOLO_H_
#define PROTOCOLO_H_

#include "Mensaje.h"
#include <string>

template < class T >
class MessageQueue;

class Protocolo {
public:

	enum comando {
		cmd_unknown = -2, op_failure, op_success, add_reg, get_regs
	};

	virtual ~Protocolo();

	virtual Mensaje recibirMensaje() const = 0;

protected:
	MessageQueue< Mensaje >* cola;
	static const long idGestor = 1;

	Protocolo(const std::string& nombreArchivo,
			char caracter) /* throw (std::string) */;

private:

	// Prohibo las siguientes operaciones
	Protocolo(const Protocolo&);
	Protocolo& operator=(const Protocolo&);
};

#endif
