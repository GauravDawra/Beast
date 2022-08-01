//
// Created by Gaurav Dawra on 29/12/21.
//

#pragma once

#include <string>
#include <vector>

namespace Beast {

#ifdef _WIN32
    #define EXECUTE(comm, status) WIN_executeCommand(comm, status)
#else
    #define EXECUTE(comm, status) executeCommand_Spawn(comm, status)
//    #define EXECUTE(comm, status) executeCommand(comm, status)
#endif
    void executeCommands(const std::vector<std::string>& commands, int& exitStatus);
    
}