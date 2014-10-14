#ifndef LOGGER_H
#define LOGGER_H

#include "EstadosNinio.h"
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
	void Log(const std::string& nombre, Estado);

	/**
	 *   Logs a message
	 *   @param sMessage message to be logged.
	 */
	void Log(const std::string& sMessage);

	/**
	 *   Variable Length Logger function
	 *   @param format string for the message to be logged.
	 */
	void Log(const char * format, ...);

	/**
	 *   << overloaded function to Logs a message
	 *   @param sMessage message to be logged.
	 */
	Logger& operator<<(const std::string& sMessage);

	/**
	 *   Funtion to create the instance of logger class.
	 *   @return singleton object of Clogger class..
	 */
	static Logger* getLogger();

private:

	/**
	 *   Singleton logger class object pointer.
	 **/
	static Logger* m_pThis;

	/**
	 *   Log file stream object.
	 **/
	static std::ofstream m_Logfile;

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
