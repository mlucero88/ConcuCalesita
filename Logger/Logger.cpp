/*
 * Logger.cpp
 *
 *  Created on: 28/9/2014
 *      Author: nico
 */

#include "Logger.h"

// Get current date/time, format is YYYY-MM-DD.HH:mm:ss
const std::string currentDateTime() {
    time_t     now = time(0);
    struct tm  tstruct;
    char       buf[80];
    tstruct = *localtime(&now);
    strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);

    return buf;
}

// Get current date, format is YYYYMMDD
const std::string logName() {
    time_t     now = time(0);
    struct tm  tstruct;
    char       buf[80];
    tstruct = *localtime(&now);
    strftime(buf, sizeof(buf), "Calsita_%Y%m%d.log", &tstruct);

    return buf;
}

Logger* Logger:: m_pThis = NULL;
ofstream Logger::m_Logfile;

Logger::Logger(){}

Logger* Logger::getLogger(){
    if(m_pThis == NULL){
        m_pThis = new Logger();
        m_Logfile.open(logName().c_str(), ios::out | ios::app );
    }
    return m_pThis;
}

void Logger::Log( const char * format, ... ){
    char sMessage[256];
    va_list args;
    va_start (args, format);
    vsprintf (sMessage,format, args);
    m_Logfile <<"\n"<< currentDateTime() <<":\t";
    m_Logfile << sMessage;
    va_end (args);
}

void Logger::Log(const std::string& nombre, Estado estado){
    m_Logfile <<"\n"<< currentDateTime() <<":\t";
    m_Logfile << nombre <<":\t";
    m_Logfile << enumToString(estado);
}

void Logger::Log( const string& sMessage ){
    m_Logfile <<"\n"<< currentDateTime() <<":\t";
    m_Logfile << sMessage;
}

Logger& Logger::operator<<(const string& sMessage ){
    m_Logfile <<"\n"<< currentDateTime() <<":\t";
    m_Logfile << sMessage;
    return *this;
}
