#ifndef LOGGER_H
#define LOGGER_H

#include "EstadosNinio.h"
#include "Lock/Lock.h"
#include <string>
#include <fstream>

#define LOGGER Logger::getLogger()

/**
 *   Singleton Logger Class.
 */

class Logger {
public:

	/**
	 *   Logs a message
	 *   @param nombre: nombre del ninio.
	 *	 @param estado
	 */
	void log(const std::string& nombre, Estado);

	/**
	 *   Logs a message
	 *   @param sMessage message to be logged.
	 */
	void log(const std::string& sMessage);

	/**
	 *   Logs a message
	 *   @param cMessage message to be logged.
	 */
	void log(const char* cMessage);

	/**
	 *   Funtion to create the instance of logger class.
	 *   @return singleton object of Clogger class..
	 */
	static Logger& getLogger();

	~Logger();

private:

	/**
	 *   Log file stream object.
	 **/
	static std::ofstream m_Logfile;

	Lock lock;

	/**
	 *    Default constructor for the Logger class.
	 */
	Logger();

	/**
	 *   copy constructor for the Logger class.
	 */
	Logger(const Logger&);

	/**
	 *   assignment operator for the Logger class.
	 */
	Logger& operator=(const Logger&);

	std::string enumToString(Estado enumVal);
};

#endif
