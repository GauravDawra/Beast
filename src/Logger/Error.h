//
// Created by Gaurav Dawra on 09/01/22.
//

#pragma once

#include <string>
#include <iostream>

namespace Beast::Error {
	void raiseError(const std::string& msg, int exitStatus = 0);
	void raiseWarning(const std::string& msg);
}

namespace Beast {
	#define RAISE_ERROR(msg)                 Error::raiseError(msg)
	#define RAISE_ERROR_AND_EXIT(msg, es)    Error::raiseError(msg, es); exit(es)
	
	#define RAISE_WARNING(msg)               Error::raiseWarning(msg)
}