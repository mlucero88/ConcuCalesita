#include "Logger.h"
#include "FilePaths.h"
#include <cstdarg>
#include <ctime>
#include <iostream>

// Get current date/time, format is YYYY-MM-DD.HH:mm:ss
const std::string currentDateTime() {
	time_t now = time(0);
	struct tm tstruct;
	char buf[80];
	tstruct = *localtime(&now);
	strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);

	return buf;
}

const std::string logName() {
	return std::string(Paths::getLogFolder() + "concucalesita.log");
}

void Logger::log(const std::string& nombre, Estado estado) {
	try {
		lock.seizeExclusiveLock();
		m_Logfile << "\n" << currentDateTime() << ":\t";
		m_Logfile << nombre << ":\t";
		m_Logfile << enumToString(estado);
		m_Logfile.flush();
		lock.releaseLock();
	}
	catch(const LockException &e) {
		std::cerr << "Error al loguear. Fallo el lock" << std::endl;
	}
}

void Logger::log(const char* cMessage) {
	log(std::string(cMessage));
}

void Logger::log(const std::string& sMessage) {
	try {
		lock.seizeExclusiveLock();
		m_Logfile << "\n" << currentDateTime() << ":\t";
		m_Logfile << sMessage;
		m_Logfile.flush();
		lock.releaseLock();
	}
	catch(const LockException &e) {
		std::cerr << "Error al loguear. Fallo el lock" << std::endl;
	}
}

Logger& Logger::getLogger() {
	static Logger m_pThis;
	if (!m_Logfile.is_open()) {
		m_Logfile.open(logName().c_str(), std::ios::out | std::ios::app);
	}
	return m_pThis;
}

Logger::~Logger() {
	if (m_Logfile.is_open()) {
		m_Logfile.close();
	}
}

Logger::Logger() :
		lock(Paths::getLoggerLockFile()) {
}

Logger& Logger::operator=(const Logger&) {
	return *this;
}

std::string Logger::enumToString(Estado enumVal) {
	switch (enumVal) {
	case EN_COLA_BOLETERIA:
		return "En la cola de la boleteria";
	case COMPRA_BOLETO:
		return "Comprando boleto";
	case EN_COLA_CALESITA:
		return "En la cola de la calesita";
	case ENTRA_CALESITA:
		return "Entrando a la calesita";
	case SALE_CALESITA:
		return "Sale de la calesita";
	default:
		return "Estado desconocido";
	}
}

std::ofstream Logger::m_Logfile;
