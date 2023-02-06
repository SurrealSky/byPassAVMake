#include "./DebugLog.h"
#include"../LogLib/log4z.h"

using namespace zsummer::log4z;

namespace SurrealDebugLog
{
	void DebugLog(const std::string& OutputString)
	{
#ifdef Dbg
		ILog4zManager::getRef().setLoggerPath(LOG4Z_MAIN_LOGGER_ID, "./log");
		ILog4zManager::getRef().start();
		ILog4zManager::getRef().setLoggerLevel(LOG4Z_MAIN_LOGGER_ID, LOG_LEVEL_TRACE);
		//LOGD: LOG WITH level LOG_DEBUG
		//LOGI: LOG WITH level LOG_INFO

		LOGD(OutputString);

#endif
	}

	void DebugLog(const std::string& Tag, const std::string OutputString)
	{
#ifdef Dbg
		ILog4zManager::getRef().setLoggerPath(LOG4Z_MAIN_LOGGER_ID, "./log");
		ILog4zManager::getRef().start();
		ILog4zManager::getRef().setLoggerLevel(LOG4Z_MAIN_LOGGER_ID, LOG_LEVEL_TRACE);
		//LOGD: LOG WITH level LOG_DEBUG
		//LOGI: LOG WITH level LOG_INFO

		LOGD(Tag <<":"<<OutputString);
#endif
	}

	void DebugLogHex(const std::string &Tag, std::string &OutputString, SurrealTypes::STu32 OutputStringLen)
	{
#ifdef Dbg
		ILog4zManager::getRef().setLoggerPath(LOG4Z_MAIN_LOGGER_ID, "./log");
		ILog4zManager::getRef().start();
		ILog4zManager::getRef().setLoggerLevel(LOG4Z_MAIN_LOGGER_ID, LOG_LEVEL_TRACE);
		//LOGD: LOG WITH level LOG_DEBUG
		//LOGI: LOG WITH level LOG_INFO

		LOGD(Tag.c_str() << ":" << Log4zBinary(OutputString.c_str(), OutputStringLen));
		//LOGD(lpTag << ":" << lpOutputStringLen);

#endif
	}

}

