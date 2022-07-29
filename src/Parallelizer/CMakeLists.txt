#set(CMAKE_CXX_STANDARD 20)
include_directories(../FileDependency ../ShellInterface ../Parser ../../vendor/taskflow ../Logger)

add_library(Parallelizer STATIC
            TaskScheduler.cpp)