//
// Created by Gaurav Dawra on 12/06/22.
//

#include "Process.h"
#include <spawn.h>
#include <errno.h>
#include <string.h>
#include "Error.h"
extern char** environ;
namespace Beast {
	Process::Process(const std::string& command, int& exitStatus) : m_ExitStatus(exitStatus) {
		const char* args[] = {"/bin/sh", "-c", command.c_str(), NULL};
		auto status = posix_spawn(&m_Pid, "/bin/sh", NULL, NULL, const_cast<char**>(args), environ);
		if (status) {
			RAISE_ERROR_AND_EXIT(strerror(status), -1);
		}
	}
	
	Process::~Process() {
		int status;
		waitpid(m_Pid, &status, 0);
		m_ExitStatus = WEXITSTATUS(status);
	}
}
