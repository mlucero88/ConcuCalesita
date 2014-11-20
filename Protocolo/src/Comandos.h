#ifndef COMANDOS_H_
#define COMANDOS_H_

class Comandos {
public:
	~Comandos();
	Comandos& getInstancia();

private:
	Comandos();
	Comandos(const Comandos&);
	Comandos& operator=(const Comandos&);
};

#endif
