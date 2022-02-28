#include "Filesystem.h"
#include <iostream>
#include <vector>
#include "scanner.h"
#include "parser.hpp"
#include "Memory.h"
#include "Graph.h"
#include <chrono>
#include <Error.h>

#include "Executor.h"
#include "Logger.h"

#include "TaskScheduler.h"
#include "cxxopts.hpp"

const char* BUILD_FILE_NAME = "beast.build";

int main(int argc, char* argv[]) {
#ifdef BEAST_DEBUG
    auto t = std::chrono::high_resolution_clock::now();
#endif
	
	signed short numThreads = 1;
	std::string buildFileDirectory = "";
	cxxopts::Options CLIoptions(argv[0]);
	CLIoptions.add_options()
		("j,threads", "number of working threads", cxxopts::value<signed short>(numThreads)->default_value("1"))
		("d,directory", "directory containing build file", cxxopts::value<std::string>(buildFileDirectory)->default_value(""));
	
	try {
		auto result = CLIoptions.parse(argc, argv);
	} catch(const cxxopts::OptionException& e) {
		Beast::RAISE_ERROR_AND_EXIT(e.what(), -1);
	}
	
	LOG_DEBUG("Number of threads: " + std::to_string(numThreads));
	LOG_DEBUG("Build file directory: " + buildFileDirectory);
	
    Beast::BuildFile buildFile;
    Beast::readBuildFile(buildFile, std::filesystem::path(buildFileDirectory) / BUILD_FILE_NAME);
    Beast::FileSystem fileSystem(buildFile);
    LOG_DEBUG("File system built");
    if (numThreads == 1) {
        Beast::Graph fileGraph(fileSystem.size());
	    Beast::buildGraph(fileSystem, buildFile, fileGraph);
	    fileGraph.topologicalSort();
	    LOG_DEBUG("graph built and sorted");
		LOG_DEBUG("Starting build");
	    Beast::Builder::build(buildFile, fileSystem, fileGraph);
		LOG_DEBUG("Build complete");
    }
    else {
	    Beast::Parallelizer::TaskScheduler(buildFile, fileSystem).run(numThreads);
    }
    
#ifdef BEAST_DEBUG
    auto t2 = std::chrono::high_resolution_clock::now();
    auto duration = t2 - t;
    std::cout << (duration.count() / 1000.0f) <<" us" << std::endl;
#endif
    return 0;
}

// for static lib: g++-11 -std=c++2a main.cpp src/Filesystem.cpp -Isrc/ -Isrc/Parser  -lparser -L./src/Parser/ -o main
// for shared: g++-11 -std=c++2a main.cpp src/Filesystem.cpp -Isrc/ -Isrc/Parser  -lsparser -L./src/Parser/ -o main -rpath ./src/Parser/
