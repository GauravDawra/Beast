//
// Created by Gaurav Dawra on 03/01/22.
//

#include <stdlib.h>
#include "Executor.h"
#include <omp.h>
#include "Error.h"

namespace Beast::Builder {
	
	void setEnvironmentVariables(const SymbolTable &env) {
		for (const auto & it : env) {
			setenv(it.first.c_str(), toString(it.second).c_str(), 1);
		}
	}
	
	static std::string buildRule(const BuildRule& rule, int& exitStatus) {
		// first set the variables local to the rule
		std::vector<std::pair<std::string, std::string> > patch;
		patch.reserve(rule.getCommands().size());
//		#pragma omp parallel for
		for (SymbolTable::iterator it = rule.begin(); it != rule.end(); it++) {
			if (const char* val = std::getenv(toString(it->first).c_str())) {
				patch.emplace_back(toString(it->first), std::string(val));
			}
			else {
				patch.emplace_back(toString(it->first), "");
			}
		}
		setEnvironmentVariables(rule);
		// run the commands
		std::string output = executeCommands(rule.getCommands(), exitStatus);
		// reverse tha value of the local variables
		for (auto& [key, value] : patch) {
			if (value.length()) {
				setenv(key.c_str(), value.c_str(), 1);
			}
			else {
				// consider using unsetenv()
				setenv(key.c_str(), NULL, 1);
			}
		}
		return output;
	}
	
	int build(const BuildFile& buildFile, const FileSystem& fileSystem, Graph& fileGraph) {
		fileGraph.topologicalSort();
		if (fileGraph.isCyclical()) {
			RAISE_ERROR_AND_EXIT("Dependencies are cyclical", -1);
		}
		int exitStatus = 0;
		for (int index : fileGraph.getSorted()) {
			FileSystem::fileRef file = fileSystem.getReference(index);
			auto rule = buildFile.getRule(file->name());
			if (rule == nullptr and !file->exists()) {
//				std::cout << file->name() << " doesn't exist and has no build rule" << std::endl;
//				exit(-1);
				RAISE_ERROR_AND_EXIT(file->name() + " doesn't exist and has no build rule", -1);
			}
			if (rule == nullptr || !checkTimeStamps(*rule, fileSystem)) {
				continue; // just move on
			}
			std::cout << "executing commands for file " << file->name() << std::endl;
			std::cout << buildRule(*rule, exitStatus);
			if (exitStatus) {
//				std::cout << "Problem in executing build command" << std::endl;
				RAISE_ERROR("Problem in building rule \"" + rule->getOutputTarget() + "\"");
				return exitStatus;
			}
			file->refresh();    // refresh time stamp
		}
		return exitStatus;
	}
}