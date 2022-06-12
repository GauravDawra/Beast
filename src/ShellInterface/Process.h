//
// Created by Gaurav Dawra on 12/06/22.
//

#ifndef BEAST_PROCESS_H
#define BEAST_PROCESS_H
#include <string>
namespace Beast {
	class Process {
	public:
		Process(const std::string& command, int& exitStatus);
		~Process();
	private:
		pid_t m_Pid;
		int& m_ExitStatus;
	};
}


#endif //BEAST_PROCESS_H
