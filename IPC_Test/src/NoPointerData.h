#ifndef NOPOINTERDATA_H_
#define NOPOINTERDATA_H_

#include "Common/ByteStream.h"

class NoPointerData {
public:
	NoPointerData();
	NoPointerData(int entero, double real, char caracter);
	~NoPointerData();

	int getEntero() const;
	double getReal() const;
	char getCaracter() const;

	const ByteStream serialize() const;
	void hidratate(const ByteStream& stream);

private:
	double real;
	int entero;
	char caracter;
};

#endif /* NOPOINTERDATA_H_ */
