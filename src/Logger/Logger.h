//
// Created by Gaurav Dawra on 14/01/22.
//

#pragma once

#include <string>

namespace Beast {
	class Logger {
	public:
		enum LogLevel {
			WARNING = 0,
			ERROR,
			INFO,
			DEBUG,
			PLAIN,
			DEFAULT
		};

//		template<typename T>
		static void log(const std::string& msg, LogLevel level);
		
	private:
		static const std::string m_HeadPrefix;
		static std::string getPrefixOfLevel(LogLevel level);
	};

	#define LOG_WARNING(msg) Beast::Logger::log(msg, Beast::Logger::LogLevel::WARNING)
	#define LOG_ERROR(msg)   Beast::Logger::log(msg, Beast::Logger::LogLevel::ERROR)
	#define LOG_INFO(msg)    Beast::Logger::log(msg, Beast::Logger::LogLevel::INFO)
	#define LOG_PLAIN(msg)   Beast::Logger::log(msg, Beast::Logger::LogLevel::PLAIN)
	#define LOG(msg)         Beast::Logger::log(msg, Beast::Logger::LogLevel::DEFAULT)
	
#ifdef BEAST_DEBUG
	#define LOG_DEBUG(msg)   Beast::Logger::log(msg, Beast::Logger::LogLevel::DEBUG)
#else
	#define LOG_DEBUG(msg)
#endif
}