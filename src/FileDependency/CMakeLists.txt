set(CMAKE_CXX_STANDARD 20)
include_directories(../Logger ../Parser)
add_library(FileDependency STATIC
            Graph.cpp
            Filesystem.cpp)