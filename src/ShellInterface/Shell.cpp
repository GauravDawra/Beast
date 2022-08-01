//
// Created by Gaurav Dawra on 29/12/21.
//
#define _GNU_SOURCE
#include "Shell.h"
#include "Error.h"

#include <array>

#ifndef _WIN32
#include <stdio.h>
#include <sys/wait.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <spawn.h>
extern char** environ;
#else
#include <windows.h>
#endif
#include <string.h>

using namespace std;

namespace Beast {
#ifdef _WIN32
	void WIN_executeCommand(const std::string& command, int& exitStatus) {
		static HANDLE std_out = GetStdHandle(STD_OUTPUT_HANDLE);
		STARTUPINFO startupInfo = { };
		PROCESS_INFORMATION processInfo;

		SECURITY_ATTRIBUTES secAttr = {};
		secAttr.nLength = sizeof(SECURITY_ATTRIBUTES);
		secAttr.bInheritHandle = TRUE;
		secAttr.lpSecurityDescriptor = NULL;

		HANDLE childWrite = NULL, parentRead = NULL; // 2 ends of a pipe

		CreatePipe(&parentRead, &childWrite, &secAttr, 0);

		SetHandleInformation(parentRead, HANDLE_FLAG_INHERIT, 0);

		startupInfo.cb = sizeof(STARTUPINFO);
		startupInfo.hStdInput = NULL;
		startupInfo.hStdError = childWrite;
		startupInfo.hStdOutput = childWrite;
		startupInfo.dwFlags |= STARTF_USESTDHANDLES;

		std::string cmd = "cmd.exe /c " + command;

		if (!CreateProcess(NULL,
			(char*)(cmd.c_str()),
			NULL,
			NULL,
			TRUE,
			CREATE_NO_WINDOW,
			NULL,
			NULL,
			&startupInfo,
			&processInfo))
		{
			WaitForSingleObject(processInfo.hProcess, INFINITE);
			CloseHandle(processInfo.hProcess);
			CloseHandle(processInfo.hThread);
			RAISE_ERROR_AND_EXIT("Cannot create new process", -1);
		}

		CloseHandle(childWrite); // close this for parent process

		DWORD readLen = 1, writtenToStdout = 0;
#define MAX_BUF_SIZE 64 << 10
		char buffer[MAX_BUF_SIZE];
		while (readLen) {
			if (!ReadFile(parentRead, buffer, MAX_BUF_SIZE, &readLen, NULL) &&
				GetLastError() != ERROR_BROKEN_PIPE) {
				RAISE_ERROR_AND_EXIT("Cannot create new process", -1);
			}
			WriteFile(std_out, buffer, readLen, &writtenToStdout, NULL);
		}

		// Check for the failure of 2 functions below
		WaitForSingleObject(processInfo.hProcess, INFINITE);
		GetExitCodeProcess(processInfo.hProcess, (LPDWORD)&exitStatus);

		CloseHandle(parentRead);
		CloseHandle(processInfo.hProcess);
		CloseHandle(processInfo.hThread);
	}
#else
	FILE* shellRun(const string& command, int& pid) {
		pid_t child_pid;
		int fd[2];
		pipe(fd);
		
		if((child_pid = fork()) == -1)
		{
			perror("fork");
			RAISE_ERROR_AND_EXIT("cannot connect to shell", 1);
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
        // wait(&status);
        // waitpid(pid, &status, 0);
        auto closingStatus = shellClose(shellPipe, pid);
	    exitStatus = WEXITSTATUS(status);
        return output;
    }
	
    void executeCommand_Spawn(const std::string& command, int& exitStatus) {
	    posix_spawnattr_t attr;
		if (posix_spawnattr_init(&attr)) {
			RAISE_ERROR_AND_EXIT("Cannot create new process", -1);
		}
#ifdef POSIX_SPAWN_USEVFORK
		if (posix_spawnattr_setflags(&attr, POSIX_SPAWN_USEVFORK)) {
			RAISE_ERROR_AND_EXIT("Cannot create new process", -1);
		}
#endif
	    const char* args[] = {"/bin/sh", "-c", command.c_str(), NULL};
	    pid_t pid;
	    auto status = posix_spawn(&pid, "/bin/sh", NULL, &attr, const_cast<char**>(args), environ);
	    if (status) {
		    RAISE_ERROR_AND_EXIT(strerror(status), -1);
	    }
	    if (posix_spawnattr_destroy(&attr)); // decide later
	    waitpid(pid, &status, 0);
	    exitStatus = WEXITSTATUS(status);
	}
#endif
    void executeCommands(const std::vector<std::string> &commands, int &exitStatus) {
	    std::string jointCommand = "";
	    for (int i = 0; i < commands.size(); i++) {
		    // joining the commands using && so that they return on a single failure
		    jointCommand += (i == commands.size() - 1 ?
		                     commands[i] : commands[i] + " && ");
	    }
	    EXECUTE(jointCommand, exitStatus);
    }
}