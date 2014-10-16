/*
 * UnifiedLogger.h
 *
 *  Created on: Oct 16, 2014
 *      Author: pable
 */

#ifndef UNIFIEDLOGGER_H_
#define UNIFIEDLOGGER_H_
#include "Logger.h"
#include "FilePaths.h"
#include <Lock/Lock.h>

class UnifiedLoggerLogger: public Logger {
public:
	UnifiedLoggerLogger(const std::string& name) :
			Logger(name), lock(Paths::getLoggerLockFile()) {

		//m_Logfile.open(name.c_str(), std::ios::out | std::ios::app);
	}

	virtual void Log(const std::string& nombre, Estado estado) {
		lock.seizeExclusiveLock();
		m_Logfile.seekp(0, m_Logfile.end);
		Logger::Log(nombre, estado);
		lock.releaseLock();
	}

	/**
	 *   Logs a message
	 *   @param sMessage message to be logged.
	 */
	virtual void Log(const std::string& sMessage) {
		lock.seizeExclusiveLock();
		m_Logfile.seekp(0, m_Logfile.end);
		Logger::Log(sMessage);
		lock.releaseLock();
	}

	/**
	 *   << overloaded function to Logs a message
	 *   @param sMessage message to be logged.
	 */
	UnifiedLoggerLogger& operator<<(const std::string& sMessage) {
		lock.seizeExclusiveLock();
		m_Logfile.seekp(0, m_Logfile.end);
		Logger::operator <<(sMessage);
		lock.releaseLock();
		return *this;
	}

	virtual ~UnifiedLoggerLogger() {

	}

private:
	Lock lock;
};

#endif /* UNIFIEDLOGGER_H_ */
