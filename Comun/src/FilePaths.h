#ifndef FILEPATHS_H_
#define FILEPATHS_H_

#include <string>
#include <libgen.h>
#include <unistd.h>

/* Funciones para obtener rutas */

class Paths {

public:

	/* Retorna el directorio raiz del programa en su path absoluto.
	 * Ejemplo: "/home/usuario/misCosas/Concucalesita"
	 * Observar que no devuelve el '/' al final
	 */
	static std::string getProgramDirectory() {
		char buffer[buffSize];
		readlink("/proc/self/exe", buffer, buffSize);
		return std::string(dirname(dirname(buffer)));
	}

	static std::string getFifoGeneradorBoleteriaFilename() {
		return std::string(getProgramDirectory().append("/tmp/fifo_gen_bol"));
	}

	static std::string getFifoBoleteriaCalesitaFilename() {
		return std::string(getProgramDirectory().append("/tmp/fifo_bol_cal"));
	}

	static std::string getSharedMemoryFilename() {
		return std::string(getProgramDirectory().append("/tmp/shared_memory"));
	}

	static std::string getLoggerLockFile() {
		return std::string(getProgramDirectory().append("/tmp/lock_file"));
	}

	static char getSharedMemoryCharacter() {
		return 'M';
	}

	static std::string getConfigFilename() {
		return std::string(getProgramDirectory().append("/conf/config"));
	}

	static std::string getLogFolder() {
		return std::string(getProgramDirectory().append("/log/"));
	}

	static std::string getBinBoleteria() {
		return std::string(getProgramDirectory().append("/bin/boleteria"));
	}

	static std::string getBinCalesita() {
		return std::string(getProgramDirectory().append("/bin/calesita"));
	}

	static std::string getBinGenerador() {
		return std::string(getProgramDirectory().append("/bin/generador"));
	}

private:
	static const int buffSize = 1024;
	Paths();
};

#endif
