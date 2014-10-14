#include <unistd.h>
#include <sys/wait.h>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cerrno>
#include "Configuracion.h"

int main(int argc, char* argv[]) {
	pid_t boleteria, calesita, generador;

	try {
		Configuracion conf;

		boleteria = fork();
		if (boleteria == 0) {
			int ret = execl(Paths::getBinBoleteria().c_str(),
					Paths::getBinBoleteria().c_str(), conf.getPrecioBoleto(),
					(char*) NULL);
			if (ret == -1) {
				std::cerr << "Error al ejecutar el proceso boleteria (exec). "
						<< strerror(errno) << std::endl;
				exit(EXIT_FAILURE);
			}
		}
		if (boleteria == -1) {
			std::cerr << "Error al crear el proceso boleteria (fork). "
					<< strerror(errno) << std::endl;
			exit(EXIT_FAILURE);
		}

		calesita = fork();
		if (calesita == 0) {
			int ret = execl(Paths::getBinCalesita().c_str(),
					Paths::getBinCalesita().c_str(),
					conf.getCapacidadCalesita(),
					conf.getDuracionVueltaCalesita(), (char*) NULL);
			if (ret == -1) {
				std::cerr << "Error al ejecutar el proceso calesita (exec). "
						<< strerror(errno) << std::endl;
				exit(EXIT_FAILURE);
			}
		}
		if (calesita == -1) {
			std::cerr << "Error al crear el proceso calesita (fork). "
					<< strerror(errno) << std::endl;
			exit(EXIT_FAILURE);
		}

		generador = fork();
		if (generador == 0) {
			int ret = execl(Paths::getBinGenerador().c_str(),
					Paths::getBinGenerador().c_str(),
					conf.getCantidadNiniosGenerador(), (char*) NULL);
			if (ret == -1) {
				std::cerr << "Error al ejecutar el proceso generador (exec). "
						<< strerror(errno) << std::endl;
				exit(EXIT_FAILURE);
			}
		}
		if (generador == -1) {
			std::cerr << "Error al crear el proceso generador (fork). "
					<< strerror(errno) << std::endl;
			exit(EXIT_FAILURE);
		}

		int status;
		waitpid(generador, &status, 0);
		std::cout << "Código de finalización del proceso generador: " << status
				<< std::endl;
		waitpid(calesita, &status, 0);
		std::cout << "Código de finalización del proceso calesita: " << status
				<< std::endl;
		waitpid(boleteria, &status, 0);
		std::cout << "Código de finalización del proceso boleteria: " << status
				<< std::endl;
	}
	catch(std::string& e) {
		std::cerr << e;
		exit(EXIT_FAILURE);
	}

	return 0;
}
