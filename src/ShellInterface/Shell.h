//
// Created by Gaurav Dawra on 29/12/21.
//

#pragma once

//#include "Memory.h"
#include <string>
#include <vector>
//#include "Graph.h"
//#include "Filesystem.h"

namespace Beast {
    std::string executeCommand(const std::string& command, int& exitStatus);
//    #define EXECUTE(comm, status) executeCommand(comm, status)
	#define EXECUTE(comm, status) executeCommand_Spawn(comm, status)
    void executeCommands(const std::vector<std::string>& commands, int& exitStatus);
//    bool checkTimeStamps(const BuildRule& rule, const FileSystem& fileSystem);
    
}