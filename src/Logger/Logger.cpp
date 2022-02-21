//
// Created by Gaurav Dawra on 14/01/22.
//

#include "Logger.h"
#include <sstream>

namespace Beast {
	const std::string Logger::m_HeadPrefix = "beast";
	
	void Logger::log(const std::string& msg, LogLevel level) {
		std::stringstream ss; // to
		ss << m_HeadPrefix << ": " << getPrefixOfLevel(level) << ": " << msg << std::endl;
		std::cout << ss.str();
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