//
// Created by Gaurav Dawra on 13/02/22.
//

#include "TaskScheduler.h"
#include "Executor.h"
#include "Logger.h"
#include "Error.h"

namespace Beast::Parallelizer {
	
	TaskScheduler::TaskScheduler(const BuildFile &buildFile, const FileSystem &fileSystem) :
		m_FileGraph(fileSystem.size()), m_BuildFile(buildFile), m_FileSystem(fileSystem) {
		
		// build the graph and dependencies first
		buildGraphAndDependencies();
		m_FileGraph.topologicalSort();
		LOG_DEBUG("At the end of task scheduler");
	}
	
	void TaskScheduler::addDependency(const std::string &input, const std::string &output) {
		// simply precede the input task to the output task
		getTask(input).precede(getTask(output));
	}
	
	tf::Task& TaskScheduler::getTask(const std::string &target) { // will retrieve and add tf::Task
		LOG_DEBUG("Inside getTask for " + target);
		auto it = m_TaskLookup.find(target);
		if (it == m_TaskLookup.end()) {
			return m_TaskLookup[target] = m_Taskflow.emplace(
				[&, target] () {
					LOG_DEBUG("Starting build for " + target);
					int es = Builder::checkAndBuild(target, m_BuildFile, m_FileSystem);
					if (es) {
						exit(es);
					}
					LOG_DEBUG("Build complete for " + target);
				}
			).name(target);
		}
		return (*it).second;
	}
	
	void TaskScheduler::buildGraphAndDependencies() {
		for (const BuildRule& rule : m_BuildFile.getRules()) {
			int outputIndex = m_FileSystem.index(rule.getOutputTarget());
			for (const std::string& inputTarget : rule.getInputTargets()) {
				m_FileGraph.addEdge(m_FileSystem.index(inputTarget), outputIndex);
				addDependency(inputTarget, rule.getOutputTarget());
			}
		}
	}
	
	void TaskScheduler::run(int numThreads = 2) {
		// blocking call that runs till all the tasks have been built
		if (m_FileGraph.isCyclical()) {
			RAISE_ERROR_AND_EXIT("Dependencies are cyclical", -1);
		}
		tf::Executor executor(numThreads);
		executor.run(m_Taskflow).wait();
	}
	
}