//
// Created by Gaurav Dawra on 14/01/22.
//

#include "Logger.h"

namespace Beast {
	const std::string Logger::m_HeadPrefix = "beast";
	
//	template<typename T>
	void Logger::log(const std::string& msg, LogLevel level) {
		std::cout << m_HeadPrefix << ": " << getPrefixOfLevel(level) << ": " << msg << std::endl;
	}
	
	std::string Logger::getPrefixOfLevel(Logger::LogLevel level) {
		switch (level) {
			case WARNING:
				return "warning";
				break;
			case ERROR:
				return "error";
				break;
			case INFO:
				return "info";
				break;
			case DEBUG:
				return "DBG";
				break;
			default:
				return "";
		}
	}
}