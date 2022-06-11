//
// Created by Gaurav Dawra on 03/01/22.
//

#include <stdlib.h>
#include "Executor.h"
#include "Logger.h"
#include "Error.h"
#include <iostream>
//#include <omp.h> // bye bye omp for now :)

namespace Beast::Builder {
	
	void setEnvironmentVariables(const SymbolTable &env) {
		for (const auto & it : env) {
			setenv(it.first.c_str(), toString(it.second).c_str(), 1);
		}
	}
	
//	static std::string buildRule(const BuildRule& rule, int& exitStatus) {
//		std::string output = executeCommands(rule.getCommands(), exitStatus);
//		return output;
//	}
	
	// sequential build
	int build(const BuildFile& buildFile, const FileSystem& fileSystem, Graph& fileGraph) {
		fileGraph.topologicalSort();
		if (fileGraph.isCyclical()) {
			RAISE_ERROR_AND_EXIT("Dependencies are cyclical", -1);
		}
		int exitStatus = 0;
		for (Graph::index_t index : fileGraph.getSorted()) {
			if((exitStatus = checkAndBuild(index, buildFile, fileSystem))) {
				return exitStatus;
			}
		}
		return exitStatus;
	}
	
	bool checkTimeStamps(const BuildRule& rule, const FileSystem& fileSystem) { // not used
		FileSystem::constFileRef outputTarget = fileSystem.getReference(rule.getOutputTarget());
		if (!outputTarget->exists()) {
			// if the file doesn't exist, always build it
			return true;
		}
		auto outStamp = outputTarget->timeStamp();
		for (const std::string& inputFile : rule.getInputTargets()) {
			if (fileSystem.getReference(inputFile)->timeStamp() > outStamp) {
				return true;
			}
		}
		return false;
	}
	
	int checkAndBuild(const FileSystem::index_t& target, const BuildFile& buildFile, const FileSystem& fileSystem) {
		auto rule = buildFile.getRule(target);
		if (rule == nullptr) return 0; // originally it was with the timestamp check below
		auto file = fileSystem.getReference(target);
		
//		if(rule == nullptr and !file->exists()) {
//			RAISE_ERROR(file->name() + " doesn't exist and has no build rule");
//			return -1;
//		} // now handled by buildGraph() // may change later
		
//		if (!checkTimeStamps(*rule, fileSystem))
//			return 0;
//
		if (!rule->toBuild() && file->exists()) {
			auto outStamp = file->timeStamp();
			auto inputTargets = rule->getInputTargets();
			bool buildTarget = false;
			for (int i = 0; i < inputTargets.size(); i++) {
				auto inputRule = buildFile.getRule(inputTargets[i]);
				if ((inputRule && inputRule->isBuilt())){
//				|| fileSystem.getReference(inputTargets[i])->timeStamp() > outStamp) { // this last condition is now never going to be because of m_ToBuild in build rules

					buildTarget = true;
					break;
				}
			}
			if (!buildTarget) return 0;
		}
//		if(rule == nullptr || !checkTimeStamps(*rule, fileSystem)) {
//			// no need to build
//			return 0;
//		}
		
		// if control reaches this point, then the rule is surely being built
		LOG("Building rule " + file->name());
		int exitStatus = 0;
		printf("%s", rule->build(exitStatus).c_str());
//		std::cout << rule->build(exitStatus);
		if(exitStatus){
			RAISE_ERROR("Problem in building rule \"" + file->name() + "\"");
			return exitStatus;
		}
//		file->refresh();
		return 0;
	}
}