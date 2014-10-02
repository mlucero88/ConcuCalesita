/*
 * Logger.h
 *
 *  Created on: 28/9/2014
 *      Author: nico
 */

#ifndef LOGGER_H
#define LOGGER_H
#include <fstream>
#include <iostream>
#include <cstdarg>
#include <string>
#include <time.h>

using namespace std;
#define LOGGER Logger::getLogger()

/**
 *   Singleton Logger Class.
 */
class Logger
{
public:
	enum Estado { COLA_BOLETERIA=0,
				  COLA_CALESITA=1,
				  EN_CALESITA=2,
				  COLA_SALIDA=3,
				  SALIO=4 };

    /**
     *   Logs a message
     *   @param nombre: nombre del ninio.
     *	 @param estado
     *
     */
    void Log(const std::string& nombre, Logger::Estado);
    /**
     *   Logs a message
     *   @param sMessage message to be logged.
     */
    void Log(const std::string& sMessage);
    /**
     *   Variable Length Logger function
     *   @param format string for the message to be logged.
     */
    void Log( const char * format, ... );
        /**
     *   << overloaded function to Logs a message
     *   @param sMessage message to be logged.
     */
    Logger& operator<<(const string& sMessage );
    /**
     *   Funtion to create the instance of logger class.
     *   @return singleton object of Clogger class..
     */
    static Logger* getLogger();
private:
    /**
     *    Default constructor for the Logger class.
     */
    Logger();
    /**
     *   copy constructor for the Logger class.
     */
    Logger( const Logger&){};             // copy constructor is private
    /**
     *   assignment operator for the Logger class.
     */
    Logger& operator=(const Logger& ){ return *this;};  // assignment operator is private
    /**
     *   Singleton logger class object pointer.
     **/
    static Logger* m_pThis;
    /**
     *   Log file stream object.
     **/
    static ofstream m_Logfile;

	string enumToString( Estado enumVal )
	{
	  switch( enumVal )
	  {
	  case COLA_BOLETERIA:
	    return "Cola de la boleteria";
	  case COLA_CALESITA:
	    return "Cola de la calesita";
	  case EN_CALESITA:
	    return "Girando en la calesita";
	  case COLA_SALIDA:
	    return "Cola de salida";
	  case SALIO:
	    return "Salio de la calesita";

	  default:
	    return "Estado desconocido..";
	  }
	}


};
#endif
