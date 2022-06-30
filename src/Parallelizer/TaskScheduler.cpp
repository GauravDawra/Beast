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
	
	void TaskScheduler::addDependency(const FileSystem::index_t &input, const FileSystem::index_t &output) {
		// simply precede the input task to the output task
		getTask(input).precede(getTask(output));
	}
	
	tf::Task& TaskScheduler::getTask(const FileSystem::index_t &target) { // will retrieve and add tf::Task
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
			);
			// .name(m_FileSystem.name(target)); // not required now but can be used later
		}
		return it->second;
	}
	
	void TaskScheduler::buildGraphAndDependencies() {
		m_FileGraph.setNumTargets(m_FileSystem.numTargets());
		std::vector<int8_t> state(m_FileSystem.size(), 0);
		int numRequiredButNotPresent = 0;
		std::unordered_set<Graph::index_t> requiredButNotPresent;
		for (const BuildRule& rule : m_BuildFile.getRules()) {
			Graph::index_t outputIndex = m_FileSystem.index(rule.getOutputTarget());
			if (state[outputIndex] == 1) {
				numRequiredButNotPresent--;
				requiredButNotPresent.erase(outputIndex);
			}
			state[outputIndex] = 2; // it is present
			for (const std::string& inputTarget : rule.getInputTargets()) {
				Graph::index_t inputIndex = m_FileSystem.index(inputTarget);
				if (state[inputIndex] == 0 && !m_FileSystem.getReference(inputIndex)->exists()) {
					state[inputIndex] = 1;
					numRequiredButNotPresent++;
					requiredButNotPresent.insert(inputIndex);
				}
				if (inputIndex < m_FileGraph.numTargets()) {
					m_FileGraph.addEdge(inputIndex, outputIndex);
					addDependency(inputIndex, outputIndex);
					if (m_BuildFile.getRule(inputIndex)->toBuild()) {
						rule.setToBuild();
					}
				}
			}
			getTask(outputIndex);
		}
		if (requiredButNotPresent.size()) {
			RAISE_ERROR_AND_EXIT("Dependency " + m_FileSystem.name(*requiredButNotPresent.begin()) + " does not exist and has no build rule", -1);
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