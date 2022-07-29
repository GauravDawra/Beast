#set(CMAKE_CXX_STANDARD 20)

include_directories(../Parser ../FileDependency ../Logger)

add_library(ShellInterface STATIC
            Executor.cpp
            Shell.cpp)