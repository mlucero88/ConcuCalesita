#ifndef TRADUCTORNINIO_H_
#define TRADUCTORNINIO_H_

#include <Pipe/ITraductor.h>
#include "Ninio.h"

class TraductorNinio: public ITraductor< Ninio > {
public:
	static const int ATRIBUTOS = 2;
	static const std::string NOMBRES[];
	explicit TraductorNinio();
	virtual ~TraductorNinio();
public:

	virtual std::string toJson(const Ninio& obj);

	virtual Ninio fromJson(std::string& json);
};

#endif
