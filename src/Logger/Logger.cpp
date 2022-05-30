//
// Created by Gaurav Dawra on 14/01/22.
//

#include "Logger.h"
#include <sstream>
#include <iostream>

namespace Beast {
	const std::string Logger::m_HeadPrefix = "beast";
	
	void Logger::log(const std::string& msg, LogLevel level) {
		std::stringstream ss; // to make output thread safe
		if (level == PLAIN) { // plain is simple print
			ss << msg << std::endl;
		}
		else {                // all outputs that will contain the "beast" header
			ss << m_HeadPrefix << ": " << getPrefixOfLevel(level) << msg << std::endl;
		}
		if (level == ERROR)
			std::cerr << ss.str();
		else
			std::cout << ss.str();
	}
	
	std::string Logger::getPrefixOfLevel(Logger::LogLevel level) {
		switch (level) {
			case WARNING:
				return "warning: ";
				break;
			case ERROR:
				return "error: ";
				break;
			case INFO:
				return "info: ";
				break;
			case DEBUG:
				return "DBG: ";
				break;
			default:
				return "";
		}
	}
}