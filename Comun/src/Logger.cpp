#include "Logger.h"
#include "UnifiedLogger.h"
#include <unistd.h>

#include "FilePaths.h"
#include <cstdarg>
#include <ctime>
#include <sstream>

// Get current date/time, format is YYYY-MM-DD.HH:mm:ss
const std::string currentDateTime() {
	time_t now = time(0);
	struct tm tstruct;
	char buf[80];
	tstruct = *localtime(&now);
	strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);

	return buf;
}

// Get current date, format is YYYYMMDD
const std::string Logger::logName(bool unified) {
	/* todo: El problema de poner hora es que cada proceso pone su hora cuando
	 * llama por primera vez a este metodo */
//	time_t now = time(0);
//	struct tm tstruct;
//	char buf[80];
//	tstruct = *localtime(&now);
//	std::string filename(Paths::getLogFolder() + "Calesita_%Y%m%d.log");
//	strftime(buf, sizeof(buf), filename.c_str(), &tstruct);
//	return buf;
	//return std::string(Paths::getLogFolder() + "concucalesita.log");
	if (!unified) {
		std::stringstream ss;
		std::string pid;
		ss << getpid();
		ss >> pid;
		return std::string(Paths::getLogFolder()) + "concucalesita." + pid + ".log";
	} else {
		return std::string(Paths::getLogFolder()) + "concucalesita.log";
	}
}

void Logger::Log(const std::string& nombre, Estado estado) {
	m_Logfile << "\n" << currentDateTime() << ":\t";
	m_Logfile << nombre << ":\t";
	m_Logfile << enumToString(estado);
	m_Logfile.flush();
}

void Logger::Log(const std::string& sMessage) {
	m_Logfile << "\n" << currentDateTime() << ":\t";
	m_Logfile << sMessage;
	m_Logfile.flush();
}

void Logger::Log(const char * format, ...) {
	char sMessage[256];
	va_list args;
	va_start(args, format);
	vsprintf(sMessage, format, args);
	m_Logfile << "\n" << currentDateTime() << ":\t";
	m_Logfile << sMessage;
	va_end(args);
	m_Logfile.flush();
}

Logger& Logger::operator<<(const std::string& sMessage) {
	m_Logfile << "\n" << currentDateTime() << ":\t";
	m_Logfile << sMessage;
	m_Logfile.flush();
	return *this;
}

Logger* Logger::getLogger(bool unified) {
	if (m_pThis == NULL) {
		if (!unified) {
			m_pThis = new Logger(logName(unified));
		} else {
			m_pThis = new UnifiedLoggerLogger(logName(unified));
		}
	}
	return m_pThis;
}

Logger::Logger(const std::string& name) {
	m_Logfile.open(name.c_str(), std::ios::out | std::ios::app);
}

Logger::Logger(const Logger&) {
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

Logger::~Logger() {
	m_Logfile.close();
}

Logger* Logger::m_pThis = NULL;
//std::ofstream Logger::m_Logfile;
