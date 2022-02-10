//
// Created by Gaurav Dawra on 03/01/22.
//

#pragma once

#include "Memory.h"
#include "Shell.h"

namespace Beast::Builder {
	void setEnvironmentVariables(const SymbolTable& env);
	int build(const BuildFile& buildFile, const FileSystem& fileSystem, Graph& fileGraph);
}