//
// Created by Gaurav Dawra on 13/02/22.
//

#ifndef BEAST_TASKSCHEDULER_H
#define BEAST_TASKSCHEDULER_H

#include "taskflow/taskflow.hpp"
#include "Filesystem.h"
#include "Graph.h"
#include <string>
#include <map>

namespace Beast::Parallelizer {
	
	class TaskScheduler { // works in conjunction with the FileSystem
	public:
		TaskScheduler(const BuildFile& buildFile, const FileSystem& fileSystem);
		void addDependency(const FileSystem::index_t& input, const FileSystem::index_t& output);
		void run(int numThreads);
	private:
		Graph m_FileGraph;
		const FileSystem& m_FileSystem;
		const BuildFile& m_BuildFile;
		tf::Taskflow m_Taskflow;
		std::map<FileSystem::index_t, tf::Task> m_TaskLookup;
		tf::Task& getTask(const FileSystem::index_t& target);
		void buildGraphAndDependencies();
	};
}


#endif //BEAST_TASKSCHEDULER_H
