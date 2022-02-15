#include "Filesystem.h"
#include <iostream>
#include <vector>
#include "scanner.h"
#include "parser.hpp"
#include "Memory.h"
#include "Graph.h"
#include <chrono>

#include "Executor.h"
#include "Logger.h"

#include "TaskScheduler.h"

int main(int argc, char* argv[]) {
#ifdef BEAST_DEBUG
    auto t = std::chrono::high_resolution_clock::now();
#endif
    Beast::BuildFile buildFile;
    readBuildFile(buildFile);
    Beast::FileSystem fileSystem(buildFile);
    LOG_DEBUG("File system built");
    
    Beast::Parallelizer::TaskScheduler(buildFile, fileSystem).run(5);

//    Beast::Graph fileGraph(fileSystem.size());
//    Beast::buildGraph(fileSystem, buildFile, fileGraph);
//    fileGraph.topologicalSort();
//    LOG_DEBUG("graph built and sorted");
//	LOG_DEBUG("Starting build");
//    Beast::Builder::build(buildFile, fileSystem, fileGraph);
	LOG_DEBUG("Build complete");
#ifdef BEAST_DEBUG
    auto t2 = std::chrono::high_resolution_clock::now();
    auto duration = t2 - t;
    std::cout << (duration.count() / 1000.0f) <<" us" << std::endl;
#endif
    return 0;
}
// for static lib: g++-11 -std=c++2a main.cpp src/Filesystem.cpp -Isrc/ -Isrc/Parser  -lparser -L./src/Parser/ -o main
// for shared: g++-11 -std=c++2a main.cpp src/Filesystem.cpp -Isrc/ -Isrc/Parser  -lsparser -L./src/Parser/ -o main -rpath ./src/Parser/
