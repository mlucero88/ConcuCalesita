/*
 * ITraductor.h
 *
 *  Created on: Oct 12, 2014
 *      Author: pable
 */

#ifndef ITRADUCTOR_H_
#define ITRADUCTOR_H_
#include <string>
template<class T>
class ITraductor {
public:
	ITraductor() {
	}
	virtual ~ITraductor() {
	}
public:

	virtual std::string toJson(const T& obj)=0;

	virtual T fromJson(std::string& json)=0;
};

#endif /* ITRADUCTOR_H_ */
