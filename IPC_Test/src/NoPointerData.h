#ifndef NOPOINTERDATA_H_
#define NOPOINTERDATA_H_

#include "Shared_Memory/SharedMemoryData.h"

class NoPointerData: public SharedMemoryData {
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
	int entero;
	double real;
	char caracter;
};

#endif /* NOPOINTERDATA_H_ */
