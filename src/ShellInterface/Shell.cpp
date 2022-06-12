//
// Created by Gaurav Dawra on 29/12/21.
//

#include "Shell.h"
#include <array>
#include <stdio.h>
#include "Error.h"
#include <sys/wait.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include "Process.h"
#include <spawn.h>

using namespace std;
extern char** environ;
namespace Beast {

	#define READ   0
	#define WRITE  1
	FILE* shellRun(const string& command, int& pid) {
		pid_t child_pid;
		int fd[2];
		pipe(fd);
		
		if((child_pid = fork()) == -1)
		{
			perror("fork");
			RAISE_ERROR_AND_EXIT("cannot connect to shell", 1);
//			exit(1);
		}
		
		/* child process */
		if (child_pid == 0){
			close(fd[0]);
			dup2(fd[1], 1);
			setpgid(child_pid, child_pid); //Needed so negative PIDs can kill children of /bin/sh
			execl("/bin/sh", "/bin/sh", "-c", command.c_str(), NULL);
			exit(0);
		}
		else {
			close(fd[1]);
		}
		
		pid = child_pid;
		
		return fdopen(fd[0], "r");
	}
	
	int shellClose(FILE* fp, pid_t pid)
	{
		int stat;
		fclose(fp);
		waitpid(pid, &stat, 0);
		if (errno != EINTR) {
			stat = -1;
		}
		return stat;
	}
	
	
	std::string executeCommand(const std::string &command, int &exitStatus) {
        std::array<char, 128> buffer;
        std::string output;
        int pid;
        auto shellPipe = shellRun(command.c_str(), pid);
        if (!shellPipe) {
			RAISE_ERROR_AND_EXIT("connection to shell could not be established", -1);
        }
        while (fgets(buffer.data(), buffer.size(), shellPipe) != nullptr) {
            output += buffer.data();
        }
        int status;
//        wait(&status);
//        waitpid(pid, &status, 0);
        auto closingStatus = shellClose(shellPipe, pid);
	    exitStatus = WEXITSTATUS(status);
        return output;
    }
	
    std::string executeCommand_Spawn(const std::string& command, int& exitStatus) {
//		Process* pro = new Process(command, exitStatus);

	    const char* args[] = {"/bin/sh", "-c", command.c_str(), NULL};
	    pid_t pid;
	    auto status = posix_spawn(&pid, "/bin/sh", NULL, NULL, const_cast<char**>(args), environ);
	    if (status) {
		    RAISE_ERROR_AND_EXIT(strerror(status), -1);
	    }
//	    int status;
	    waitpid(pid, &status, 0);
	    exitStatus = WEXITSTATUS(status);
	    return "";
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