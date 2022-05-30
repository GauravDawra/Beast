//
// Created by Gaurav Dawra on 03/01/22.
//

#pragma once

#include "Memory.h"
#include "Shell.h"
#include "Filesystem.h"
#include "Graph.h"

namespace Beast::Builder {
	void setEnvironmentVariables(const SymbolTable& env);
	
	// the following is the sequential build function
	int build(const BuildFile& buildFile, const FileSystem& fileSystem, Graph& fileGraph);
	
	// the following checks if the target really needs to be built
//	int checkForBuilding(const std::string& target, const BuildFile& buildFile, const FileSystem& fileSystem);
	
	int checkAndBuild(const FileSystem::index_t& target, const BuildFile& buildFile,
					   const FileSystem& fileSystem);
}