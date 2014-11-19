#ifndef INTERFAZSERVIDOR_H_
#define INTERFAZSERVIDOR_H_

class SocketServidor;

class InterfazServidor {
public:

	InterfazServidor(const char *puerto);

	bool crearSocket();
	bool enlazar();
	bool escuchar(int colaMaxima);
	void atenderCliente();
	bool cerrarSocket();
	~InterfazServidor();

private:
	SocketServidor *servidor;
};

#endif
