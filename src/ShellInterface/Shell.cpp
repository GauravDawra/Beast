//
// Created by Gaurav Dawra on 29/12/21.
//

#include "Shell.h"
#include <array>
#include <stdio.h>
#include "Error.h"
//#include <iostream>
namespace Beast {

    std::string executeCommand(const std::string &command, int &exitStatus) {
        std::array<char, 128> buffer;
        std::string output;
        auto shellPipe = popen(command.c_str(), "r");
        if (!shellPipe) {
			RAISE_ERROR_AND_EXIT("connection to shell could not be established", -1);
        }
        while (fgets(buffer.data(), buffer.size(), shellPipe) != nullptr) {
            output += buffer.data();
        }
        int status;
        wait(&status);
        auto closingStatus = pclose(shellPipe);
	    exitStatus = WEXITSTATUS(status);
        return output;
    }

    std::string executeCommands(const std::vector<std::string> &commands, int &exitStatus) {
	    std::string jointCommand = "";
	    for (int i = 0; i < commands.size(); i++) {
		    // joining the commands using && so that they return on a single failure
		    jointCommand += (i == commands.size() - 1 ?
		                     commands[i] : commands[i] + " && ");
	    }
	    
	    return EXECUTE(jointCommand, exitStatus);
    }

//    bool checkTimeStamps(const BuildRule& rule, const FileSystem& fileSystem) {
//    	FileSystem::constFileRef outputTarget = fileSystem.getReference(rule.getOutputTarget());
//    	if (!outputTarget->exists()) {
//		    // if the file doesn't exist, always build it
//    		return true;
//    	}
//        auto outStamp = outputTarget->timeStamp();
//        for (const std::string& inputFile : rule.getInputTargets()) {
//            if (fileSystem.getReference(inputFile)->timeStamp() > outStamp) {
//                return true;
//            }
//        }
//        return false;
//    }
}