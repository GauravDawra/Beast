#include "Filesystem.h"
#include <vector>
#include "unix_scanner.h"
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
#define SET_CWD(cwd) try { if(cwd.length()) std::filesystem::current_path(cwd); } \
					catch (std::exception& e) { Beast::RAISE_ERROR_AND_EXIT("couldn't open directory " + cwd, -1); }

int main(int argc, char* argv[]) {
#ifdef BEAST_DEBUG
    auto t = std::chrono::high_resolution_clock::now();
#endif
	signed short numThreads = 1;
	std::string buildFileDirectory;
	cxxopts::Options CLIoptions(argv[0]);
	CLIoptions.add_options()
		("j,threads", "number of working threads", cxxopts::value<signed short>(numThreads)->default_value("1"))
		("d,directory", "directory containing build file", cxxopts::value<std::string>(buildFileDirectory)->default_value(""))
		("h,help", "print help");
	
	cxxopts::ParseResult result;
	try {
		result = CLIoptions.parse(argc, argv);
	} catch(const cxxopts::OptionException& e) {
		Beast::RAISE_ERROR_AND_EXIT(e.what(), 2);
	}
	
	if (result.count("help")) { // print help
		LOG_PLAIN(CLIoptions.help());
		exit(0);
	}
	
	LOG_DEBUG("Number of threads: " + std::to_string(numThreads));
	LOG_DEBUG("Build file directory: " + buildFileDirectory);
	
    Beast::BuildFile buildFile;
    SET_CWD(buildFileDirectory);
    Beast::readBuildFile(buildFile, BUILD_FILE_NAME);
    Beast::FileSystem fileSystem(buildFile);
    LOG_DEBUG("File system built");
    if (numThreads == 1) {
        Beast::Graph fileGraph(fileSystem.size());
	    Beast::buildGraph(fileSystem, buildFile, fileGraph);
	    LOG_DEBUG("graph built and sorted");
		LOG_DEBUG("Starting build");
	    int es = Beast::Builder::build(buildFile, fileSystem, fileGraph);
		LOG_DEBUG("Build complete");
		if (es) exit(es);
    }
    else {
	    Beast::Parallelizer::TaskScheduler(buildFile, fileSystem).run(numThreads);
	    LOG_DEBUG("Parallel build complete");
    }
    
#ifdef BEAST_DEBUG
    auto t2 = std::chrono::high_resolution_clock::now();
    auto duration = t2 - t;
    std::cout << (duration.count() / 1000.0f) <<" us" << std::endl;
#endif
    return 0;
}