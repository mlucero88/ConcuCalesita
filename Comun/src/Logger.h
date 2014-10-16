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
	virtual void Log(const std::string& nombre, Estado);

	/**
	 *   Logs a message
	 *   @param sMessage message to be logged.
	 */
	virtual void Log(const std::string& sMessage);

	/**
	 *   Variable Length Logger function
	 *   @param format string for the message to be logged.
	 */
	virtual void Log(const char * format, ...);

	/**
	 *   << overloaded function to Logs a message
	 *   @param sMessage message to be logged.
	 */
	Logger& operator<<(const std::string& sMessage);

	/**
	 *   Funtion to create the instance of logger class.
	 *   @return singleton object of Clogger class..
	 */
	static Logger* getLogger(bool unified = false);

	virtual ~Logger();

private:

	static const std::string logName(bool unified);

	/**
	 *   Singleton logger class object pointer.
	 **/
	static Logger* m_pThis;

	/**
	 *   Log file stream object.
	 **/

	/**
	 *   copy constructor for the Logger class.
	 */
	Logger(const Logger&);

	/**
	 *   assignment operator for the Logger class.
	 */
	Logger& operator=(const Logger&);

	std::string enumToString(Estado enumVal);
protected:
	/*static*/
	std::ofstream m_Logfile;

	/**
	 *    Default constructor for the Logger class.
	 */
	Logger(const std::string &);
};

#endif
