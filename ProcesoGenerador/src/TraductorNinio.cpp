/*
 * TraductorNinio.cpp
 *
 *  Created on: Oct 12, 2014
 *      Author: pable
 */

#include "TraductorNinio.h"
#include <stdexcept>
#include <jsoncpp/json/writer.h>
#include <jsoncpp/json/reader.h>

const std::string TraductorNinio::NOMBRES[] = { "nombre", "estado" };
TraductorNinio::TraductorNinio() {
	// TODO Auto-generated constructor stub

}

TraductorNinio::~TraductorNinio() {
	// TODO Auto-generated destructor stub
}

std::string TraductorNinio::toJson(const Ninio& obj) {
	Json::Value json;
	json["nombre"] = obj.getNombre();
	json["estado"] = obj.getEstado();
	Json::FastWriter writer;
	return writer.write(json);
}

Ninio TraductorNinio::fromJson(std::string& json) {
	Json::Value root;   // will contains the root value after parsing.
	Json::Reader reader;
	bool parsingSuccessful = reader.parse(json, root);
	if (!parsingSuccessful) {
		throw std::runtime_error("malformed json");
	}
	Ninio n("prueba");
	for (unsigned int i = 0; i < ATRIBUTOS; i++) {
		switch (i) {
		case 0:
			n.setNombre(root.get(NOMBRES[i], "").asString());
			break;
		case 1:
			n.setEstado(Estado(root.get(NOMBRES[i], "").asInt()));
			break;
		default:
			break;
		}
	}
	return n;
}
