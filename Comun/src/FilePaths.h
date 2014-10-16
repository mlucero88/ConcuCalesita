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

	// Pablo, fijate si te sirve
	static std::string getFifoGeneradorBoleteriaFilename() {
		return std::string(getProgramDirectory().append("/temp/fifo_gen_bol"));
	}

	// Pablo, fijate si te sirve
	static std::string getFifoBoleteriaCalesitaFilename() {
		return std::string(getProgramDirectory().append("/temp/fifo_bol_cal"));
	}

	static std::string getSharedMemoryFilename() {
		return std::string(getProgramDirectory().append("/temp/shared_memory"));
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

	static std::string getLoggerLockFile() {
			return std::string(getProgramDirectory().append("/tmp/lock_file"));
		}

private:
	static const int buffSize = 1024;
	Paths();
};

#endif
