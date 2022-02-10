//
// Created by Gaurav Dawra on 14/01/22.
//

#include "Logger.h"
#include "Error.h"

namespace Beast::Error {
	void raiseError(const std::string& msg, int exitStatus) {
		LOG_ERROR(msg);
//		exit(exitStatus);
	}
	void raiseWarning(const std::string& msg) {
		LOG_WARNING(msg);
	}
}